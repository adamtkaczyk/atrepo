#include "imageslice.h"

ImageSlice::ImageSlice(cv::Mat inPhaseImage, cv::Mat outOfPhaseImage) : inPhaseImage(inPhaseImage), outOfPhaseImage(outOfPhaseImage)
{
    steatosis = 0;
}

int ImageSlice::getSteatosis() const
{
    return steatosis;
}

void ImageSlice::setSteatosis(int value)
{
    steatosis = value;
}

cv::Mat ImageSlice::getOutOfPhaseImage() const
{
    return outOfPhaseImage;
}

void ImageSlice::setOutOfPhaseImage(const cv::Mat &image)
{
    outOfPhaseImage = image;
}

cv::Mat ImageSlice::getInPhaseImage() const
{
    return inPhaseImage;
}

void ImageSlice::setInPhaseImage(const cv::Mat &image)
{
    inPhaseImage = image;
}

