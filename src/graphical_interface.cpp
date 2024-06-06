#include <graphical_interface.h>
#include <iostream>
#include <constants.h>

using namespace cv;
using namespace std;

GraphicalInterface::GraphicalInterface() {}

void GraphicalInterface::displayImage(const cv::Mat& img) {
    if (img.empty()) {
        cerr << "Failed to load image." << endl;
        return;
    }

    imshow("Display", img);
}


cv::Mat GraphicalInterface::createWelcomeScreen(const std::vector<std::string>& messages, int width, int height) {

    // Create a black image
    cv::Mat welcomeScreen = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);

    // Define the rectangle for the instructions
    cv::Rect instructionRect(50, height / 4, width - 50, height / 2);

    // Draw a black rectangle for the instructions background
    cv::rectangle(welcomeScreen, instructionRect, cv::Scalar(0, 0, 0), cv::FILLED);

    // Set the text properties
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.75;
    int thickness = 2;
    cv::Scalar textColor(255, 255, 255); // White color for the text

    // Calculate the position to center the text inside the rectangle
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(messages[0], fontFace, fontScale, thickness, &baseline);
    cv::Point textOrg((welcomeScreen.cols - textSize.width) / 2, 
                      instructionRect.y + (instructionRect.height + textSize.height) / 2);

    // Put the instruction texts in vector onto the welcome screen
    for (int i = 0; i < messages.size(); i++) {
        cv::putText(welcomeScreen, messages[i], textOrg, fontFace, fontScale, textColor, thickness);
        textOrg.y += textSize.height * 2;
    }

    return welcomeScreen;
}

void GraphicalInterface::setFetchImageFunction(const std::function<cv::Mat(int)>& fetchImage) {
    this->fetchImage = fetchImage;
}

void GraphicalInterface::run() {
    namedWindow(constants::windowName, WINDOW_AUTOSIZE);
    displayImage(createWelcomeScreen({"Press Enter to view image", "Press 'a' and 'd' to navigate images", "Press 'q' to quit"}, width, height));
    int selectedImage = 0;

    while (true) {
        int number = -1;
        char key = waitKey(0);
        if (key == 'q') break;
        else if (key == 13 || key == 10) {
            displayImage(fetchImage(selectedImage));
        } 
        // Move with a and d keys
        else if (key == 'a') {
            selectedImage -= 1;
            if (selectedImage < 0) selectedImage = 0;
            displayImage(fetchImage(selectedImage));
        } else if (key == 'd') {
            selectedImage += 1;
            displayImage(fetchImage(selectedImage));
        }
        else if (key >= '0' && key <= '9') {
            // If the key is a digit, we process it to construct a number
            string numberStr = "";
            numberStr += key; // Add the first digit

            // Continue to capture digits until Enter is pressed
            while(true) {
                key = waitKey(0);
                if (key == 13 || key == 10) { // If Enter is pressed, break
                    number = atoi(numberStr.c_str());
                    selectedImage = number;
                    displayImage(fetchImage(selectedImage));
                    std::cout << "Current image: " << number << std::endl;
                    break;
                }
                else if (key >= '0' && key <= '9') {
                    numberStr += key; // Append the digit to the number string
                }
            }

        }
    }
}
