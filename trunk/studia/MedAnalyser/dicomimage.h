#ifndef DICOMIMAGE_H
#define DICOMIMAGE_H

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class DICOMImage
{
public:
    DICOMImage();
    virtual ~DICOMImage() {}
    virtual void parse() = 0;
    virtual void openImageFile() = 0;

    std::string getFilePath() { return filepath; }
    cv::Mat getImage() { return image; }
protected:
    std::string filepath;
    cv::Mat image;

    int maxValue;
    int minValue;

    bool imageConverted = false;

    virtual void convertImage() = 0;
    void normalizeImage();
};

#endif // DICOMIMAGE_H
