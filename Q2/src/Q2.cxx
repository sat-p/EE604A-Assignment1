#include "../include/histogram_matching.h"

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

int main (int argc, char** argv)
{
    if (argc != 3) {
    
        std::cout << "Please input reference and target image path" << std::endl;
        return 0;
    }
    
    const auto& tar = cv::imread (argv[2], cv::IMREAD_GRAYSCALE);
    const auto& ref = cv::imread (argv[1], cv::IMREAD_GRAYSCALE);
    
    // Obtaining the matched_image without printing of the histograms
    const auto& matched_tar = EE604A::histogram_matching (tar, ref, false);
    
    // Obtaining the matched_image and printing of the histograms
//     const auto& matched_tar = EE604A::histogram_matching (tar, ref, true);
    
    cv::imshow ("Reference Image", ref);
    cv::imshow ("Target Image", tar);
    
    cv::imshow ("Matched Target Image", matched_tar);
    
    std::cout << "Press 'q' to exit" << std::endl;
    
    while ('q' != cv::waitKey (1));
    
    return 0;
}