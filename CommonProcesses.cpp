/* *******************************************************
 * Filename     : CommonProcesses.cpp
 * Author       : Muhammet Mert KUÞ
 * Date         : 05.01.2024
 * Description  : CommonProcesses Class Implementation
 * ******************************************************/

#include "CommonProcesses.h"

 /**
  * @brief Constructor that takes the filename of an image and reads the image.
  * @param filename The filename of the image to be read.
  * @throws std::runtime_error if the image cannot be opened or has an unsupported number of channels.
  */
CommonProcesses::CommonProcesses(const std::string& filename) {
    readRGBFromFile(filename);
}

/**
 * @brief Reads an RGB image from a file.
 * @param filename The filename of the image to be read.
 * @throws std::runtime_error if the image cannot be opened or has an unsupported number of channels.
 */
void CommonProcesses::readRGBFromFile(const std::string& filename) {
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
    if (image.empty() || (image.channels() != 3 && image.channels() != 4)) {
        throw std::runtime_error("Could not open or find the image, or the number of channels is not supported: " + filename);
    }
    setRGBPic(image);
}

/**
 * @brief Sets the RGB image data and clones it for reference.
 * @param data The RGB image data to be set.
 */
void CommonProcesses::setRGBPic(const cv::Mat& data) {
    orginalPic = data.clone();
    RGBPic = data.clone();
}

/**
 * @brief Gets the RGB image data.
 * @return The RGB image data.
 */
const cv::Mat& CommonProcesses::getRGBPic() const {
    return RGBPic;
}

/**
 * @brief Gets the cloned copy of the original image.
 * @return The cloned copy of the original image.
 */
const cv::Mat& CommonProcesses::getOrginalPic() const {
    return orginalPic;
}

/**
 * @brief Filters noise using GaussianBlur.
 */
void CommonProcesses::filterNoise() {
    cv::Mat result;
    cv::GaussianBlur(RGBPic, result, cv::Size(5, 5), 1.5);
    RGBPic = result;
}

/**
 * @brief Denoises the image using bilateral filtering.
 */
void CommonProcesses::denoiseBilateralFilter() {
    cv::Mat denoisedImage;
    cv::bilateralFilter(RGBPic, denoisedImage, 9, 75, 75);
    RGBPic = denoisedImage;
}

/**
 * @brief Rescales the image to the specified width and height.
 * @param width The target width for rescaling.
 * @param height The target height for rescaling.
 */
void CommonProcesses::rescale(int width, int height) {
    cv::Mat result;
    cv::resize(RGBPic, result, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
    RGBPic = result;
}

/**
 * @brief Converts the image to grayscale.
 */
void CommonProcesses::convertToGrays() {
    cv::Mat result;
    cv::cvtColor(RGBPic, result, cv::COLOR_BGR2GRAY);
    RGBPic = result;
}
