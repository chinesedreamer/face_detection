// face_detection.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//参考blog:https://blog.csdn.net/xingchenbingbuyu/article/details/51105159

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

String face_cascade_name = "haarcascade_frontalface_default.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;   //人脸分类器
CascadeClassifier eyes_cascade;   //人眼分类器
String window_name = "Face detection";

void detectAndDisplay(Mat frame);

int main()
{
	Mat frame = imread("D:\\yanxue\\openCV\\pic\\face.jpeg");//图片路径

	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading eyes cascade\n"); return -1; };

	
	detectAndDisplay(frame);

	waitKey(0);
	 
	return 0;
	
}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);//转灰度图
	equalizeHist(frame_gray, frame_gray);//直方图均衡化，增强图像

	//Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, CV_HAAR_DO_ROUGH_SEARCH, Size(70, 70), Size(100, 100));

	for (size_t i = 0; i < faces.size(); i++)
	{
		rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);//矩形框

		Mat faceROI = frame_gray(faces[i]);//faceROI为找出的人脸图像
		std::vector<Rect> eyes;

		// In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 1, CV_HAAR_DO_ROUGH_SEARCH, Size(3, 3));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Rect rect(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y, eyes[j].width, eyes[j].height);
			rectangle(frame, rect, Scalar(0, 255, 0), 2, 8, 0);
		}
	}
	//Show
	namedWindow(window_name, 2);
	imshow(window_name, frame);
}

