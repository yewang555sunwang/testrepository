//���ܣ�չʾһ��ͼ   �����visual studio 2013����  ģʽ��debug x64
#include<iostream>  
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;    
int main()  
{      // ����һ��ͼƬ����Ϸԭ����     
	Mat img=imread("C:\\pic.jpg");     
	// ����һ����Ϊ "��Ϸԭ��"����      
	namedWindow("��Ϸԭ��");    
	// �ڴ�������ʾ��Ϸԭ��      
	imshow("��Ϸԭ��",img);    
	// �ȴ�6000 ms�󴰿��Զ��ر�      
	waitKey(60000);  
	return 0;
} 