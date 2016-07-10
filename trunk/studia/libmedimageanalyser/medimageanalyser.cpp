#include "medimageanalyser.h"
#include "imagesegments.h"

using namespace cv;

MedImageAnalyser::MedImageAnalyser()
{
}

MedImageAnalyser::~MedImageAnalyser()
{
}

MedImageAnalyser& MedImageAnalyser::getInstance()
{
    static MedImageAnalyser instance;

    return instance;
}

void MedImageAnalyser::convertImage(ImageSlice& slice, int cannyValue)
{
    Mat grayImage;
    Mat image = slice.getInPhaseImage();
    cvtColor(image, grayImage, CV_RGB2GRAY);
    Mat orgImage = grayImage.clone();

    ///wykrywanie krawędzi za pomocą operatora canny-ego
    Canny(grayImage, grayImage, cannyValue, cannyValue * 2, 3);

    ///Pocienianie krawędzi
    thinning(grayImage);

    ImageSegments segments;
    ///Usunięcie małych segmentów
    segments.labelImage(grayImage);
    segments.removeSmallSegments(grayImage, 350);

    ///znalezienie punktów gdzie krawędzi się urywa
    auto points = findEndPixel(grayImage);

    ///Połączenie punktów krawędzi które są blisko siebie
    closeEgde(grayImage, points, 10.0);

    segments.labelImage(grayImage);
    auto seg = segments.filter(grayImage);

    Mat mask = createMask(image.rows, image.cols, seg);
    cv::normalize(mask, mask, 0, 255, cv::NORM_MINMAX);


    Mat e = (Mat_<char>(3, 3) <<
        1, 1, 1,
        1, 1, 1,
        1, 1, 1);

    erode(mask, mask,e, Point(-1, -1), 2);

    cv::Mat imc = image.clone();
    cv::cvtColor(imc, imc, CV_RGB2GRAY);

    setImageWithMask(imc, mask, 0, 0);
    equalizeHistWithMask(imc, imc, mask);

    //poprawienie jakości dla centralnego fragmentu zdjęcia
    Mat q(imc, getBundleBox(mask,4));
    GaussianBlur(q, q, Size(3, 3), 0, 0, BORDER_DEFAULT);

    cv::Canny(imc, imc, 65, 65 * 2, 3);

    ///Pocienianie krawędzi
    thinning(imc);

    ///Usunięcie małych segmentów
    segments.labelImage(imc);
    segments.removeSmallSegments(imc, 15);

    points = findEndPixel(imc);
    closeEdgeWithClosest(imc, points);
    segments.labelImage(imc);

    Mat image2 = getImage(imc, mask, 30);

    int morph_size = 1;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    morphologyEx(image2, image2, MORPH_CLOSE, element, Point(-1, -1), 1);

    Mat image3;
    getEdgeFromBinary(image2, image3);

    segments.labelImage(image3);

    int max = segments.getMaxSize();
    segments.removeSmallSegments(image3, max - 1);

    image3 = orgImage + image3;

    cvtColor(image3, image3, CV_GRAY2RGB);
    slice.setInPhaseImage(image3);
    //return slice;
}

void MedImageAnalyser::setImageWithMask(Mat image, Mat mask, int maskValue, int newValue)
{
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
            if (mask.at<uchar>(i, j) == maskValue)
                image.at<uchar>(i, j) = newValue;
}

void MedImageAnalyser::hitmiss(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel)
{
    CV_Assert(src.type() == CV_8U && src.channels() == 1);

    cv::Mat k1 = (kernel == 1) / 255;
    cv::Mat k2 = (kernel == -1) / 255;

    cv::Mat e1, e2;
    cv::erode(src, e1, k1, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT, cv::Scalar(0));
    cv::erode(1 - src, e2, k2, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT, cv::Scalar(0));
    dst = e1 & e2;
}

void MedImageAnalyser::thin(cv::Mat& image, cv::Mat& element)
{
    cv::Mat res = image.clone();
    hitmiss(image, res, element);

    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
            image.at<uchar>(i, j) = (image.at<uchar>(i, j) + res.at<uchar>(i, j)) % 2;
}

