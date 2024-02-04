/* *******************************************************
 * Filename		:	CornerDetection.h
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	CornerDetection Class Header
 * ******************************************************/

#pragma once

#include "Detection.h"
#include <opencv2/imgproc.hpp>
#include <vector>
#include <fstream>

 /**
  * @brief The CornerDetection class is a derived class from the Detection base class.
  * It specializes in detecting and visualizing corners in an image.
  */
class CornerDetection : public Detection {
protected:
    // Output image with visualized corner features

private:
    cv::Mat output;
    std::vector<cv::Point2f> corners;  // Detected corner points
    double qualityLevel;  // Quality level parameter for corner detection
    double minDistance;  // Minimum distance between corners
    int blockSize;  // Size of the neighborhood considered for corner detection
    bool useHarrisDetector;  // Flag indicating whether to use Harris corner detector
    double k;  // Free parameter for the Harris detector

public:
    /**
     * @brief Constructor that initializes a CornerDetection object with the given filename.
     *
     * @param filename The filename of the image.
     */
    CornerDetection(const std::string& filename);

    /**
     * @brief Destructor for the CornerDetection class.
     */
    ~CornerDetection() {}

    /**
     * @brief Setter function to set the quality level parameter for corner detection.
     *
     * @param level The quality level parameter.
     */
    void setQualityLevel(double level);

    /**
     * @brief Setter function to set the minimum distance between corners.
     *
     * @param distance The minimum distance between corners.
     */
    void setMinDistance(double distance);

    /**
     * @brief Setter function to set the size of the neighborhood considered for corner detection.
     *
     * @param size The size of the neighborhood.
     */
    void setBlockSize(int size);

    /**
     * @brief Setter function to set whether to use Harris corner detector.
     *
     * @param useHarris Flag indicating whether to use Harris corner detector.
     */
    void setUseHarrisDetector(bool useHarris);

    /**
     * @brief Setter function to set the free parameter for the Harris detector.
     *
     * @param kValue The free parameter.
     */
    void setK(double kValue);

    /**
     * @brief Overridden function to detect corner features in the image.
     */
    void analyzeFeatures();

    /**
     * @brief Function to retrieve the output image with visualized corner features.
     *
     * @return cv::Mat The output image with visualized corners.
     */
    cv::Mat getOutputImage() const override;

    /**
     * @brief Function to retrieve the coordinates of detected corner features.
     *
     * @return std::vector<std::pair<int, int>> A vector containing pairs of x, y coordinates of detected corners.
     */
    std::vector<std::pair<int, int>> getanalyzeFeatures() const override;

    /**
     * @brief Overridden function to visualize detected corner features.
     */
    void plotFeatures() const override;

    /**
     * @brief Overloaded stream insertion operator to display the detected corner information.
     *
     * @param os The output stream.
     * @param cd The CornerDetection object.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const CornerDetection& cd);

};
