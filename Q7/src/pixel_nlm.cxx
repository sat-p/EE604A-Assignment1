#include "../include/pixel_nlm.h"

#include <cmath>

/*****************************************************************************/

cv::Mat_<float>
EE604A::pixel_nlm (const cv::Mat_<float>& img, const float h)
{
    const float h2_inv = 1 / (2 * h * h);
    
    auto denoised_img = img.clone();
    
    for (auto pixel  = denoised_img.begin(); pixel != denoised_img.end();
            ++pixel) {
    
        float weight_sum = 0;
        float sum = 0;
        
        for (auto orig_pixel  = img.begin(); orig_pixel != img.end(); 
                ++orig_pixel) {
            
            const float diff = *pixel - *orig_pixel;
            const float weight = std::exp (-diff * diff * h2_inv);
            
            sum += *orig_pixel * weight;
            weight_sum += weight;
        }
        
        *pixel = sum / weight_sum;
    }
    
    return denoised_img;
}

/*****************************************************************************/
/*****************************************************************************/