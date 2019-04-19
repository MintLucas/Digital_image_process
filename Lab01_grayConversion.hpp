#ifndef Lab01_grayConversion_hpp
#define Lab01_grayConversion_hpp

#include <stdio.h>
#include "Lab01_grayConversion.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void imgShow(Mat&, string);
void imShow(string title, Mat &srcImg);
void Threshold(Mat&, double);
void logTransform(Mat&, int);
void gammaTransform(Mat&, int, double);
void complementaryTransform(Mat&);
void complementaryTransforminHSV(Mat &srcImg);
int Lab01();
#endif /* Lab01_grayConversion_hpp */
