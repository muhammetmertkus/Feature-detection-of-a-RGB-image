/* *******************************************************
 * Filename		:	CornerDetection.cpp
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	CornerDetection Class Implementation
 * ******************************************************/

#include "CornerDetection.h"
#include <iomanip>
#include <cmath>
#include "LineDetection.h"
#include "Detection.h"

 // Constructor that takes the filename of an image and initializes default parameters.
CornerDetection::CornerDetection(const std::string& filename) : Detection(filename), qualityLevel(0.01), minDistance(10), blockSize(3), useHarrisDetector(false), k(0.04) {}

/** Set the quality level for corner detection using the Shi-Tomasi method.
 *  The quality level is a parameter specifying the minimal accepted quality of corners.
 *  Higher values result in fewer corners being detected.
 *  @param level The quality level to be set.
 */
void CornerDetection::setQualityLevel(double level)
{

    qualityLevel = level;
}

/** Set the minimum distance between corners for corner detection.
 *  The minimum distance is the minimum possible Euclidean distance between the returned corners.
 *  @param distance The minimum distance to be set.
 */
void CornerDetection::setMinDistance(double distance)
{

    minDistance = distance;
}

/** Set the size of the neighborhood considered for corner detection.
 *  The blockSize parameter is the size of the average block for computing the derivative covariance matrix over each pixel neighborhood.
 *  @param size The size of the neighborhood to be set.
 */
void CornerDetection::setBlockSize(int size)
{

    blockSize = size;
}

/** Set whether to use the Harris corner detector for corner detection.
  *  The Harris detector is a more complex corner detection algorithm.
  *  @param useHarris Boolean indicating whether to use the Harris detector.
  */
void CornerDetection::setUseHarrisDetector(bool useHarris)
{
 
    useHarrisDetector = useHarris;
}

/** Set the free parameter (k) for the Harris corner detector.
 *  The k parameter is a free parameter for the Harris detector, typically in the range [0.04, 0.06].
 *  @param kValue The value of the free parameter to be set.
 */void CornerDetection::setK(double kValue)
{

    k = kValue;
}

//  perform corner detection using the Shi-Tomasi method.
void CornerDetection::analyzeFeatures()
{
    // Common image processing operations from the base class
    commonOperations();

    // Perform corner detection using the Shi-Tomasi method
    cv::goodFeaturesToTrack(getRGBPic(), corners, 200, qualityLevel, minDistance, cv::Mat(), blockSize, useHarrisDetector, k);

    // Create an output image and convert it to BGR for visualization
    output = getRGBPic().clone();
    cv::cvtColor(output, output, cv::COLOR_GRAY2BGR);

    // Visualize the detected corners on the output image
    for (const cv::Point2f& corner : corners) {
        cv::circle(output, corner, 5, cv::Scalar(0, 255, 0), -1);
    }
}

/** Get the output image with visualized corner features.
 *  @return A clone of the output image with corners visualized.
 */cv::Mat CornerDetection::getOutputImage() const
 {


    return output.clone();
}

// Method to get the coordinates of detected corners.
std::vector<std::pair<int, int>> CornerDetection::getanalyzeFeatures() const {
    std::vector<std::pair<int, int>> coordList;
    for (const cv::Point2f& corner : corners) {
        // emplace_back, unlike push_back, directly constructs the element in the memory of the vector without copying existing elements in the vector.
        coordList.emplace_back(static_cast<int>(corner.x), static_cast<int>(corner.y));
    }
    return coordList;
}


// Method to visualize detected corners.
void CornerDetection::plotFeatures() const
{
    // Display the image with visualized corners
    cv::imshow("Detected Corners", output);
    cv::waitKey();
}

/*
 * Overloaded stream insertion operator to display the detected corner information.
 * Outputs the index and coordinates of each detected corner in the CornerDetection class.
 */
std::ostream& operator<<(std::ostream& os, const CornerDetection& cd)
{
    os << "Detected Corner Information:\n";

    for (size_t i = 0; i < cd.corners.size(); ++i) {
        os << "Corner " << i + 1 << ":\n";
        os << "  Coordinates: (" << cd.corners[i].x << ", " << cd.corners[i].y << ")\n";
        os << "-------------------------\n";
    }
    os << "Number of Corners: " << cd.corners.size() << "\n";
    return os;
}
