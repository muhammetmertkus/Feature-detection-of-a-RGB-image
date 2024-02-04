/* *******************************************************
 * Filename		:	LineDetection.h
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	LineDetection Class Header
 * ******************************************************/

#pragma once
#include "Detection.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>

 /**
  * @brief The LineDetection class.
  *
  * A derived class from the Detection base class, specializing in detecting and visualizing lines in an image.
  */
class LineDetection : public Detection {
private:
    cv::Mat output;         ///< Output image containing detected lines

    int threshold;          ///< Threshold for line detection
    std::vector<cv::Vec4i> lines;   ///< Detected lines in the image
    cv::Mat edges;          ///< Image edges after Canny edge detection
    cv::Mat cannyOutput;    ///< Temporary storage for Canny output
    std::vector<cv::Vec4i> tempLines;  ///< Temporary storage for detected lines

    cv::Mat visualization;  ///< Image used for visualization purposes

    /**
     * @brief Calculate the length of a line.
     *
     * @param line The line represented by four coordinates.
     * @return The length of the line.
     */
    double calculateLineLength(const cv::Vec4i& line) const;

    /**
     * @brief Calculate the angle of a line.
     *
     * @param line The line represented by four coordinates.
     * @return The angle of the line.
     */
    double calculateLineAngle(const cv::Vec4i& line) const;

    /**
     * @brief Merge lines that are close to each other.
     */
    void mergeLines();

public:
    /**
     * @brief Constructor for the LineDetection class.
     *
     * @param filename The filename of the image to be processed.
     */
    LineDetection(const std::string& filename);

    /**
     * @brief Destructor for the LineDetection class.
     */
    ~LineDetection() {}

    /**
     * @brief Set the threshold value for line detection.
     *
     * @param value The threshold value.
     */
    void setThreshold(int value);

    /**
     * @brief Get the threshold value for line detection.
     *
     * @return The threshold value.
     */
    int getThreshold() const;

    /**
     * @brief Implement the abstract method for line detection.
     */
    void analyzeFeatures() override;

    /**
     * @brief Implement the abstract method for visualizing detected lines.
     */
    void plotFeatures() const override;

    /**
     * @brief Implement the abstract method for getting features' coordinates.
     *
     * @return A vector of pairs representing the coordinates of detected lines.
     */
    std::vector<std::pair<int, int>> getanalyzeFeatures() const override;

    /**
     * @brief Implement the abstract method for getting the output image.
     *
     * @return The output image containing detected lines.
     */
    cv::Mat getOutputImage() const override;

    /**
     * @brief Overloaded stream insertion operator to output LineDetection information.
     *
     * @param os The output stream.
     * @param ld The LineDetection object to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const LineDetection& ld);
};
