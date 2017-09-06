#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

/*****************************************************************************/

/*
 * Developed with help from the following tutorial :
 * http://docs.opencv.org/2.4/doc/tutorials/core/discrete_fourier_transform/discrete_fourier_transform.html
 */

void task (const cv::Mat& img)
{   
    const cv::Mat float_img = cv::Mat_<float> (img) / 255;
    
    cv::imshow ("Original Image", float_img);
    
    // Computing the DFT
    cv::Mat complexI;
    cv::dft (float_img, complexI, cv::DFT_COMPLEX_OUTPUT);
    
    cv::Mat planes[2];

    cv::split (complexI, planes); // Splitting into real and imaginary planes
    
    // Computing the magnitude of frequency specturm
    cv::Mat magnitude;
    cv::magnitude (planes[0], planes[1], magnitude);
    
    // Scaling the magnitude of frequency spectrum
    cv::Mat log_mag;
    cv::log (magnitude + 1, log_mag);
    
    /*
     * Swapping of quadrants so that F (0, 0) is at center.
     * 
     * Top-Right quadrant must be swapped with Bottom-Left.
     * Top-Left quadrant must be swapped with Bottom-Right.
     */
    
    /*
     * x1, x2, y1, y2 are required to deal with odd or even values for row
     * and column sizes.
     * 
     * We have : x1 + x2 = length
     *           y1 + y2 = breadth
     */
    
    const int x1 = (log_mag.cols + 1) / 2;
    const int y1 = (log_mag.rows + 1) / 2;
    
    const int x2 = log_mag.cols / 2;
    const int y2 = log_mag.rows / 2;
    
    // Setting up ROIs (Regions of Interest)    
    cv::Mat q0 (log_mag, cv::Rect(0,  0,  x1, y1)); // Top-Left
    cv::Mat q1 (log_mag, cv::Rect(x1, 0,  x2, y1)); // Top-Right
    cv::Mat q2 (log_mag, cv::Rect(0,  y1, x1, y2)); // Bottom-Left
    cv::Mat q3 (log_mag, cv::Rect(x1, y1, x2, y2)); // Bottom-Right
    
    cv::Mat tmp;
    q0.copyTo (tmp);
    q3.copyTo (q0);
    tmp.copyTo (q3);

    q1.copyTo (tmp);
    q2.copyTo (q1);
    tmp.copyTo (q2);
    
    // Mapping log (log (|G(jw_x, jw_y)| + 1) between 0 and 1
    cv::normalize (log_mag, log_mag, 0, 1, cv::NORM_MINMAX);
    
    // Plotting scaled version of magnitude of frequency spectrum
    cv::imshow ("Plot of scaled version of log (|G(jw_x, jw_y)| + 1)",
                log_mag);
    
    /***************** PART 2 ****************************/
    /*
     * Obtaining inverse of only the phase component
     */
    
    auto it_real = planes[0].begin<float>();
    auto it_imag = planes[1].begin<float>();
    
    auto it_mag = magnitude.begin<float>();
    
    const auto it_real_end = planes[0].end<float>();
    
    // Divinding each frequency component by its magnitude to
    // to obtain the phase part.
    while (it_real != it_real_end) {
    
        *it_real /= *it_mag;
        *it_imag /= *it_mag;
        
        ++it_real; ++it_imag; ++it_mag;
    }
    
    
    // Computing the inverse DFT
    cv::Mat phase_val, inv_phase;
    cv::merge (planes, 2, phase_val);
    cv::dft (phase_val, inv_phase,
             cv::DFT_INVERSE | cv::DFT_SCALE);    
    
    cv::split (inv_phase, planes);
    
    // Computing magitude of the inverse DFT
    cv::Mat magnitude_inv_phase;
    cv::magnitude (planes[0], planes[1], magnitude_inv_phase);
    
    // Scaling the magnitude of the inverse DFT
    cv::normalize (magnitude_inv_phase, magnitude_inv_phase,
                   0, 1, cv::NORM_MINMAX);
    
    // Plotting of the magnitude of the inverse DFT
    cv::imshow ("Plot of inverse of the phase only spectrum",
                magnitude_inv_phase);
    
    /***************** PART 1 ****************************/
    /*
     * Obtaining inverse of only the magnitude component
     */
    
    // Computing the inverse DFT
    cv::Mat inv_mag;
    cv::dft (magnitude, inv_mag,
             cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
    
    cv::split (inv_mag, planes);
    
    // Computing magitude of the inverse DFT
    cv::Mat magnitude_inv_mag;
    cv::magnitude (planes[0], planes[1], magnitude_inv_mag);
    
    // Plotting of the magnitude of the inverse DFT
    cv::imshow ("Plot of inverse of the magnitude  only spectrum",
                magnitude_inv_mag);   
}

/*****************************************************************************/

int main (int argc, char** argv)
{
    if (argc != 2) {
    
        std::cout << "Please input image path" << std::endl;
        return 0;
    }
    
    cv::Mat img = cv::imread (argv[1], cv::IMREAD_GRAYSCALE);
    const int N = img.rows * img.cols;
    
    if (!N) {
    
        std::cerr << "Unable to load the image. "
                  << "Please enter correct path"
                  << std::endl;
                  
        return -1;
    }
    
    task (img);
    
    std::cout << "Press 'q' to exit" << std::endl;
    
    while ('q' != cv::waitKey (1));
    
    return 0;
}

/*****************************************************************************/
/*****************************************************************************/