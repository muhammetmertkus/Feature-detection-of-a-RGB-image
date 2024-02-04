/* *******************************************************
 * Filename		:	Detection.cpp
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	Detection Class Implementation
 * ******************************************************/

#include "Detection.h"
#include "LineDetection.h"
#include "CornerDetection.h"

 /**
  * @brief Constructor for the Detection class.
  *
  * Initializes the Detection class by invoking the base class constructor (CommonProcesses).
  *
  * @param filename The filename of the image to be processed.
  */
Detection::Detection(const std::string& filename) : CommonProcesses(filename) {
}

/**
 * @brief Perform common image operations.
 *
 * This method applies common image processing operations such as filtering noise, rescaling,
 * converting to grayscale, and applying bilateral filtering.
 */
void Detection::commonOperations() {
    filterNoise();
    rescale(800, 600);
    convertToGrays();
    denoiseBilateralFilter();
}

/**
 * @brief Write the detected features to a specified file.
 *
 * Writes the detected features (lines or corners) to the specified file.
 *
 * @param filename The name of the file to write the features to.
 */
void Detection::writeFeaturesToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the file for writing: " << filename << std::endl;
        throw std::runtime_error("Could not open the file for writing: " + filename);
    }

    const std::vector<std::pair<int, int>>& features = getanalyzeFeatures();
    for (const std::pair<int, int>& feature : features) {
        outFile << feature.first << "," << feature.second << "\n";
        if (outFile.fail()) {
            std::cerr << "Error: Failed to write data to file: " << filename << std::endl;
            throw std::runtime_error("Failed to write data to file: " + filename);
        }
    }

    std::cout << "Features written to file successfully: " << filename << std::endl;
}


/**
 * @brief Save the output image containing detected features to a specified file.
 *
 * Saves the output image, which contains the detected features, to the specified file.
 *
 * @param filename The name of the file to save the image to.
 */
void Detection::saveOutputImage(const std::string& filename) const {
    cv::imwrite(filename, getOutputImage());
    std::cout << "Image saved successfully: " << filename << std::endl;
}

/**
 * @brief Get the file path.
 *
 * Retrieves the file path for demonstration purposes.
 *
 * @return The file path.
 */
std::string Detection::getFilePath() {
    std::string filePath = "color.png";

    return filePath;
}

/**
 * @brief Merge detected features from LineDetection and CornerDetection into a single image.
 *
 * Combines the detected features (lines and corners) from LineDetection and CornerDetection into a single image.
 *
 * @return The combined image.
 */
cv::Mat Detection::combineLineAndCornerPlot() {
    LineDetection lineDetection(getFilePath());
    CornerDetection cornerDetection(getFilePath());

    lineDetection.analyzeFeatures();
    cornerDetection.analyzeFeatures();

    std::vector<std::pair<int, int>> lineFeatures = lineDetection.getanalyzeFeatures();
    std::vector<std::pair<int, int>> cornerFeatures = cornerDetection.getanalyzeFeatures();

    cv::Mat combinedImage = lineDetection.getOutputImage().clone();

    // Draw lines detected by LineDetection on the combined image.
    for (const std::pair<int, int>& lineFeature : lineFeatures) {
        cv::circle(combinedImage, cv::Point(lineFeature.first, lineFeature.second), 3, cv::Scalar(0, 255, 0), -1);
    }

    // Draw corners detected by CornerDetection on the combined image.
    for (const std::pair<int, int>& cornerFeature : cornerFeatures) {
        cv::circle(combinedImage, cv::Point(cornerFeature.first, cornerFeature.second), 3, cv::Scalar(255, 0, 0), -1);
    }

    // Save the combined image containing merged features to a file.
    std::string savePath = "merged_features.png";
    cv::imwrite(savePath, combinedImage);

    // Display the combined image
    cv::imshow("Combined Features", combinedImage);
    cv::waitKey(0);
    return combinedImage;
}
