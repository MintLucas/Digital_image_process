#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "Lab01_grayConversion.hpp"
#include "Lab02_hisBalance.hpp"
#include "Lab03_spacialFilter.hpp"
#include "Lab04_noiseEliminate.hpp"
#include "Lab05_spectrumFileter.hpp"

using namespace std;
using namespace cv;

int main(){
    Mat img, img2, img3, gray, blur_img, edges, mask, masked_edges;
    img = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/4.jpg",-1);
    img2 = img.clone();
    img3 = img.clone();
    if(img.empty()){
        cout << "read file error" << endl;
        return -1;
    }
    //imshow("srcImg", img);
    
    //第一步灰度均衡化：
    cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    GaussianBlur(gray, blur_img, Size(5, 5), 0);
    imshow("1gray", gray);
    
    //第二步进行边缘检测：
    Canny(blur_img, edges, 100, 250);
    imshow("2canny", edges);
    
    //第三部ROI:在感兴趣区域内寻找车道线，大大缩减图像的处理计算量
    mask = Mat::zeros(img.size(), CV_8UC1);
    vector<vector<Point>> contour;
    vector<Point> pts;
    pts.push_back(Point(0, img.rows));//横坐标cols,纵坐标rows
    pts.push_back(Point(img.cols/2.0 - 20, img.rows*0.6));
    pts.push_back(Point(img.cols/2.0 + 20, img.rows*0.6));
    pts.push_back(Point(img.cols, img.rows));
    contour.push_back(pts);
    //绘制轮廓的最大等级。如果等级为0，绘制单独的轮廓。如果为-1,s绘制所有轮廓
    drawContours(mask, contour, 0, Scalar::all(255), -1);
    edges.copyTo(masked_edges, mask);
    imshow("3mask", mask);
    imshow("3masked_edges", masked_edges);
    
    //第四部：概率hough直线变换
    vector<Vec4i> lines, left_lines, right_lines;// Vec4i -> lines[i][0-3]
    //得到的lines就是所有线的列表,用起点和终点xy坐标记录
    HoughLinesP(masked_edges, lines, 2, CV_PI/180, 30, 10, 30);
    //分为左右车道线
    vector<double> left_slope, right_slope;
    //Point2d -> left_centers[i].x
    vector<Point2d> left_centers, right_centers;
    list<Vec4i> list_lines;
    
    
    //Part1:直接用hough变换存入list里的直线 在原图画线
    vector<Vec4i> pro_lines;   //list(after erase) -> vector
    for(auto v:lines)
        pro_lines.push_back(v);

    for(int i=0; i<pro_lines.size(); i++)
    {
        line(img, Point(pro_lines[i][0], pro_lines[i][1]),
             Point(pro_lines[i][2], pro_lines[i][3]) ,Scalar(255,0,0),3,8);
    }
    imshow("houghListLines", img);
    
    
    double slo;
    Point2d center;
    int i = 0;
    for(auto v : lines) //vector->list
        list_lines.push_back(v);
    
    for (auto iter = list_lines.begin(); iter != list_lines.end(); ++i) {
        //slo=(y2-y1)/(x2-x1)
        slo = double((lines[i][3]-lines[i][1]))/double((lines[i][2]-lines[i][0])) ;
        //center=(x1+x2)/2, (y1+y2)/2
        center = Point( double(lines[i][2]+lines[i][0])/2 , double(lines[i][3]+lines[i][1])/2 );
        
        //斜率不满足车道线的erase
        if(fabs(slo)<0.35)
        {
            iter = list_lines.erase(iter);
            continue;
        }
        
        //根据斜率正负判断左右车道线
        if(slo > 0)
        {
            right_lines.push_back(lines[i]);
            right_centers.push_back(center);
            right_slope.push_back(slo);
        }
        else
        {
            left_lines.push_back(lines[i]);
            left_centers.push_back(center);
            left_slope.push_back(slo);
        }
        
        *iter = lines[i];
        iter++;
        
    }
    
    //Part2:斜率不满足车道线的erase后 在原图画线
    vector<Vec4i> pro_lines2;   //list(after erase) -> vector
    for(auto v:list_lines)
        pro_lines2.push_back(v);

    for(int i=0; i<pro_lines2.size(); i++)
    {
        line(img2, Point(pro_lines2[i][0], pro_lines2[i][1]),
             Point(pro_lines2[i][2], pro_lines2[i][3]) ,Scalar(0,255,0),3,8);
    }
    imshow("sloSelectLines", img2);
    
    //left to mean slope and center
    double left_len, total_left_len=0, total_left_slope=0;
    Point2d total_left_center(0,0);
    for(int i = 0; i< left_lines.size(); i++)
    {
        //记录总线长和总中心点
        left_len = sqrt( (left_lines[i][2]-left_lines[i][0])*(left_lines[i][2]-left_lines[i][0]) + (left_lines[i][3]-left_lines[i][1])*(left_lines[i][3]-left_lines[i][1]) );
        total_left_slope += left_len * left_slope[i];
        total_left_len += left_len;
        total_left_center = Point(total_left_center.x + left_len * left_centers[i].x , total_left_center.y + left_len * left_centers[i].y );
    }
    
    //按线越长权值越大算平均斜率
    double mean_left_slope;
    Point2d mean_left_center;
    mean_left_slope = total_left_slope/ total_left_len;
    mean_left_center = Point( total_left_center.x/total_left_len, total_left_center.y/total_left_len);
    
    //right to mean slope and center
    double right_len, total_right_len=0, total_right_slope=0;
    Point2d total_right_center(0,0);
    for(int i = 0; i< right_lines.size(); i++)
    {
        right_len = sqrt( (right_lines[i][2]-right_lines[i][0])*(right_lines[i][2]-right_lines[i][0]) + (right_lines[i][3]-right_lines[i][1])*(right_lines[i][3]-right_lines[i][1]) );
        total_right_slope = total_right_slope + right_len * right_slope[i];
        total_right_len = total_right_len + right_len;
        total_right_center = Point(total_right_center.x + right_len * right_centers[i].x , total_right_center.y + right_len * right_centers[i].y );
    }
    
    double mean_right_slope;
    Point2d mean_right_center;
    mean_right_slope = total_right_slope/ total_right_len;
    mean_right_center = Point( total_right_center.x/total_right_len, total_right_center.y/total_right_len);
    
    //设置车道线起点y1终点y2,在驾驶位上可看到的视野车道线在下部分0.6-1对应的y区域内
    double start_y = img.rows * 0.6;//左上角0,0,即上半部分0-0.6为天空
    double end_y = img.rows;
    //算得的斜率和中心点,带入方程算x1,x2单侧画线
    double left_start_x = (start_y - mean_left_center.y)/mean_left_slope + mean_left_center.x;
    double left_end_x = (end_y - mean_left_center.y)/mean_left_slope + mean_left_center.x;
    double right_start_x = (start_y - mean_right_center.y)/mean_right_slope + mean_right_center.x;
    double right_end_x = (end_y - mean_right_center.y)/mean_right_slope + mean_right_center.x;
    
    //Part3：分了左右再根据先验知识计算平均中点和平均斜率后 在原图画线
    line(img3, Point(left_start_x, start_y), Point(left_end_x, end_y), Scalar(0,0,255), 3, 8);
    line(img3, Point(right_start_x, start_y), Point(right_end_x, end_y), Scalar(0,0,255), 3, 8);
    
    imshow("4twoLinesInHorizon", img3);
    
    waitKey(0);
    return 0;
}
