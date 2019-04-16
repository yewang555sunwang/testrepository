//功能：展示一张图   软件：visual studio 2013以上  模式：debug x64
#include<iostream>  
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;    
int main()  
{      // 读入一张图片（游戏原画）     
	Mat img=imread("C:\\pic.jpg");     
	// 创建一个名为 "游戏原画"窗口      
	namedWindow("游戏原画");    
	// 在窗口中显示游戏原画      
	imshow("游戏原画",img);    
	// 等待6000 ms后窗口自动关闭      
	waitKey(60000);  
	return 0;
} 