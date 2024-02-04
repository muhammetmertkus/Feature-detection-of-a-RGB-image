/* *******************************************************
 * Filename		:	LineDetection.cpp
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	LineDetection Class Implementation
 * ******************************************************/

#include "LineDetection.h"
#include "CornerDetection.h"

#include <iomanip>
#include <cmath>

 /**
  * @brief Constructor that takes the filename of an image.
  *
  * @param filename The filename of the image.
  */
LineDetection::LineDetection(const std::string& filename) : Detection(filename), threshold(10) {}

/**
 * @brief Setter for the threshold value.
 *
 * @param value The threshold value for line detection.
 */
void LineDetection::setThreshold(int value) {
    threshold = value;
}

/**
 * @brief Getter for the threshold value.
 *
 * @return int The current threshold value for line detection.
 */
int LineDetection::getThreshold() const {
    return threshold;
}

/**
 * @brief Get the output image containing detected lines.
 *
 * @return cv::Mat The output image with detected lines.
 */
cv::Mat LineDetection::getOutputImage() const {
    return output.clone();
}

/**
 * @brief Calculate the length of a line segment.
 *
 * @param line The vector representing the line segment.
 * @return double The length of the line segment.
 */
double LineDetection::calculateLineLength(const cv::Vec4i& line) const {
    cv::Point pt1(line[0], line[1]);
    cv::Point pt2(line[2], line[3]);
    return cv::norm(pt1 - pt2);
}

/**
 * @brief Calculate the angle of a line segment.
 *
 * @param line The vector representing the line segment.
 * @return double The angle of the line segment in degrees.
 */
double LineDetection::calculateLineAngle(const cv::Vec4i& line) const {
    cv::Point pt1(line[0], line[1]);
    cv::Point pt2(line[2], line[3]);
    return std::atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;
}

/**
 * @brief Merge lines that are similar in angle and close in distance.
 *
 * This function applies a merging strategy to similar lines based on angle and distance.
 */
void LineDetection::mergeLines() {
    // Thresholds for merging lines
    const double angleThreshold = CV_PI / 180.0 * 8.0;  // Maximum allowed angle difference for merging lines
    const double distanceThreshold = 10.0;  // Maximum allowed distance between lines for merging

    std::vector<cv::Vec4i> mergedLines;

    for (size_t i = 0; i < lines.size(); ++i) {
        cv::Vec4i line1 = lines[i];
        cv::Point pt1(line1[0], line1[1]);
        cv::Point pt2(line1[2], line1[3]);

        // Check line length
        double length1 = cv::norm(pt1 - pt2);

        for (size_t j = i + 1; j < lines.size(); ++j) {
            cv::Vec4i line2 = lines[j];
            cv::Point pt3(line2[0], line2[1]);
            cv::Point pt4(line2[2], line2[3]);

            // Check line length
            double length2 = cv::norm(pt3 - pt4);

            // Check angle difference
            double angleDiff = std::abs(std::atan2(pt2.y - pt1.y, pt2.x - pt1.x) -
                std::atan2(pt4.y - pt3.y, pt4.x - pt3.x));

            if (angleDiff > angleThreshold) {
                continue;  // Do not merge if angles are not close
            }

            // Check average point and distance
            cv::Point midPoint1 = (pt1 + pt2) * 0.5;
            cv::Point midPoint2 = (pt3 + pt4) * 0.5;

            double distance = cv::norm(midPoint1 - midPoint2);
            if (distance > distanceThreshold) {
                continue;  // Do not merge if points are not close
            }

            // Create a merged line
            mergedLines.push_back(cv::Vec4i(pt1.x, pt1.y, pt4.x, pt4.y));

            // Mark the merged lines to avoid re-merging
            lines.erase(lines.begin() + j);
            lines.erase(lines.begin() + i);
            --j;
        }
    }

    // Append merged lines to the original vector
    lines.insert(lines.end(), mergedLines.begin(), mergedLines.end());
}

/**
 * @brief Implement the abstract method for line detection.
 *
 * This function performs line detection using Canny edge detection and Hough Lines.
 */
void LineDetection::analyzeFeatures() {
    commonOperations();

    // Canny edge detection
    cv::Mat edges;
    cv::Canny(getRGBPic(), edges, getThreshold(), getThreshold() * 3, 3);

    // Probabilistic Hough Transform for line detection
    cv::HoughLinesP(edges, tempLines, 0.1, CV_PI / 180, 3, 15, 10);

    lines = tempLines;
    mergeLines();

    cannyOutput = edges;

    // Visualization image resizing
    visualization = getOrginalPic().clone();
    cv::resize(visualization, visualization, cv::Size(800, 600));

    // Output image creation
    output = getRGBPic().clone();
    cv::cvtColor(output, output, cv::COLOR_GRAY2BGR);

    // Drawing lines on the output image
    for (size_t i = 0; i < lines.size(); ++i) {
        cv::Vec4i line = lines[i];
        cv::Scalar color = cv::Scalar(0, 255, 0);
        cv::line(output, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), color, 5);
    }
}

/**
 * @brief Implement the abstract method for visualizing detected lines.
 *
 * This function displays the Canny edges, original picture, and detected lines.
 */
void LineDetection::plotFeatures() const {
    cv::imshow("Canny Edges", cannyOutput);
    cv::imshow("Original Picture", visualization);
    cv::imshow("Detected Lines", output);
    cv::waitKey();
}

/**
 * @brief Implement the abstract method for getting features' coordinates.
 *
 * @return std::vector<std::pair<int, int>> A vector containing pairs of x, y coordinates of detected lines.
 */
std::vector<std::pair<int, int>> LineDetection::getanalyzeFeatures() const {
    std::vector<std::pair<int, int>> coordinates;

    for (const cv::Vec4i& line : lines) {
        // Extract coordinates from the cv::Vec4i
        int x1 = line[0];
        int y1 = line[1];
        int x2 = line[2];
        int y2 = line[3];

        // Add the coordinates to the vector
        coordinates.emplace_back(x1, y1);
        coordinates.emplace_back(x2, y2);
    }

    return coordinates;
}


/**
 * @brief Overloaded stream insertion operator to display detailed information about detected lines.
 *
 * @param os The output stream.
 * @param ld The LineDetection object.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const LineDetection& ld) {
    os << "Detailed Line Information:\n";

    // Iterate through each detected line and display its details
    for (size_t i = 0; i < ld.lines.size(); ++i) {
        cv::Vec4i line = ld.lines[i];
        double length = ld.calculateLineLength(line);
        double angle = ld.calculateLineAngle(line);

        os << "Line " << i + 1 << ":\n";
        os << "  Start Point: (" << line[0] << ", " << line[1] << ")\n";
        os << "  End Point:   (" << line[2] << ", " << line[3] << ")\n";
        os << "  Length:      " << length << "\n";
        os << "  Angle:       " << angle << " degrees\n";
        os << "-------------------------\n";
    }
    os << "Detected lines: " << ld.lines.size() << std::endl;

    return os;
}
