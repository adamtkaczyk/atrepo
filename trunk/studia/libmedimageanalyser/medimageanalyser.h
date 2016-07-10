#ifndef MEDIMAGEANALYSER_H
#define MEDIMAGEANALYSER_H

#include "imageslice.h"

#include <string>
#include <vector>
#include <list>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MedImageAnalyser
{
public:
    static MedImageAnalyser& getInstance();

    void convertImage(ImageSlice& slice, int cannyValue);

private:
    MedImageAnalyser();
    ~MedImageAnalyser();

    MedImageAnalyser(const MedImageAnalyser&) = delete;
    MedImageAnalyser(MedImageAnalyser &&) = delete;
    MedImageAnalyser& operator=(const MedImageAnalyser&) = delete;
    MedImageAnalyser& operator=(MedImageAnalyser&&) = delete;

    ///metoda na podstawie maski ustawia wszystkie pixele które pasują do maski na
    /// na nową wartość newValue
    void setImageWithMask(cv::Mat image, cv::Mat mask, int maskValue, int newValue);
    void thinning(cv::Mat& image);
    void thin(cv::Mat& image, cv::Mat& element);
    void hitmiss(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel);
    //void removeSmallSegments(cv::Mat& image, std::vector< std::vector<cv::Point2i > > segments, int size);
    //std::vector < std::vector<cv::Point2i > > labelImage(cv::Mat &image);
    void closeEgde(cv::Mat& image, std::list<cv::Point> endPoints, double maxDistance);
    std::list<cv::Point> findEndPixel(cv::Mat& image);
    //std::vector<cv::Point2i > filter(cv::Mat& image, std::vector< std::vector<cv::Point2i > > segments);
    cv::Mat createMask(int rows, int cols, std::vector<cv::Point2i > segment);
    void equalizeHistWithMask(const cv::Mat& src, cv::Mat& dst, cv::Mat1b mask = cv::Mat1b());
    unsigned int getLength(cv::Point A, cv::Point B);

    cv::Rect getFirstRect(cv::Mat mask, int size);
    cv::Point getFirstPoint(cv::Mat mask, int size);
    cv::Mat getImage(cv::Mat& image, cv::Mat mask, int size);
    void getEdgeFromBinary(cv::Mat& src, cv::Mat& dst);
    cv::Rect getBundleBox(cv::Mat& image, int divX = 1, int divY = 1);
    void closeEdgeWithClosest(cv::Mat& image, std::list<cv::Point> endPoints);

    ///metoda usuwa punkty segmentu z obrazka (ustawia na wartość 0)
    //void removeSegmentsFromImage(cv::Mat& image, std::vector<cv::Point2i > segment);
};

#endif // MEDIMAGEANALYSER_H
