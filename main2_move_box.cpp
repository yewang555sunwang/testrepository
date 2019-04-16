//功能：移动箱子游戏 软件：visual studio 2013及以上 
//项目文件依次向内为<move_box>
//<Debug<Project3.exe,Project3.ilk,Project3.pdb>,
//Project3<Debug<...>,blank.jpg,box.jpg,boxman.cbp,boxman.layout,end.jpg,main.cppmusic.wav,people.jpg
//,Project3.vcxproj,Project3.vcxproj.filters,Project3.vcxproj.user,redbox.jpg,wall.jpg>
//,boxman.sdf,Project3.sln>
//<>
//标准的输入输出头文件
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>  //图形库,没有也要自行配置
#include <mmsystem.h>  //多媒体设备接口 media control interface(MCI)
#pragma comment(lib,"winmm.lib")

IMAGE people, end, blank, wall, redbox, box;

int map[7][9] = {
		{0,0,1,1,1,1,0,0,0},  //0  空地
		{1,1,1,0,0,1,1,0,0},  //1  墙
		{1,0,3,3,0,0,1,1,1},  //3  目的地
		{1,0,7,3,7,0,0,0,1},  //4  箱子
		{1,5,4,4,3,4,4,0,1},  //5  人
		{1,0,0,1,1,0,0,0,1},  //7  箱子+目的地 
		{1,1,1,1,1,1,1,1,1} }; //8  人+目的地

//游戏的初始化  符号(直接用)和图片(加载到程序当中)区别在于
void GameInit()
{
	//初始化一个界面  窗口
	initgraph(350, 450);   //创建一个窗口 大小 宽  高

	//初始化音乐
	PlaySound(L"music.wav", NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);//只支持mav

	//加载图片  加载
	people, end, blank, wall, redbox, box;
	loadimage(&people, L"people.jpg", 50, 50);
	loadimage(&end, L"end.jpg", 50, 50);
	loadimage(&blank, L"blank.jpg", 50, 50);
	loadimage(&wall, L"wall.jpg", 50, 50);
	loadimage(&redbox, L"redbox.jpg", 50, 50);
	loadimage(&box, L"box.jpg", 50, 50);
}

//绘制地图
void DrawMap()
{
	//遍历二维数组
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(i * 50, j * 50, &blank);
				break;
			case 1:
				putimage(i * 50, j * 50, &wall);
				break;
			case 3:
				putimage(i * 50, j * 50, &end);
				break;
			case 4:
				putimage(i * 50, j * 50, &box);
				break;
			case 5:
				putimage(i * 50, j * 50, &people);
				break;
			case 7:
				putimage(i * 50, j * 50, &redbox);
				break;
			case 8:
				putimage(i * 50, j * 50, &people);
				break;
			}
		}
		printf("\n");
	}
}

//玩游戏
void PlayGame()
{
	char key;    //按键

	//找人的位置  人的标志是什么? 5 8(细节)
	int r, c;  //记录人当前的 行 和 列.
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)
			{
				r = i;
				c = j;
			}
		}
	}
	//map[r][c]   当前人的位置
	//map[r-1][c] 人前面的位置
	//map[r-2][c] 人前面的前面的位置

	key = getch(); //key接收按键

	switch (key)
	{
	case 72:
		if (map[r][c - 1] == 0 || map[r][c - 1] == 3)
		{
			map[r][c - 1] += 5;
			map[r][c] -= 5;
		}
		if (map[r][c - 1] == 4 || map[r][c - 1] == 7)
		{
			if (map[r][c - 2] == 0 || map[r][c - 2] == 3)
			{
				map[r][c - 2] += 4;
				map[r][c - 1] += 1;
				map[r][c] -= 5;
			}
		}
		break;
	case 80:
		if (map[r][c + 1] == 0 || map[r][c + 1] == 3)
		{
			map[r][c + 1] += 5;
			map[r][c] -= 5;
		}
		if (map[r][c + 1] == 4 || map[r][c + 1] == 7)
		{
			if (map[r][c + 2] == 0 || map[r][c + 2] == 3)
			{
				map[r][c + 2] += 4;
				map[r][c + 1] += 1;
				map[r][c] -= 5;
			}
		}
		break;
	case 75:
		//1.人的前面是空地(可以)//2.人的前面是目的地(可以)
		if (map[r - 1][c] == 0 || map[r - 1][c] == 3)
		{
			map[r - 1][c] += 5;
			map[r][c] -= 5;
		}
		//4.人的前面箱子(不一定)
		if (map[r - 1][c] == 4 || map[r - 1][c] == 7)
		{
			//4.1 箱子的前面是空地(可以)
			//4.2 箱子的前面是目的地(可以)
			if (map[r - 2][c] == 0 || map[r - 2][c] == 3)
			{
				map[r - 2][c] += 4;
				map[r - 1][c] += 1;
				map[r][c] -= 5;
			}
		}


		break;
	case 77:
		if (map[r + 1][c] == 0 || map[r + 1][c] == 3)
		{
			map[r + 1][c] += 5;
			map[r][c] -= 5;
		}
		if (map[r + 1][c] == 4 || map[r + 1][c] == 7)
		{
			if (map[r + 2][c] == 0 || map[r + 2][c] == 3)
			{
				map[r + 2][c] += 4;
				map[r + 1][c] += 1;
				map[r][c] -= 5;
			}
		}
		break;
	}
}

//主函数
int main()
{
	GameInit();

	while (1)
	{
		system("cls");
		DrawMap();
		PlayGame();
	}
	return 0;
}





