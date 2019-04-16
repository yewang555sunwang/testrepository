/********************************
	文件名称：main.cpp visualstudio 2019
	文件描述：实现一个表白程序 
*********************************/
#include <stdio.h>		//标准的输入输出头文件。
#include <graphics.h>   //EasyX图形界面。
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926548

//烟花
struct Fire
{
	int		r;  //半径
	int		max_r;
	int		x, y;
	int		cen_x, cen_y; 
	int		width, height;
	int		xy[240][240];  //像素数组图片！  跳一跳的外挂！
	bool	show;
	bool	draw;
	DWORD	t1, t2, dt;
}fire[13];


//烟花弹
struct Jet		//面向对象  类！
{
	int		x, y;			//坐标
	int		hx, hy;			//最高点的坐标
	IMAGE	img[2];			//图片数组 存放一明一暗两张图片。
	DWORD	t1, t2, dt;		//控制速度
	bool	shoot;          //是否发射
	byte	n : 1;			//C语言结构体：位段
}jet[13];  //13个sizeof(Jet) 描述烟花弹。

void Shoot();
void LoadImg();
void Choise(DWORD& t1);
void GameInit(int i);
void Show(DWORD* pmem);

int main()
{
	srand((unsigned int)time(NULL));
	//初始化图形界面 打开一个窗口！
	initgraph(1200,800); 

	DWORD t1 = GetTickCount();
	DWORD *pmem = GetImageBuffer();


	LoadImg();  //初始化13个内存的图片数组
	for (int i = 0; i < 13; i++)
	{
		GameInit(i); //初始化是3个内存的一些其他数据
	}
	BeginBatchDraw();
	while (1)
	{
		Choise(t1);
		Shoot();
		Show(pmem);
		FlushBatchDraw();
	}
	return 0;
}
void GameInit(int i)
{
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	fire[i].width = 240;
	fire[i].height = 240;
	fire[i].max_r = r[i];
	fire[i].cen_x = x[i];
	fire[i].cen_y = y[i];
	fire[i].show = false;
	//fire[i].draw = false;
	fire[i].dt = 5;
	fire[i].t1 = GetTickCount();
	fire[i].r = 0;

	//初始化烟花弹
	jet[i].t1 = GetTickCount();  //获取系统时间。
	jet[i].dt = rand() % 10; //0-9 ms
	jet[i].n = 0;
	jet[i].shoot = false;
}
void LoadImg()
{
	IMAGE flower,fimg;
	loadimage(&flower, L"./fire/flower.jpg", 3120, 240);
	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&flower);
		getimage(&fimg, i * 240, 0, 240, 240);
		SetWorkingImage(&fimg);
		for (int a = 0; a < 240; a++)
		{
			for (int b = 0; b < 240; b++)
			{
				fire[i].xy[a][b] = getpixel(a, b);
			}
		}
	}

	IMAGE jetimg;
	loadimage(&jetimg, L"./fire/shoot.jpg", 200, 50);
	SetWorkingImage(&jetimg);  //从jetimg获取
	for (int i = 0; i < 13; i++)
	{
		int n = rand() % 5;  //0-4
		getimage(&jet[i].img[0], n*20, 0, 20, 50);
		getimage(&jet[i].img[1], (n+5)*20, 0, 20, 50);
	}
	SetWorkingImage(NULL);  //从jetimg获取
}
void Choise(DWORD& t1)
{
	DWORD t2 = GetTickCount();
	if (t2 - t1 > 100)  //时间间隔100ms
	{
		int i = rand() % 13; //随机选一个 
		if (jet[i].shoot == false&&fire[i].show==false)
		{
			jet[i].x = rand() % 1179;
			jet[i].y = rand() % 100 + 600; //0-99  +600
			jet[i].hx = jet[i].x;
			jet[i].hy = rand() % 400;
			jet[i].shoot = true;

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
		}
		t1 = t2;
	}
}
void Shoot()  //13个！！ shoot = true  y--  n++
{
	for (int i = 0; i < 13; i++)
	{
		jet[i].t2 = GetTickCount();
		if (jet[i].t2 - jet[i].t1>jet[i].dt&&jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			if (jet[i].y > jet[i].hy) //没有到达最高点！
			{
				jet[i].y -= 5;
				jet[i].n++;
			}
			//jet[i].n
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			
			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				//hx  hy  烟花爆炸的点吗？传递烟花
				fire[i].x = jet[i].x;
				fire[i].y = jet[i].y;
				jet[i].shoot = false; //烟花弹重新利用
				fire[i].show = true;

			}
			jet[i].t1 = jet[i].t2;
		}
	}
}
void Show(DWORD* pmem)  //显存指针 渲染
{
	int drt[16] = { 5, 5, 5, 5, 5, 15, 15, 45, 45, 55, 55, 65, 65, 65, 65, 75 };

	for (int i = 0; i < 13; i++)
	{
		fire[i].t2 = GetTickCount();
		if (fire[i].t2 - fire[i].t1>fire[i].dt&&fire[i].show == true)
		{
			if (fire[i].r < fire[i].max_r)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}
			if (fire[i].r >= fire[i].max_r - 1)
			{
				fire[i].draw = false;
				GameInit(i);
			}
			fire[i].t1 = fire[i].t2;
		}

		if (fire[i].draw)
		{
			//弧度
			for (double a = 0; a <= 6.28; a+=0.01)  //int  double  ++
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r*cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r*sin(a));

				if (x1 > 0 && x1 < fire[i].width&&y1 > 0 && y1 < fire[i].height)
				{
					//图片 -》 像素 -》  颜色 -》 int -》32位
					//00000000(透明度) 00000000(red) 00000000(green) 0000000(blue)
					int b = fire[i].xy[x1][y1] & 0xff;
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (fire[i].xy[x1][y1] >> 16);

					int xx = (int)(fire[i].x + fire[i].r*cos(a));
					int yy = (int)(fire[i].y + fire[i].r*sin(a));

					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx<1200 && yy>0 && yy < 800)
					{
						pmem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
					}
				}
			}
			fire[i].draw = false;
		}
	}
}

////图片 如何定义！  赋值！  输出！
//IMAGE image;
//loadimage(&image, L"图片_20180903161423.jpg", 600, 800);
//IMAGE img;
//SetWorkingImage(&image);  //从image获取
//getimage(&img, 160, 20, 200, 250);
//SetWorkingImage(NULL);
//putimage(0, 0, &img);

/*
	IMAGE jetimg;
	loadimage(&jetimg, L"./fire/shoot.jpg", 200, 50);
	SetWorkingImage(&jetimg);  //从jetimg获取
	for (int i = 0; i < 13; i++)
	{
		int n = rand() % 5;  //0-4
		getimage(&jet[i].img[0], n*20, 0, 20, 50);
		getimage(&jet[i].img[1], (n+5)*20, 0, 20, 50);
	}
	SetWorkingImage(NULL);  //从jetimg获取






*/
