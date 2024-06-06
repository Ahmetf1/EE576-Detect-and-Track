#include <iostream>
#include <tracker.h>
#include <graphical_interface.h>

int main() {
    std::cout << "Hello" << std::endl;
    GraphicalInterface gui;
    gui.setFetchImageFunction([](int index) {
        // return black image if index is even, white image if index is odd
        return cv::Mat(100, 100, CV_8UC3, cv::Scalar(index % 2 == 0 ? 0 : 255));
    });
    gui.run();
}