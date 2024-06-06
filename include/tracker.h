#ifndef TRACKER_H
#define TRACKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <map>
#include <string>
#include <vector>

class Tracker {
public:
    Tracker();
    void initializeTrackers(const cv::Mat& frame, const std::map<std::string, cv::Rect>& boundingBoxes);
    void updateTrackers(const cv::Mat& frame);
    std::map<std::string, cv::Rect> getBoundingBoxes() const;

private:
    std::map<std::string, cv::Ptr<cv::Tracker>> trackers;
    std::map<std::string, cv::Rect> boundingBoxes;
};

#endif // TRACKER_H
