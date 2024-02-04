# Feature Detection of an RGB Image - Object-Oriented Programming Project

This repository contains my implementation for the "Feature Detection of a RGB Image" project as part of the Object-Oriented Programming I course during the 2023-2024 Fall semester.

## Project Overview

The goal of this project was to implement a console-based application for detecting features (lines and corners) in an RGB image using OpenCV. The project follows object-oriented programming principles and includes a class hierarchy with four classes: `CommonProcesses`, `Detection`, `LineDetection`, and `CornerDetection`. The grading criteria include class design, code quality, documentation, and functionality.

## Implemented Features

- **CommonProcesses (Base Class):**
  - Raw RGB data storage, viewer, and various image processing operations.
  
- **Detection (Base Class):**
  - Feature writing to a file.
  - Visualization of lines or corners.
  
- **Line Detection (Derived from Detection):**
  - Specific functionalities for line detection.
  
- **Corner Detection (Derived from Detection):**
  - Specific functionalities for corner detection.

## Requirements Met

- Private data members for all classes.
- Constructors and destructors for each class.
- Member initializer and base class member initializer usage.
- Data member validation using exception handling.
- Get and set functions for data members.
- Access and utility functions implementation.
- Print functions or overloaded stream insertion operator (<<).
- Const qualifier, static storage class, and reference parameters usage.
- Dynamic memory allocation or STL container and algorithm usage.
- Composition and/or inheritance application.


## How to Run

1. Clone the repository.
2. Compile the source code using a C++ compiler.
3. Execute the compiled program in the console.



## References

- [OpenCV](https://opencv.org/)
- [Canny Method Tutorial](https://docs.opencv.org/4.x/da/d5c/tutorial_canny_detector.html)
- [Harris Method Tutorial](https://docs.opencv.org/4.x/d4/d7d/tutorial_harris_detector.html)

Feel free to explore the code and reach out for any questions or feedback!
