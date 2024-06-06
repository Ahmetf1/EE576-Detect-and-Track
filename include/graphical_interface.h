#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <constants.h>
#include <functional>

class GraphicalInterface {
public:
    GraphicalInterface();

    /**
     * @brief Starts the image Processor application.
     */
    void run();

    /**
     * @brief Sets the function object to fetch images.
     * @param fetchImage The function object to fetch images.
     */
    void setFetchImageFunction(const std::function<cv::Mat(int)>& fetchImage);

private:
    static constexpr int width = constants::width; ///< Width of the display window.
    static constexpr int height = constants::height; ///< Height of the display window.

    // Define a function object to fetch image getting int as input and returning cv::Mat
    std::function<cv::Mat(int)> fetchImage;

    /**
     * @brief Displays images in a grid format.
     * @param num The number of images to display in the grid.
     */
    void displayImage(const cv::Mat& img);


    /**
     * @brief Creates a welcome screen with messages.
     * @param messages The messages to display on the welcome screen.
     * @param width The width of the welcome screen.
     * @param height The height of the welcome screen.
     * @return A cv::Mat object containing the welcome screen.
     */
    cv::Mat createWelcomeScreen(const std::vector<std::string>& messages, int width, int height);


};

#endif // IMAGEPROCESSOR_H
