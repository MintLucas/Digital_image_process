#include "Lab02_hisBalance.hpp"
#include<iostream>
#include<string>
#include<vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat equalize_hist(Mat& input)
{
    int gray[256] = { 0 };
    double gray_prob[256] = { 0 };
    double gray_distribution[256] = { 0 };
    int gray_equal[256] = { 0 };
    
    int MN = 0;
    Mat output = input.clone();
    MN = input.cols * input.rows;
    
    Mat_<uchar>::iterator it = output.begin<uchar>();
    Mat_<uchar>::iterator end = output.end<uchar>();
    
    for (; it < end; it++)
        gray[*it]++;//统计像素值出现次数
    
    it = output.begin<uchar>();
    for(; it < end; it++)
        gray_prob[*it] = ((double)gray[*it]/MN);//计算PDF

    it = output.begin<uchar>();
    gray_distribution[0] = gray_prob[0];
    for (int i = 1; i < 256; i++)
        //计算cdf
        gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
    
    //映射后的像素值
    for (int i = 0; i < 256; i++)
        gray_equal[i] = (uchar)(255 * gray_distribution[i]);
    
    it = output.begin<uchar>();
    for(; it < end; it++)
        *it = gray_equal[*it];
    
    return output;
}

Mat color_equalize_hist(Mat input)
{
    vector<Mat> channels;
    split(input, channels);
    
    for (int i = 0; i < channels.size(); i++)
        channels[i] = equalize_hist(channels[i]);

    Mat res;
    merge(channels, res);
    return res;
}

int drawHisRGB(Mat image)
{
    int bins = 256;
    int hist_size[] = { bins };
    float range[] = { 0, 256 };
    const float* ranges[] = { range };
    
    MatND hist_r, hist_g, hist_b;
    int channels_r[] = { 0 };
    calcHist(&image, 1, channels_r, Mat(), // do not use mask
             hist_r, 1, hist_size, ranges,
             true, // the histogram is uniform
             false);
    
    int channels_g[] = { 1 };
    calcHist(&image, 1, channels_g, Mat(), // do not use mask
             hist_g, 1, hist_size, ranges,
             true, // the histogram is uniform
             false);
    
    int channels_b[] = { 2 };
    calcHist(&image, 1, channels_b, Mat(), // do not use mask
             hist_b, 1, hist_size, ranges,
             true, // the histogram is uniform
             false);
    
    double max_val_r, max_val_g, max_val_b;
    minMaxLoc(hist_r, 0, &max_val_r, 0, 0);
    minMaxLoc(hist_g, 0, &max_val_g, 0, 0);
    minMaxLoc(hist_b, 0, &max_val_b, 0, 0);
    int scale = 1;
    
    int hist_height = 256;
    Mat colorHis = Mat::zeros(hist_height, bins * 3, CV_8UC3);
    for (int i = 0; i < bins; i++)
    {
        float bin_val_r = hist_r.at<float>(i);
        float bin_val_g = hist_g.at<float>(i);
        float bin_val_b = hist_b.at<float>(i);
        int intensity_r = cvRound(bin_val_r*hist_height / max_val_r);  //“™ªÊ÷∆µƒ∏ﬂ∂»
        int intensity_g = cvRound(bin_val_g*hist_height / max_val_g);  //“™ªÊ÷∆µƒ∏ﬂ∂»
        int intensity_b = cvRound(bin_val_b*hist_height / max_val_b);  //“™ªÊ÷∆µƒ∏ﬂ∂»
        rectangle(colorHis, Point(i*scale, hist_height - 1),
                  Point((i + 1)*scale - 1, hist_height - intensity_r),
                  CV_RGB(255, 0, 0));
        
        rectangle(colorHis, Point((i + bins)*scale, hist_height - 1),
                  Point((i + bins + 1)*scale - 1, hist_height - intensity_g),
                  CV_RGB(0, 255, 0));
        
        rectangle(colorHis, Point((i + bins * 2)*scale, hist_height - 1),
                  Point((i + bins * 2 + 1)*scale - 1, hist_height - intensity_b),
                  CV_RGB(0, 0, 255));
        
    }
    imgShow(colorHis, "colorHis");
    return 0;
    
}

int drawHisGray(Mat image)
{
    int bins = 256;
    int hist_size[] = { bins };
    float range[] = { 0, 256 };
    const float* ranges[] = { range };
    
    MatND hist;
    int channels[] = { 0 };
    calcHist(&image, 1, channels, Mat(), // do not use mask
             hist, 1, hist_size, ranges,
             true, // the histogram is uniform
             false);
    
    double max_val;
    minMaxLoc(hist, 0, &max_val, 0, 0);
    
    int scale = 2;
    int hist_height = 256;
    Mat hist_img = Mat::zeros(hist_height, bins*scale, CV_8UC3);
    for (int i = 0; i < bins; i++)
    {
        float bin_val = hist.at<float>(i);
        int intensity = cvRound(bin_val*hist_height / max_val);
        
        rectangle(hist_img, Point(i*scale, hist_height - 1),
                  Point((i + 1)*scale - 1, hist_height - intensity),
                  CV_RGB(255, 255, 255));
    }
    
    imgShow(hist_img, "histOfImg");
    return 0;
}

int drawHis2D(Mat image)
{
    int hbins = 256, sbins = 256;
    int histSize[] = { hbins, sbins };
    
    float hranges[] = { 0, 256 };
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    
    int channels[] = { 0, 1 };
    calcHist(&image, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false);
    double maxVal = 0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);
    int scale = 2;
    Mat histImg = Mat::zeros(sbins*scale, hbins*scale, CV_8UC3);
    for (int h = 0; h < hbins; h++)
        for (int s = 0; s < sbins; s++)
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal * 255 / maxVal);
            rectangle(histImg, Point(h*scale, s*scale),
                      Point((h + 1)*scale - 1, (s + 1)*scale - 1),
                      Scalar::all(intensity),
                      FILLED);
        }
    imgShow(histImg, "2Dhist");
    return 0;
}

int Lab02()
{
    // 以黑白方式载入图像
    Mat img = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/CSet12/lena.png", 0);
    Mat colorImg = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/CSet12/lena.png", 1);
    // 检测图像是否真的被载入
    if(img.empty() || colorImg.empty())
        return -1;
    drawHisGray(img);
    Mat gray_equalized = equalize_hist(img);
    drawHisGray(gray_equalized);

    drawHisRGB(colorImg);
    Mat color_equalized = color_equalize_hist(colorImg);
    drawHisRGB(color_equalized);

    imgShow(colorImg, "colorImg");
    imgShow(color_equalized, "color_equalized");
    return 0;
}
