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
//�������ַ����ر���
vector<string> mydm;
;

void getmd()
{
	string str;
	while (1)
	{
		cout << "��������Ҫ����ʲô��";
		cin >> str;
	    mydm.push_back(str);
	}

}

int main()
{
	//1.�������ڣ�����  ѡһ������f12�鿴����
	HWND hWnd=initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//1.1���ô��ڴ�С��ȫ��
	//SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),SWP_SHOWWINDOW);
	
	//2.����ѭ���ȴ����룬��ʾ����ѭ�����
	x = GetSystemMetrics(SM_CXSCREEN);
	y = 20;
	setbkcolor(RED);
	cleardevice();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getmd, NULL, NULL, NULL);
	while (1)
	{
		cleardevice();//����
		const char out[128] = "������Ϻã���ɳ��ѩ��";
		outtextxy(x, y, "������Ϻã���ɳ��ѩ��" );
		Sleep(1000);
		x -= 50;
	}
	
	//3����
	while (1);
	return 0;

}