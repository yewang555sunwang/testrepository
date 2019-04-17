// ConsoleApplication3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//visual studio 2013以上版本
#include"stdafx.h"
#include<time.h>
#include <iostream>
#include<graphics.h>
#include<stdio.h>
#include<vector>
#include<string>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

//弹幕结构体
struct wenzi
{
	COLORREF color;
	int xpos;
	int ypos;
	int speed;
	char buff[128];
};

vector<wenzi> w; //动态数组

//1.弹幕初始化
void getwenzi()
{
	wenzi* p = new wenzi;
	while (1)
	{
		printf("请输入要发送的弹幕：\n");
		cin >> p->buff;
		//scanf("%s", p->buff);
		p->color = RGB(rand() % 256, rand() % 256, rand() % 256);
		p->xpos = 50;
		p->ypos = rand() % 800;
		p->speed = rand() % 10 + 1;
		w.push_back(*p);//加载动态数组
	}
	
}
//2.显示弹幕
void showwenzi()
{
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		for (int i = 0; i < w.size(); i++)
		{
			settextcolor(w[i].color);
			outtextxy(w[i].xpos, w[i].ypos, w[i].buff);
		}
		EndBatchDraw();
	}
}

//3.弹幕的移动
void movewenzi()
{
	for (int i = 0; i < w.size(); i++)
	{
		w[i].xpos = w[i].xpos + w[i].speed;
	}

}

int main()
{ 
	//int add=0;
	//打开音频文件  x.wav应放在同项目cpp主函数一个目录
	mciSendString("open x.wav", 0, 0, 0);
	//播放音频文件
	mciSendString("play x.wav", 0, 0, 0);
	wenzi w;
	//1.创建窗口 
	HWND hwnd=initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),SHOWCONSOLE);
	 
	//设置文字颜色
	srand((unsigned)time(NULL));

	//设置窗口风格
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);

	//设置窗口点位及风格
	SetWindowPos(hwnd,HWND_TOPMOST,0,0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),SWP_SHOWWINDOW);

	//拿到背面的窗口风格
	LONG windowLong = GetWindowLong(hwnd,GWL_EXSTYLE)|WS_EX_LAYERED;

	//设置窗口风格
	SetWindowLong(hwnd, GWL_EXSTYLE, windowLong);

	//设置窗口透明
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

	//创建线程
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getwenzi, NULL, NULL, NULL);//创建输入线程
	//设置定时器
	SetTimer(hwnd,10086,50,(TIMERPROC)movewenzi);
        //getwenzi();
	showwenzi();
	settextcolor(RGB(rand()%256, rand() % 256,rand() % 256));
	
    
	while (1);
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
