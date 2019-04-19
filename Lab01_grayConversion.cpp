#include "Lab01_grayConversion.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;


int Lab01() {

    // 以黑白方式载入图像
    Mat img = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/CSet12/lena.png", 0);
    // 检测图像是否真的被载入
    if(img.empty())
        return -1;

    imgShow(img, "original");
    Threshold(img, 30);
    logTransform(img, 1);
    gammaTransform(img, 1, 0.5);

    // 返回一个3通道的彩色图像
    img = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/CSet12/lena.png", 1);
    //complementaryTransform(img);
    complementaryTransforminHSV(img);

    return 0;
}

// 显示一张图片
void imgShow(Mat &srcImg, string title) {
    
    // 新建一个标题为"Example1"的窗口，WINDOW_AUTOSIZE表示窗口的大小会根据载入图像的大小进行调整
    namedWindow(title, WINDOW_AUTOSIZE);
    // 将所选图片绘制到窗口上，且显示
    imshow(title, srcImg);
    // 无限等待直到用户按下某个键
    waitKey(0);
    // 销毁窗口
    destroyWindow(title);
}

void imShow(string title, Mat &srcImg) {
    
    // 新建一个标题为"Example1"的窗口，WINDOW_AUTOSIZE表示窗口的大小会根据载入图像的大小进行调整
    namedWindow(title, WINDOW_AUTOSIZE);
    // 将所选图片绘制到窗口上，且显示
    imshow(title, srcImg);
    // 无限等待直到用户按下某个键
    waitKey(0);
    // 销毁窗口
    destroyWindow(title);
}

// 灰度图像二值化处理
void Threshold(Mat &srcImg, double thresh) {
    Mat resultImg;
    resultImg = srcImg.clone();
    
    Mat_<uchar>::iterator it = resultImg.begin<uchar>();
    Mat_<uchar>::iterator itend = resultImg.end<uchar>();
    for (; it < itend; it++) {
        if((*it) > thresh)
            *it = 200;
        else
            *it = 0;
    }
    // InputArray src,  源图像
    // OutputArray dst, 输出图像
    // double thresh,   门限值
    // double maxval,   最大值
    // int type,        函数类型选择，THRESH_BINARY，THRESH_BINARY_INV，THRESH_TRUNC，THRESH_TOZERO，THRESH_TOZERO_INV
    //threshold(srcImg, resultImg, thresh, 200.0, THRESH_BINARY);
    
    imgShow(resultImg, "Threshold");
}

// 灰度图像的对数变换
void logTransform(Mat &srcImg, int c) {
    Mat resultImg = srcImg.clone();
    
    // OpenCV有为Mat提供了与STL相兼容的迭代器
    Mat_<uchar>::iterator it = resultImg.begin<uchar>();
    Mat_<uchar>::iterator itend = resultImg.end<uchar>();
    for(; it!=itend; it++){
        // 依据log变换公式: c * log(1 + data)
        (*it) = c * log(1 + (*it));
    }
    
    // 归一化处理
    normalize(resultImg, resultImg, 0, 255, cv::NORM_MINMAX);
    imgShow(resultImg, "logTransform");
}

// 灰度图像的伽马变换
void gammaTransform(Mat &srcImg, int c, double gamma) {
    Mat resultImg = srcImg.clone();
    
    Mat_<uchar>::iterator it = resultImg.begin<uchar>();
    Mat_<uchar>::iterator itend = resultImg.end<uchar>();
    for(; it!=itend; it++) {
        // 依据gamma变换公式: c * pow(data, gamma)
        (*it) = c * pow((*it), gamma);
    }
    
    // 归一化处理
    normalize(resultImg, resultImg, 0, 255, cv::NORM_MINMAX);
    imgShow(resultImg, "gammaTransform");
}

// 彩色图像的补色变换
void complementaryTransform(Mat &srcImg) {
    Mat resultImg = srcImg.clone();
    
    Mat_<Vec3b>::iterator it = resultImg.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = resultImg.end<Vec3b>();
    Vec3b temp;//不能交替变
    for(;it!=itend;it++){
        temp[0] = 255 - (*it)[2];//C=255-R£ª
        temp[1] = 255 - (*it)[1];//M=255-G£ª
        temp[2] = 255 - (*it)[0];//Y=255-B£ª
        
        *it = temp;
    }
    
    imgShow(resultImg, "ComplementaryColorTransform");
}

void complementaryTransforminHSV(Mat &srcImg) {
    Mat resultImg = srcImg.clone();
    
    cvtColor(srcImg, resultImg, COLOR_BGR2HSV);
    
    Mat_<Vec3b>::iterator it = resultImg.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = resultImg.end<Vec3b>();
    Vec3b temp;//不能交替变
    for(;it!=itend;it++){
        
        if ((*it)[0] >= 180.0)
            temp[0] = (*it)[0] - 180.0;
        else
            temp[0] = 180.0 - (*it)[0];
        temp[1] = (*it)[1];
        temp[2] = 1.0 - (*it)[2];
        
        *it = temp;
        
    }
    
    imgShow(resultImg, "ComplementaryTransforminHSV");
}
