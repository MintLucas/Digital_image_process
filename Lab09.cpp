//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>
//#include "Lab01_grayConversion.hpp"
//#include "Lab02_hisBalance.hpp"
//#include "Lab03_spacialFilter.hpp"
//using namespace std;
//using namespace cv;
//
//
//int video(){
//    VideoCapture capture;
//    VideoWriter writer;
//    //capture.open("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/1.mp4");
//    //capture.open("/Users/zhipeng/opencv/samples/data/tree.avi");
//    capture.open(0);
////    Size S = Size((int)capture.get(CAP_PROP_FRAME_WIDTH),
////                  (int)capture.get(CAP_PROP_FRAME_HEIGHT));
////    writer.open("2.mp4", -1, 30.0, S);
//    Mat edge;
//    while (1) {
//        Mat frame;
//        capture >> frame;
//        //writer << frame;
//        //cvtColor(frame, edge, COLOR_BGR2GRAY);
//        //blur(edge, edge, Size(7,7));
//        //Canny(edge, edge, 0, 30);
//        if(!frame.empty())
//            imshow("frame", frame);
//        else
//            cout << "read error";
//        waitKey(30);
//        if (char(waitKey(1)) == 'q') break;
//    }
//    return 0;
//
//}
//
//
//int copytoROI()
//{
//    // 【1】读入图像
//    Mat srcImage= imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/My_dataSet/dota_pa.jpg");
//    Mat logoImage= imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/My_dataSet/dota_logo.jpg");
//
//    // 【2】定义一个Mat类型并给原图设定ROI区域
//    Mat imageROI= srcImage(Rect(400,250,logoImage.cols,logoImage.rows));
//    imShow("roi", imageROI);
//
//    // 【3】加载掩模（必须是灰度图）
//    Mat mask= imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/My_dataSet/dota_logo.jpg",0);
//    imShow("mask", logoImage);
//
//    //【4】将掩膜拷贝到原图上的ROI
//    logoImage.copyTo(imageROI,mask);
//
//    // 【5】显示结果
//    imShow("desImg", srcImage);
//    return 0;
//}
//
//int canny(){
//    Mat srcImg = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/1.jpg");
//    imshow("src", srcImg);
//    Mat midImg = getStructuringElement(MORPH_RECT, Size(3,3));
//
//    Mat desImg, edge, grayImg;
//
//    //desImg.create(srcImg.size(),srcImg.type());
//    cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
//    blur(grayImg, edge, Size(3,3));
//    Canny(edge, edge, 3, 9, 3);
//
//    //erode(srcImg, desImg, midImg);
//
//   // imshow("des",desImg);
//    imshow("edge",edge);
//    waitKey(0);
//
//    return 0;
//}
//
//void LinearBlending(double ratio)
//{
//    //【0】定义一些局部变量
//    double alphaValue = ratio/100;
//    double betaValue;
//    Mat srcImage, blendImg, dstImage;
//
//    // 【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )
//    srcImage = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/My_dataSet/mogu.jpg");
//    blendImg = imread("//Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/My_dataSet/rain.jpg");
//
//    // 【2】进行图像混合加权操作
//    betaValue = ( 1.0 - alphaValue );
//    addWeighted( srcImage, alphaValue, blendImg, betaValue, 0.0, dstImage);
//
//    // 【3】显示原图窗口
//    imShow( "<2>线性混合示例窗口【原图】", srcImage );
//    imShow( "<3>线性混合示例窗口【效果图】", dstImage );
//}
//
//
//
//
//
//void resizeImg(){
//    Mat srcImg = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/1.jpg");
//    Mat temImg, desImg1, desImg2, pyrDownImg;
//    temImg = srcImg;
//    imshow("srcImg", srcImg);
//
//    resize(temImg, desImg1, Size(temImg.cols/2, temImg.rows/2));
//    pyrDown(temImg, pyrDownImg, Size(temImg.cols/2, temImg.rows/2));
//    resize(temImg, desImg2, Size(temImg.cols*2, temImg.rows*2), (0,0), (0,0), 3);
//    imshow("resizeDown", desImg1);
//    imshow("pyrDown", pyrDownImg);
//    imshow("pyrUp", desImg2);
//
//    waitKey(0);
//}
//
//int main(){
//    Mat srcImg = imread("/Users/zhipeng/ustc_term2/Opencv/Opencv/Opencv/Digital_imgae_process/1.jpg");
//    //video();
//    //canny();
//    //    copytoROI();
//    //    LinearBlending(50);
//    resizeImg();
//}
//
