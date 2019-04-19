#ifndef Lab04_noiseEliminate_hpp
#define Lab04_noiseEliminate_hpp

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

void meanFilterShow(Mat srcImg, Mat colImg);
void medeanFilterShow(Mat srcImg);
void harmonicFilterShow(Mat srcImg);
int Lab04();

#endif /* Lab04_noiseEliminate_hpp */
