#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "../include/pixel_nlm.h"

/*****************************************************************************/

constexpr float sigma = 0.01;
constexpr float multiplier = 10;

/*****************************************************************************/

void task (const cv::Mat& img)
{
    const auto& float_img = cv::Mat_<float> (img) / 255;
    cv::Mat output = cv::Mat::zeros (img.rows, img.cols, CV_32F);
    
    cv::randn (output,
               0,
               sigma);
    
    const auto& gauss_img = float_img + output;
    const auto& denoised_img = EE604A::pixel_nlm (gauss_img,
                                                  sigma * multiplier);
    
    cv::imshow ("Original Image", float_img);
    cv::imshow ("Image with Gaussian Noise", gauss_img);
    cv::imshow ("Denoised Image using Pixel-wise Non Local Means", denoised_img);
}

/*****************************************************************************/

int main (int argc, char** argv)
{
    if (argc != 2) {
    
        std::cout << "Please input image path" << std::endl;
        return 0;
    }
    
    const auto& img = cv::imread (argv[1], cv::IMREAD_GRAYSCALE);
    task (img);
    
    std::cout << "Press 'q' to exit" << std::endl;
    
    while ('q' != cv::waitKey (1));
    
    return 0;
}

/*****************************************************************************/
/*****************************************************************************/