#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

/*****************************************************************************/

constexpr double sigma = 0.01;

/*****************************************************************************/

void task (const cv::Mat& img)
{
    const cv::Mat& float_img = cv::Mat_<float> (img) / 255;
    cv::Mat output = cv::Mat::zeros (img.rows, img.cols, CV_32F);
    cv::randn (output,
               0,
               sigma);
    
    cv::Mat gauss_img = float_img + output;
    
    cv::imshow ("Original Image", float_img);
    cv::imshow ("Image with Gaussian Noise", gauss_img);
    
    
}

/*****************************************************************************/

int main (int argc, char** argv)
{
    if (argc != 2) {
    
        std::cout << "Please input image path" << std::endl;
        return 0;
    }
    
    cv::Mat img = cv::imread (argv[1], cv::IMREAD_GRAYSCALE);
    task (img);
    
    std::cout << "Press 'q' to exit" << std::endl;
    
    while ('q' != cv::waitKey (1));
    
    return 0;
}

/*****************************************************************************/
/*****************************************************************************/