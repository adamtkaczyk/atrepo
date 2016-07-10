#ifndef IMAGESEGMENTS_H
#define IMAGESEGMENTS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageSegments
{
public:
    ImageSegments();

    ///metoda wyszukuje segmenty na obrazie
    void labelImage(cv::Mat &image);
    ///metoda usuwa z obrazu segmenty o mniejszych rozmiarach niż podane
    void removeSmallSegments(cv::Mat& image, int size);
    std::vector<cv::Point2i > filter(cv::Mat& image);

    ///metoda zwraca maksymalny rozmiar segmentu w pikselach
    unsigned int getMaxSize();

    ///metoda usuwa punkty segmentu z obrazka (ustawia na wartość 0)
    void removeSegmentsFromImage(cv::Mat& image, std::vector<cv::Point2i > segment);
private:
    std::vector < std::vector<cv::Point2i > > segments;
};

#endif // IMAGESEGMENTS_H
