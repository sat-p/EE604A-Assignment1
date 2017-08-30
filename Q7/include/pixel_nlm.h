#ifndef __EE604A_PIXEL_NLM__
#define __EE604A_PIXEL_NLM__

#include <opencv2/core/core.hpp>

namespace EE604A {

cv::Mat_<float>
pixel_nlm (const cv::Mat_<float>& img, const float h);
    
}; // namespace EE604A
#endif