/* *******************************************************
 * Filename		:	CommonProcesses.h
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	CommonProcesses Class Header
 * ******************************************************/

#pragma once
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>

class CommonProcesses {
private:
    cv::Mat RGBPic;        ///< Original raw RGB image data
    cv::Mat orginalPic;    ///< Cloned copy of the original image

public:
    /**
     * @brief Constructor that takes the filename of an image and reads the image.
     * @param filename of the image to be processed.
     */
    CommonProcesses(const std::string& filename);

    /**
     * @brief Destructor.
     */
    virtual ~CommonProcesses() {}

    /**
     * @brief read an RGB image from a file.
     * @param filename of the image to be read.
     */
    void readRGBFromFile(const std::string& filename);

    /**
     * @brief Getter for raw RGB data.
     * @return The raw RGB image data.
     */
    const cv::Mat& getRGBPic() const;

    /**
     * @brief Setter for raw RGB data, also clones the original image for reference.
     * @param data The raw RGB image data to be set.
     */
    void setRGBPic(const cv::Mat& data);

    /**
     * @brief Getter for the cloned copy of the original image.
     * @return The cloned copy of the original image.
     */
    const cv::Mat& getOrginalPic() const;

    /**
     * @brief filter noise using GaussianBlur.
     */
    void filterNoise();

    /**
     * @brief rescale the image to the specified width and height.
     * @param Rescale width and height for target width
     */
    void rescale(int width, int height);

    /**
     * @brief convert the image to grayscale.
     */
    void convertToGrays();

    /**
     * @brief denoise the image using bilateral filtering.
     */
    void denoiseBilateralFilter();
};