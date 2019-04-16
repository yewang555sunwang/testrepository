// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//功能：visual paint circle 

#include "pch.h"
#include <iostream>
#include<graphics.h>  //此文件自行配置
#include <conio.h>
#include<Windows.h>


int main()
{
    std::cout << "Hello World!\n"; 
	int x0 = 320, y0 = 240;
	int n = 25, i, j, r = 180;
	int x[50], y[50];
	initgraph(640, 480);   // 这里和 TC 略有区别
	setcolor(GREEN);
	   circle(200, 200, 100); // 画圆，圆心(200, 200)，半径 100
	   Sleep(6000);          // 按任意键继续
	   setcolor(BLACK);
	   circle(200, 200, 100);
	     //closegraph();          // 关闭图形界面
		// initgraph(640, 480);
		 setcolor(RED);
		 for (i = 0; i < n; i++)
		 {
			 x[i] = r * cos(2 * 3.1415926*i / n) + x0;
			 y[i] = r * sin(2 * 3.1415926*i / n) + y0;
		 }
		 for (i = 0; i <= n - 2; i++)
		 {
			 for (j = i + 1; j <= n - 1; j++)
				 line(x[i], y[i], x[j], y[j]);
		 }
		 Sleep(6000);          // 按任意键继续
		 closegraph();
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
