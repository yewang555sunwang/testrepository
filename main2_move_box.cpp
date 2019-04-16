//���ܣ��ƶ�������Ϸ �����visual studio 2013������ 
//��Ŀ�ļ���������Ϊ<move_box>
//<Debug<Project3.exe,Project3.ilk,Project3.pdb>,
//Project3<Debug<...>,blank.jpg,box.jpg,boxman.cbp,boxman.layout,end.jpg,main.cppmusic.wav,people.jpg
//,Project3.vcxproj,Project3.vcxproj.filters,Project3.vcxproj.user,redbox.jpg,wall.jpg>
//,boxman.sdf,Project3.sln>
//<>
//��׼���������ͷ�ļ�
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>  //ͼ�ο�,û��ҲҪ��������
#include <mmsystem.h>  //��ý���豸�ӿ� media control interface(MCI)
#pragma comment(lib,"winmm.lib")

IMAGE people, end, blank, wall, redbox, box;

int map[7][9] = {
		{0,0,1,1,1,1,0,0,0},  //0  �յ�
		{1,1,1,0,0,1,1,0,0},  //1  ǽ
		{1,0,3,3,0,0,1,1,1},  //3  Ŀ�ĵ�
		{1,0,7,3,7,0,0,0,1},  //4  ����
		{1,5,4,4,3,4,4,0,1},  //5  ��
		{1,0,0,1,1,0,0,0,1},  //7  ����+Ŀ�ĵ� 
		{1,1,1,1,1,1,1,1,1} }; //8  ��+Ŀ�ĵ�

//��Ϸ�ĳ�ʼ��  ����(ֱ����)��ͼƬ(���ص�������)��������
void GameInit()
{
	//��ʼ��һ������  ����
	initgraph(350, 450);   //����һ������ ��С ��  ��

	//��ʼ������
	PlaySound(L"music.wav", NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);//ֻ֧��mav

	//����ͼƬ  ����
	people, end, blank, wall, redbox, box;
	loadimage(&people, L"people.jpg", 50, 50);
	loadimage(&end, L"end.jpg", 50, 50);
	loadimage(&blank, L"blank.jpg", 50, 50);
	loadimage(&wall, L"wall.jpg", 50, 50);
	loadimage(&redbox, L"redbox.jpg", 50, 50);
	loadimage(&box, L"box.jpg", 50, 50);
}

//���Ƶ�ͼ
void DrawMap()
{
	//������ά����
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

//����Ϸ
void PlayGame()
{
	char key;    //����

	//���˵�λ��  �˵ı�־��ʲô? 5 8(ϸ��)
	int r, c;  //��¼�˵�ǰ�� �� �� ��.
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
	//map[r][c]   ��ǰ�˵�λ��
	//map[r-1][c] ��ǰ���λ��
	//map[r-2][c] ��ǰ���ǰ���λ��

	key = getch(); //key���հ���

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
		//1.�˵�ǰ���ǿյ�(����)//2.�˵�ǰ����Ŀ�ĵ�(����)
		if (map[r - 1][c] == 0 || map[r - 1][c] == 3)
		{
			map[r - 1][c] += 5;
			map[r][c] -= 5;
		}
		//4.�˵�ǰ������(��һ��)
		if (map[r - 1][c] == 4 || map[r - 1][c] == 7)
		{
			//4.1 ���ӵ�ǰ���ǿյ�(����)
			//4.2 ���ӵ�ǰ����Ŀ�ĵ�(����)
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

//������
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





