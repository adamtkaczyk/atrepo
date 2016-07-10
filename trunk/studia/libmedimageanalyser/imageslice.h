#ifndef IMAGESLICE_H
#define IMAGESLICE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageSlice
{
public:
    ImageSlice(cv::Mat inPhaseImage, cv::Mat outOfPhaseImage);
    int getSteatosis() const;
    void setSteatosis(int value);

    cv::Mat getOutOfPhaseImage() const;
    void setOutOfPhaseImage(const cv::Mat &image);

    cv::Mat getInPhaseImage() const;
    void setInPhaseImage(const cv::Mat &image);

private:
    cv::Mat inPhaseImage;
    cv::Mat outOfPhaseImage;
    int steatosis;
};

#endif // IMAGESLICE_H