void MedImageAnalyser::thinning(cv::Mat& image)
{
    cv::Mat prev;
    bool eq = true;
    Mat e1 = (Mat_<char>(3, 3) <<
        -1, -1, -1,
        0, 1, 0,
        1, 1, 1);

    Mat e2 = (Mat_<char>(3, 3) <<
        0, -1, -1,
        1, 1, -1,
        0, 1, 0);

    Mat e3 = (Mat_<char>(3, 3) <<
        1, 0, -1,
        1, 1, -1,
        1, 0, -1);

    Mat e4 = (Mat_<char>(3, 3) <<
        0, 1, 0,
        1, 1, -1,
        0, -1, -1);

    Mat e5 = (Mat_<char>(3, 3) <<
        1, 1, 1,
        0, 1, 0,
        -1, -1, -1);

    Mat e6 = (Mat_<char>(3, 3) <<
        0, 1, 0,
        -1, 1, 1,
        -1, -1, 0);

    Mat e7 = (Mat_<char>(3, 3) <<
        -1, 0, 1,
        -1, 1, 1,
        -1, 0, 1);

    Mat e8 = (Mat_<char>(3, 3) <<
        -1, -1, 0,
        -1, 1, 1,
        0, 1, 0);

    cv::normalize(image, image, 0, 1, cv::NORM_MINMAX);
    do
    {
        prev = image;

        thin(image, e1);
        thin(image, e2);
        thin(image, e3);
        thin(image, e4);
        thin(image, e5);
        thin(image, e6);
        thin(image, e7);
        thin(image, e8);

        eq = std::equal(image.begin<uchar>(), image.end<uchar>(), prev.begin<uchar>());
    } while (!eq);
    //cv::Mat diff = im1 != im2;
    // Equal if no elements disagree
    //bool eq = cv::countNonZero(diff) == 0;
    cv::normalize(image, image, 0, 255, cv::NORM_MINMAX);
}

void MedImageAnalyser::closeEgde(Mat& image, std::list<Point> endPoints, double maxDistance)
{
    while(!endPoints.empty())
    {
        auto it = endPoints.begin();
        auto itNext = it;
        for (++itNext; itNext != endPoints.end(); ++itNext)
            if (getLength(*it, *itNext) < maxDistance)
            {
                line(image, *it, *itNext, Scalar(255));
                endPoints.erase(itNext);
                break;
            }

        endPoints.erase(it);
    }
}

std::list<Point> MedImageAnalyser::findEndPixel(cv::Mat& image)
{
    std::list<Point> points;
    cv::Mat res = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
        {
            if (image.at<uchar>(i, j) == 255)
            {
                int num = 0;
                if (image.at<uchar>(i - 1, j) == 255)
                    num++;
                if (image.at<uchar>(i + 1, j) == 255)
                    num++;
                if (image.at<uchar>(i, j - 1) == 255)
                    num++;
                if (image.at<uchar>(i, j + 1) == 255)
                    num++;
                if (image.at<uchar>(i - 1, j - 1) == 255)
                    num++;
                if (image.at<uchar>(i + 1, j - 1) == 255)
                    num++;
                if (image.at<uchar>(i - 1, j + 1) == 255)
                    num++;
                if (image.at<uchar>(i + 1, j + 1) == 255)
                    num++;

                if (num == 1)
                    points.push_back(Point(j, i));
            }
        }
    return points;
}

cv::Mat MedImageAnalyser::createMask(int rows, int cols, std::vector<cv::Point2i > segment)
{
    //cv::Mat image = cv::Mat::zeros(rows, cols, CV_8UC1);
    cv::Mat image = cv::Mat::ones(rows, cols, CV_8UC1);

    for (auto it = segment.begin(); it != segment.end(); ++it)
        image.at<uchar>(it->y, it->x) = 0;

    cv::floodFill(image, cv::Point(0, 0), 0);

    return image;
}

