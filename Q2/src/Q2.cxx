#include "../include/histogram_matching.h"

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

int main (int argc, char** argv)
{
    if (argc != 3) {
    
        std::cout << "Please input reference and target image path" << std::endl;
        return 0;
    }
    
    cv::Mat ref = cv::imread (argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat tar = cv::imread (argv[2], cv::IMREAD_GRAYSCALE);
    
    /*
     * Obtaining the matched_image without printing of the histograms
     */
    cv::Mat matched_tar = EE604A::histogram_matching (tar, ref, true);
    
    /*
     * Obtaining the matched_image and printing of the histograms
     */
//     cv::Mat matched_tar = EE604A::histogram_matching (tar, ref, false);
    
    cv::imshow ("Reference Image", ref);
    cv::imshow ("Target Image", tar);
    
    cv::imshow ("Matched Target Image", matched_tar);
    
    std::cout << "Press 'q' to exit" << std::endl;
    
    while ('q' != cv::waitKey (1));
    
    return 0;
}