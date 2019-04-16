#include<graphics.h>
#include"stdafx.h"
#include<iostream>
#include<vector>
#include<string>

using namespace std;

#define window_width 800
#define window_height 800

struct mydm
{
	int x, y;
	string str;
};

int x, y;
//保存多个字符串必备行
vector<string> mydm;
;

void getmd()
{
	string str;
	while (1)
	{
		cout << "请问你需要输入什么：";
		cin >> str;
	    mydm.push_back(str);
	}

}

int main()
{
	//1.制作窗口，输入  选一个函数f12查看函数
	HWND hWnd=initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//1.1设置窗口大小，全屏
	//SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),SWP_SHOWWINDOW);
	
	//2.输入循环等待输入，显示窗口循环输出
	x = GetSystemMetrics(SM_CXSCREEN);
	y = 20;
	setbkcolor(RED);
	cleardevice();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getmd, NULL, NULL, NULL);
	while (1)
	{
		cleardevice();//清屏
		const char out[128] = "大家晚上好，长沙下雪了";
		outtextxy(x, y, "大家晚上好，长沙下雪了" );
		Sleep(1000);
		x -= 50;
	}
	
	//3设置
	while (1);
	return 0;

}