#ifndef __EE604A_HISTOGRAM_MATCHING__
#define __EE604A_HISTOGRAM_MATCHING__

#include <opencv2/core/core.hpp>

namespace EE604A {
    
constexpr int L = 256;       // Number of quantization levels, 2^8 = 256
constexpr int L_max = L - 1; //Levels are assumed to be [0, L -1]
    
cv::Mat
histogram_matching (const cv::Mat& tar, const cv::Mat& ref, bool plot = false);

}; // namespace EE604A

#endif