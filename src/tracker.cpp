#include "tracker.h"

Tracker::Tracker() {}

void Tracker::initializeTrackers(const cv::Mat& frame, const std::map<std::string, cv::Rect>& boundingBoxes) {
    for (const auto& [label, box] : boundingBoxes) {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
        tracker->init(frame, cv::Rect2d(box));
        trackers[label] = tracker;
        this->boundingBoxes[label] = box;
    }
}

void Tracker::updateTrackers(const cv::Mat& frame) {
    for (auto& [label, tracker] : trackers) {
        cv::Rect box;
        if (tracker->update(frame, box)) {
            boundingBoxes[label] = cv::Rect(box);
        }
    }
}

std::map<std::string, cv::Rect> Tracker::getBoundingBoxes() const {
    return boundingBoxes;
}
