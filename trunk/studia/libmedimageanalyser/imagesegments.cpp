#include "imagesegments.h"

using namespace cv;

ImageSegments::ImageSegments()
{

}

void ImageSegments::labelImage(cv::Mat &image)
{
    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground

    segments.clear();
    cv::Mat label_image;
    image.convertTo(label_image, CV_32SC1);

    int label_count = 2; // starts at 2 because 0,1 are used already

    for (int y = 0; y < label_image.rows; y++) {
        int *row = (int*)label_image.ptr(y);
        for (int x = 0; x < label_image.cols; x++) {
            if (row[x] != 255) {
                continue;
            }

            cv::Rect rect;
            //wypełniia segment daną wartością
            cv::floodFill(label_image, cv::Point(x, y), label_count, &rect, 0, 0, 8);

            std::vector <cv::Point2i> blob;

            //punkty z tą wartością dodaje do wektora
            for (int i = rect.y; i < (rect.y + rect.height); i++) {
                int *row2 = (int*)label_image.ptr(i);
                for (int j = rect.x; j < (rect.x + rect.width); j++) {
                    if (row2[j] != label_count) {
                        continue;
                    }

                    blob.push_back(cv::Point2i(j, i));
                }
            }

            segments.push_back(blob);

            label_count++;
        }
    }
}

void ImageSegments::removeSmallSegments(cv::Mat& image, int size)
{
    int df = 255, v = 255;
    int num = 0;
    cv::Mat output = cv::Mat::zeros(image.size(), CV_8UC1);
    for (size_t i = 0; i < segments.size(); i++) {
        if (segments[i].size() > size)
        {
            v = df = 255;//df - 40;
            num++;
        }
        else
            v = 0;
        for (size_t j = 0; j < segments[i].size(); j++) {
            int x = segments[i][j].x;
            int y = segments[i][j].y;

            output.at<uchar>(y, x) = v;
        }
    }

    image = output;
}

std::vector<cv::Point2i > ImageSegments::filter(cv::Mat& image)
{
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

    std::vector<cv::Point2i > res;
    int size = image.cols;

    for (auto it = segments.begin(); it != segments.end(); ++it)
    {
        auto itPoint = it->begin();
        minX = maxX = itPoint->x;
        minY = maxY = itPoint->y;
        for (itPoint++; itPoint != it->end(); ++itPoint)
        {
            if (itPoint->x < minX)
                minX = itPoint->x;
            if (itPoint->x > maxX)
                maxX = itPoint->x;
            if (itPoint->y < minY)
                minY = itPoint->y;
            if (itPoint->y > maxY)
                maxY = itPoint->y;
        }

        if (maxX - minX < image.cols * 0.6 || maxY - minY < image.rows * 0.6)
            removeSegmentsFromImage(image, *it);
        else
            if (maxX - minX < size)
                res = *it;
    }

    return res;
}

unsigned int ImageSegments::getMaxSize()
{
    unsigned int max = 0;
    for (auto it = segments.begin(); it != segments.end(); ++it)
        if (it->size() > max)
            max = it->size();

    return max;
}

void ImageSegments::removeSegmentsFromImage(cv::Mat& image, std::vector<cv::Point2i > segment)
{
    for (auto it = segment.begin(); it != segment.end(); it++)
        image.at<uchar>(it->y, it->x) = 0;
}
