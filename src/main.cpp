#include <iostream>
#include <tracker.h>
#include <graphical_interface.h>
#include <opencv2/opencv.hpp>
#include <yolov7_cxx.h>
#include <dataset.h>



cv::Mat _process_image(cv::Mat &img, YOLOv7_CXX::YOLOv7 &yolo, Tracker &tracker);

int main() {
    std::cout << "Hello" << std::endl;
    GraphicalInterface gui;
    YOLOv7_CXX::YOLOv7 yolo("best.onnx");
    Tracker tracker;
    Dataset dataset("../dataset/rgbd-scenes/kitchen_small/kitchen_small_1");
    std::function<cv::Mat(int)> process_image = [&dataset, &yolo](int index) {
        cv::Mat img = cv::imread(dataset.get(index));
        img = _process_image(img, yolo);
        return img;
    };
    gui.setFetchImageFunction(process_image);
    gui.run();
}

cv::Mat _process_image(cv::Mat &img, YOLOv7_CXX::YOLOv7 &yolo, Tracker &tracker) {
    auto detections = YOLOv7_CXX::detect_on_mat(img, yolo);
    std::map<std::string, cv::Rect> boundingBoxes;
    for (const auto &det : detections[0])
    {
        cv::rectangle(img, cv::Rect(det.x , det.y, det.w, det.h), cv::Scalar(0, 255, 0), 2);
        cv::putText(img, det.name, cv::Point(det.x, det.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        cv::putText(img, std::to_string(det.confidence), cv::Point(det.x, det.y + 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        boundingBoxes[det.name] = cv::Rect(det.x, det.y, det.w, det.h);
    }
    return img;
}