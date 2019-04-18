// ConsoleApplication5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include <Windows.h>
#include <cassert>
#include <Vfw.h>
#pragma comment(lib, "vfw32")

LRESULT CALLBACK IndexWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK viewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void initializeClass();
bool myRegisterClass();
void myCreateWindow();
void myUpdateWindow();
void myShowWindow();
void myMessageRoute();

// 全局实例
HINSTANCE g_hInst;

// 窗口名
TCHAR indexClassName[] = TEXT("index");
TCHAR viewClassName[] = TEXT("view");

// 窗口类
WNDCLASS indexWndClass;
WNDCLASS viewWndClass;

// 窗口对象
HWND indexHWnd;
HWND viewHWnd;

// 应用名字
const TCHAR appName[] = TEXT("使用vfw");

// 按钮ID
const INT BTN_BEGIN = 100;
const INT BTN_END = 101;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	g_hInst = hInstance;

	initializeClass();

	// 注册
	if (!myRegisterClass())
	{
		MessageBox(NULL, TEXT("注册类失败"), TEXT("错误"), MB_ICONERROR);
		return 0;
	}

	// 创建
	myCreateWindow();

	// 显示
	myShowWindow();

	// 更新
	myUpdateWindow();

	// 消息循环
	myMessageRoute();

	return 0;
}

void initializeClass()
{
	/// 初始化indexWndClass
	memset(&indexWndClass, 0, sizeof(indexWndClass));
	indexWndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	indexWndClass.hInstance = g_hInst;
	indexWndClass.lpfnWndProc = IndexWndProc;
	indexWndClass.lpszClassName = indexClassName;
	indexWndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 初始化viewWndClass
	memset(&viewWndClass, 0, sizeof(viewWndClass));
	viewWndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	viewWndClass.hInstance = g_hInst;
	viewWndClass.lpfnWndProc = viewWndProc;
	viewWndClass.lpszClassName = viewClassName;
	viewWndClass.style = CS_HREDRAW | CS_VREDRAW;
}

bool myRegisterClass()
{
	if (!RegisterClass(&indexWndClass))
	{
		return false;
	}

	if (!RegisterClass(&viewWndClass))
	{
		return false;
	}

	return true;
}

void myCreateWindow()
{
	indexHWnd = CreateWindow(indexClassName, appName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 900, 700, NULL, NULL, g_hInst, NULL);
	assert(NULL != indexHWnd);
}

void myUpdateWindow()
{
	UpdateWindow(indexHWnd);
}

void myShowWindow()
{
	ShowWindow(indexHWnd, SW_NORMAL);
}

void myMessageRoute()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK IndexWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT id;
	switch (message)
	{
	case WM_COMMAND:
		id = LOWORD(wParam);
		switch (id)
		{
		case BTN_BEGIN:
			assert(NULL != viewHWnd);
			capDriverConnect(viewHWnd, 0);
			capPreviewRate(viewHWnd, 60);
			capPreview(viewHWnd, TRUE);
			break;
		case BTN_END:
			assert(NULL != viewHWnd);
			capPreview(viewHWnd, FALSE);
			capDriverDisconnect(viewHWnd);
			break;
		}
		break;
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("打开摄像头"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 650 + 20, 10, 200, 50, hWnd, (HMENU)BTN_BEGIN, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		CreateWindow(TEXT("button"), TEXT("关闭摄像头"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 650 + 20, 70, 200, 50, hWnd, (HMENU)BTN_END, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		viewHWnd = capCreateCaptureWindow(viewClassName, WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 640, 480, hWnd, 1);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK viewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT re;

	HGDIOBJ old;
	switch (message)
	{
	case WM_PAINT:
		GetClientRect(hWnd, &re);

		hdc = BeginPaint(hWnd, &ps);
		old = SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Rectangle(hdc, re.left, re.top, re.right, re.bottom);
		SelectObject(hdc, old);

		EndPaint(hWnd, &ps);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
