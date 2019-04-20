// server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
// Project1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include"stdafx.h"
#include <iostream>

#include<winsock2.h>
#include"ws2tcpip.h"
#pragma comment(lib,"ws2_32.lib")

int  send1(SOCKET,SOCKET,char buff[] );
int send2(SOCKET clientsocket1,SOCKET clientsocket, char BUFF[]);
int send1(SOCKET clientsocket1,SOCKET clientsocket,char buff[])
{
	int r = recv(clientsocket, buff, 255, NULL);
	if (r > 0)
	{
		buff[r] = '\0';
		int H = send(clientsocket1, buff, strlen(buff), NULL);
		printf("往服务器发送了%d字节的数据！\n", H);

	}
	return 0;
}

int send2(SOCKET clientsocket1, SOCKET clientsocket, char BUFF[])
{
	int y = recv(clientsocket1, BUFF, 255, NULL);
	if (y > 0)
	{
		BUFF[y] = '\0';
		int H = send(clientsocket, BUFF, strlen(BUFF), NULL);

	}
	return 0;
}

int main()//_tmain(int argc,_TCHAR_DEFINED char*argv[])//
{
	//获取协议版本
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (HIBYTE(wsadata.wVersion) != 2 || LOBYTE(wsadata.wVersion) != 2)
	{
		printf("请求版本失败！");
		return -1;
	}
	printf("请求版本成功！\n");

	//创建socket套接字
	SOCKET serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == serversocket)
	{
		printf("创建socket失败！\n");
		return -1;
	}
	printf("创建socket成功！\n");


	//创建协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET; //确定协议
	//PVOID64 ipv6addr;
	addr.sin_addr.S_un.S_addr = inet_addr("169.254.32.196");//inet_pton(AF_INET, "127.0.0.1", &ipv6addr); ////IP地址 
	addr.sin_port = htons(10086);//端口

	//绑定
	int r = bind(serversocket, (SOCKADDR*)& addr, sizeof addr);
	if (r == -1)
	{
		printf("bind失败！\n");
		return -1;
	}
	printf("bind成功！\n");

	//监听
	r = listen(serversocket, 10);
	if (r == -1)
	{
		printf("listen失败！\n");
		return -1;
	}
	printf("listen成功！\n");

	//等待客户端连接服务器
	SOCKADDR_IN caddr = { 0 };
	int len = sizeof caddr;
	SOCKET clientsocket= accept(serversocket, (sockaddr*)& caddr, &len);
	if (clientsocket == -1)
	{
		printf("客户端错误！\n");
		WSACleanup();
		closesocket(serversocket);
		return -1;
	}
	printf("有客户端连接到服务器了：%s\n", inet_ntoa(caddr.sin_addr));

	//通信
	char buff[256]; char BUFF[256];
	while (1)
	{
		r=recv(clientsocket, buff, 255, NULL);
		if (r> 0)
		{
			buff[r] = '\0';
			printf(">>%s\n", buff);
		}
		
		
	}

	//关闭socket
	closesocket(serversocket);
	closesocket(clientsocket);

	//清除版本信息
	WSACleanup();
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
