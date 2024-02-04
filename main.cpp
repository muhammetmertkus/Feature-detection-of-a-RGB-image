/* *******************************************************
 * Filename		:	main.cpp
 * Author		:	Muhammet Mert KUÞ
 * Date			:	05.01.2024
 * Description	:	Main Program
 * ******************************************************/


#include "LineDetection.h"
#include "CornerDetection.h"
#include <iostream>
int main() {
    try {
        // Specify the file path of the image to be processed.
        std::string imagePath = "color.png";

        // Create instances of LineDetection and CornerDetection classes and associate them with the input image.
        LineDetection lineDetection(imagePath);
        CornerDetection cornerDetection(imagePath);

        // Perform line detection operations
        lineDetection.analyzeFeatures();
        std::cout << "\nLine Detection Results:\n" << lineDetection;
        lineDetection.plotFeatures();
        lineDetection.writeFeaturesToFile("lines_features.txt");
        lineDetection.saveOutputImage("lines_output.png");

        // Perform corner detection operations
        cornerDetection.analyzeFeatures();
        std::cout << "\nCorner Detection Results:\n" << cornerDetection;
        cornerDetection.plotFeatures();
        cornerDetection.writeFeaturesToFile("corners_features.txt");
        cornerDetection.saveOutputImage("corners_output.png");

        // Show line and corner plot
        lineDetection.combineLineAndCornerPlot();

    }
    catch (const std::exception& ex) {
        // Handle exceptions and print error messages.
        std::cerr << "An exception has occurred: " << ex.what() << std::endl;
        return -1;
    }

    return 0;
}