void MedImageAnalyser::equalizeHistWithMask(const Mat& src, Mat& dst, Mat1b mask)
{
    int cnz = countNonZero(mask);
    if (mask.empty() || (cnz == src.rows*src.cols))
    {
        equalizeHist(src, dst);
        return;
    }

    dst = src.clone();

    // Histogram
    std::vector<int> hist(256, 0);
    for (int r = 0; r < src.rows; ++r) {
        for (int c = 0; c < src.cols; ++c) {
            if (mask(r, c)) {
                hist[src.at<uchar>(r, c)]++;
            }
        }
    }

    // Cumulative histogram
    float scale = 255.f / float(cnz);
    std::vector<uchar> lut(256);
    int sum = 0;
    for (unsigned int i = 0; i < hist.size(); ++i) {
        sum += hist[i];
        lut[i] = saturate_cast<uchar>(sum * scale);
    }

    // Apply equalization
    for (int r = 0; r < src.rows; ++r) {
        for (int c = 0; c < src.cols; ++c) {
            if (mask(r, c)) {
                dst.at<uchar>(r, c) = lut[src.at<uchar>(r, c)];
            }
        }
    }
}

unsigned int MedImageAnalyser::getLength(Point A, Point B)
{
    return sqrt(pow(A.x - B.x,2) + pow(A.y - B.y,2));
}

cv::Rect MedImageAnalyser::getFirstRect(cv::Mat mask, int size)
{
    cv::Rect rect;
    rect.width = size;
    rect.height = size;
    for (int j = 0; j < mask.cols; ++j)
        for (int i = 0; i < mask.rows; ++i)
            if (mask.at<uchar>(i, j) == 255)
            {
                rect.x = j;
                rect.y = i - size/2;
                return rect;
            }

    //return p;
    return rect;
}

Point MedImageAnalyser::getFirstPoint(cv::Mat mask, int size)
{
    int x, y;
    for (int j = 0; j < mask.cols; ++j)
        for (int i = 0; i < mask.rows; ++i)
            if (mask.at<uchar>(i, j) == 255)
            {
                x = j + size;
                y = i;
                return Point(x,y);
            }
}

cv::Mat MedImageAnalyser::getImage(cv::Mat& image, cv::Mat mask, int size)
{
    Mat im = image.clone();
    Point p = getFirstPoint(mask, size);
    cv::Rect rect;
    cv::floodFill(im, p, 255, &rect, 0, 0, 4);

    return im - image;
}

void MedImageAnalyser::getEdgeFromBinary(cv::Mat& src, cv::Mat& dst)
{
    dst = src.clone();
    cv::normalize(dst, dst, 0, 1, cv::NORM_MINMAX);
    cv::normalize(src, src, 0, 1, cv::NORM_MINMAX);

    for (int j = 1; j < src.cols - 1; ++j)
        for (int i = 1; i < src.rows - 1; ++i)
        {
            if (src.at<uchar>(i - 1, j) == 1 && src.at<uchar>(i + 1, j) == 1 &&
                src.at<uchar>(i, j - 1) == 1 && src.at<uchar>(i, j + 1) == 1)
            {
                dst.at<uchar>(i, j) = 0;
                //std::cout << "Jest" << std::endl;
            }
        }

    cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX);
    cv::normalize(src, src, 0, 255, cv::NORM_MINMAX);
}

cv::Rect MedImageAnalyser::getBundleBox(cv::Mat& image, int divX, int divY)
{
    int minX = image.cols;
    int maxX = 0;
    int minY = image.rows;
    int maxY = 0;

    for (int j = 1; j < image.cols - 1; ++j)
        for (int i = 1; i < image.rows - 1; ++i)
            if(image.at<uchar>(i,j) == 255)
            {
                if (j > maxX)
                    maxX = j;
                if (j < minX)
                    minX = j;
                if (i > maxY)
                    maxY = i;
                if (i < minY)
                    minY = i;
            }

    int width = (maxX - minX) / divX;
    int height = (maxY - minY) / divY;
    int diffX = ((maxX - minX) - width) / 2;
    int diffY = ((maxY - minY) - height) / 2;

    return Rect(minX + diffX, minY + diffY, width, height);
}

void MedImageAnalyser::closeEdgeWithClosest(Mat& image, std::list<Point> endPoints)
{
    for (auto it = endPoints.begin(); it != endPoints.end(); ++it)
    {
        std::list<Point>::iterator itClosest;
        int dist = 99999;
        for (auto itNext = endPoints.begin(); itNext != endPoints.end(); ++itNext)
        {
            if (it == itNext)
                continue;
            int newDist = getLength(*it, *itNext);
            if (newDist < dist)
            {
                itClosest = itNext;
                dist = newDist;
            }
        }

        line(image, *it, *itClosest, Scalar(255));
    }
}
