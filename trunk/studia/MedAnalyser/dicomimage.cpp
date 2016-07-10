#include "dicomimage.h"

DICOMImage::DICOMImage()
{

}

void DICOMImage::normalizeImage()
{
    int rows = image.rows;
    int cols = image.cols;

    cv::Mat res = cv::Mat(rows, cols, CV_8UC3);
    cv::Mat_<cv::Vec3b> _R = res;
    cv::Mat_<int> _I = image;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
        {
            int newValue = double(_I(i, j)) / double(maxValue) * 255.0;
            _R(i, j)[0] = _R(i, j)[1] = _R(i, j)[2] = newValue;
        }

    res = _R;
    image = res;
}

