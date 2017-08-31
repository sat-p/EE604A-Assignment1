#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "../include/pixel_nlm.h"

/*****************************************************************************/

// Parameters for gaussian case
constexpr float sigma = 0.01;
constexpr float multiplier = 10;

// Parameters for impulse case
constexpr float a = -0.5;
constexpr float p_a = 0.01;
constexpr float b = 0.5;
constexpr float p_b = 0.01;
constexpr float p_noise = p_a + p_b;
constexpr float h = 0.1;

/*****************************************************************************/

void task (const cv::Mat& img)
{
    const cv::Mat& float_img = cv::Mat_<float> (img) / 255;
    
    /**** GAUSSIAN NOISE *********************************/
    
    cv::Mat eta = cv::Mat::zeros (img.rows, img.cols, CV_32F);
    
    cv::randn (eta,
               0,
               sigma);
    
    const auto& gauss_img = float_img + eta;
    const auto& denoised_gauss_img = EE604A::pixel_nlm (gauss_img,
                                                  sigma * multiplier);
    
    /**** IMPULSE NOISE **********************************/
    
    cv::RNG rng;
    
    cv::Mat_<float> impulse_img = float_img.clone();
    
    for (auto it = impulse_img.begin(); it != impulse_img.end();
         ++it) {
        
        const float p = rng.uniform (0.f, 1.f);
        
        if (p < p_a)
            *it += a;
        else if (p < p_noise)
            *it += b;
        else
            continue;
        
        if (*it < 0)
            *it = 0;
        else if (*it > 1)
            *it = 1;
    }
    
    const auto& denoised_impulse_img = EE604A::pixel_nlm (impulse_img,
                                                          h);
    
    /**** Plotting ***************************************/
    
    cv::imshow ("Original Image", float_img);
    
    cv::imshow ("Image with Gaussian Noise", gauss_img);
    cv::imshow ("Denoised Gaussian noise Image using Pixel-wise Non Local Means",
                denoised_gauss_img);
    
    cv::imshow ("Image with Impulse Noise", impulse_img);
    cv::imshow ("Denoised Impulse Noise Image using Pixel-wise Non Local Means",
                denoised_impulse_img);
    
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