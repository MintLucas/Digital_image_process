#ifndef Lab02_hisBalance_hpp
#define Lab02_hisBalance_hpp
#include<iostream>
#include<string>
#include<vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include "Lab01_grayConversion.hpp"

Mat equalize_hist(Mat& input);
Mat color_equalize_hist(Mat input);
int drawHisGray(Mat image);
int drawHis2D(Mat image);
int drawHisRGB(Mat image);
int Lab02();

#endif /* Lab02_hisBalance_hpp */
