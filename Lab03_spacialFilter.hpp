#ifndef Lab03_spacialFilter_hpp
#define Lab03_spacialFilter_hpp

#include <stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include "Lab01_grayConversion.hpp"


int MeanFilter_Gray(int a, int b);
int GaussianFilter_Gray(int a, int b);
int Laplacian_Gray();
int Robert_G();
int Sobel();
int MeanFilter_Color(int a, int b);
int GaussianFilter_Color(int a, int b);

int sobelXY();
int spacialFilter(vector<float> filter);
int Laplacian_Color();
int enhanceFilter();
int Robert_RGB();
int Sobel_Color();
int Lab03();

#endif /* Lab03_spacialFilter_hpp */
