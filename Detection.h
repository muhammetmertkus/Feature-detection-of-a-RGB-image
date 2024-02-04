/* *******************************************************
 * Filename		:	Detection.h
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	Detection Class Header
 * ******************************************************/

#pragma once
#include "CommonProcesses.h"
#include <vector>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>

 /**
  * @brief Detection class that inherits from CommonProcesses and defines abstract methods for feature detection.
  */
class Detection : public CommonProcesses {
public:
    /**
     * @brief Constructor that initializes Detection class by invoking the base class constructor (CommonProcesses).
     * @param filename The filename of the image to be processed.
     */
    Detection(const std::string& filename);

    /**
     * @brief Virtual destructor for Detection class.
     */
    virtual ~Detection() {}

    /**
     * @brief Pure virtual method to be implemented by derived classes for analyzing features.
     */
    virtual void analyzeFeatures() = 0;

    /**
     * @brief Pure virtual method to be implemented by derived classes for plotting features.
     */
    virtual void plotFeatures() const = 0;

    /**
     * @brief Pure virtual method to be implemented by derived classes for getting analyzed features.
     * @return A vector of pairs representing analyzed features.
     */
    virtual std::vector<std::pair<int, int>> getanalyzeFeatures() const = 0;

    /**
     * @brief Pure virtual method to be implemented by derived classes for getting the output image.
     * @return The output image containing detected features.
     */
    virtual cv::Mat getOutputImage() const = 0;

    /**
     * @brief Get the file path of the image (example file path for demonstration purposes).
     * @return The file path of the image.
     */
    std::string getFilePath();

    /**
     * @brief Perform common image operations such as filtering noise, rescaling, converting to grayscale, and applying bilateral filtering.
     */
    void commonOperations();

    /**
     * @brief Write the detected features (lines or corners) to a specified file.
     * @param filename The name of the file to write features to.
     */
    void writeFeaturesToFile(const std::string& filename) const;

    /**
     * @brief Save the output image containing detected features to a specified file.
     * @param filename The name of the file to save the output image to.
     */
    void saveOutputImage(const std::string& filename) const;

    /**
     * @brief Merge detected features (lines and corners) from LineDetection and CornerDetection into a single image.
     * @return The merged image containing both lines and corners.
     */
    cv::Mat combineLineAndCornerPlot();
};
