#include "../include/histogram_matching.h"

#include <opencv2/core/core.hpp>

#include <iostream>
#include <array>
#include <cstdint>
#include <algorithm>

/*****************************************************************************/

constexpr int L = EE604A::L;
constexpr int L_max = EE604A::L_max; 

/*****************************************************************************/

void
plot_histogram (const auto& hist, const char* plot_title = "")
{
    constexpr long long MAX = 60;

    const int max = *std::max_element (hist.cbegin(), hist.cend());
    
    std::cout << plot_title << std::endl;
    for (const auto& p : hist) {
        
        assert (max);
        const int val = (p * MAX) / max;
        
        std::cout << p << "\t|";
        
        for (int i = 0; i < val; ++i)
            std::cout << '*';
       
        std::cout << std::endl;
    }
    
    for (int i = 0; i < MAX; ++i)
        std::cout << '-';
    std::cout << std::endl;
}

/*****************************************************************************/

cv::Mat
EE604A::histogram_matching (const cv::Mat& tar, const cv::Mat& ref, bool plot)
{
    typedef uint8_t pixel_t;
    
    std::array<int, L> tar_hist, ref_hist;
    std::array<int, L> T_tar, T_ref;
    
    std::array<int, L> T;
    
    const int N_tar = tar.rows * tar.cols;
    const int N_ref = ref.rows * ref.cols;
    
    tar_hist.fill (0);
    ref_hist.fill (0);
    
    /***** Constructing Histograms ***********************/
    
    for (auto it = ref.begin<pixel_t>(); it != ref.end<pixel_t>(); ++it)
        ++ref_hist[*it];
    
    for (auto it = tar.begin<pixel_t>(); it != tar.end<pixel_t>(); ++it)
        ++tar_hist[*it];
    
    /***** Constructing CDFs *****************************/
    
    long long sum = 0;
    for (int idx = 0; idx < tar_hist.size(); ++idx) {
        
        sum += tar_hist[idx] * L_max;
        T_tar[idx] = sum / N_tar;
    }
    
    sum = 0;
    for (int idx = 0; idx < ref_hist.size(); ++idx) {
    
        sum += ref_hist[idx] * L_max;
        T_ref[idx] = sum / N_ref;
    }
    
    /***** Finding inverse *******************************/
    
    int idx2 = 0;
    for (int idx1 = 0; idx1 < tar_hist.size(); ++idx1) {
        
        while (T_tar[idx1] > T_ref[idx2])
            ++idx2;
        
        T[idx1] = idx2;
    }
    
    /***** Matching the target image *********************/
    
    std::array<int, L> matched_hist;
    matched_hist.fill (0);
    
    cv::Mat matched_tar = tar.clone();
    for (auto it = matched_tar.begin<pixel_t>();
              it != matched_tar.end<pixel_t>();
            ++it) {
         
        *it = T[*it];
        ++matched_hist[*it];
    }
    
    /***** Plotting the histograms ***********************/
    
    if (plot) {
        
        plot_histogram (ref_hist,       "Reference Histogram");
        plot_histogram (tar_hist,       "Target Histogram");
        plot_histogram (matched_hist,   "matched_tar");
    }
    
    return matched_tar;
}

/*****************************************************************************/
/*****************************************************************************/