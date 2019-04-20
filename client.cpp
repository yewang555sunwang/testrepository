// client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
//// Project1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include"stdafx.h"
#include <iostream>

#include<winsock2.h>
#include"ws2tcpip.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

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


	//连接地址族
	int r= connect(serversocket, (sockaddr*)& addr, sizeof addr);
	if (r == -1)
	{
		printf("连接服务器失败");
		return -1;
	}
	printf("连接服务器成功");



	//通信
	char buff[256]; char BUFF[256];
	while (1)
	{


		printf("\n请输入;");
		scanf("%s", buff);
		r = send(serversocket, buff, 255, NULL);
		if (r > 0)
		{
			
			printf("发送了%d字节数据\n", r);
		}
	



		
		
	}
	while (1);
	//关闭socket
	closesocket(serversocket);
	
	//清除版本信息
	WSACleanup();
	return 0;
}

