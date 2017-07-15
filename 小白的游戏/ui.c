#include<windows.h>
#include<tchar.h>
#include "Sismark.h"
#pragma comment (lib, "Winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#define TIMER_ID			12340     
//【关于背景】
#define MAX_X 600
#define MAX_Y 600
#define BITMAP_FILE_BK		"cloud.bmp"
#define CLASS_NAME_BK "Sismark"
//【关于飞机】
#define INIT_X		300	// 飞机的初始位置
#define INIT_Y	 300//飞机的初始位置
#define INIT_DIR	FLIGHT_UP
#define COLOR_FLIGHT RGB(0,255,0)
#define COLOR_BOUNDARY RGB(255,0,0)
//【关于行星】
#define COLOR_PLANET RGB(rand()%256,rand()%256,rand()%256)
#define TRANS_BK_COLOR		RGB(255,255,255)
//【关于字体】
#define COLOR_FONT			RGB(0,245,255)
//【全局变量】
HINSTANCE hinst;
RECT rectBoundary;
HBITMAP hbmpFighter;
HBITMAP hbmpBackground;
//【函数声明】
void GamePaint(HWND hwnd);
void BackgroundCreat(HWND hwnd);
void GamePaint(HWND hwnd) {
	HPEN hpen;
	HDC hdc, hdcmem, hdcBitmapSrc;

	HBRUSH hbrushPlanet;
	HBRUSH hOldBrush;

	BITMAP bmp;
	RECT rect;

	PGAME_COORD pFlight;
	PGAME_COORD lpPlanet;

	int size;

	GetClientRect(hwnd, &rect);//该函数获取窗口客户区的大小

	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc); //该函数创建一个与指定设备兼容的内存设备上下文环境
	hdcBitmapSrc = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmapSrc, hbmpFighter);
	
	// 创建需要用到的PEN和BRUSH

	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN， PS_NULL表示不可见
	SelectObject(hdcmem, hpen);
	/************************************画背景**********************************************/
		
	    BackgroundCreat(hwnd);
	    SelectObject(hdcmem, hbmpBackground);

		
//【画飞机】

	pFlight = GetFlight();
	GetObject(hbmpFighter, sizeof(BITMAP), &bmp);

	TransparentBlt(hdcmem,
		pFlight->x- WIDTH_FLIGHT/2,
		pFlight->y- HIGH_FLIGHT/2,
		WIDTH_FLIGHT,
		HIGH_FLIGHT,
		hdcBitmapSrc,
		0, 0, bmp.bmWidth, bmp.bmHeight,
		RGB(0, 0, 0));
	//【画行星】

	for (int i = 0; i < NUMBER_PLANET; i++) {
		hbrushPlanet = CreateSolidBrush(COLOR_PLANET); // RGB颜色，实心BRUSH
		hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushPlanet);
		lpPlanet = GetPlanet();
		size = SIZE_PLANET;
		Ellipse(hdcmem,
			lpPlanet->x- size/2,
			lpPlanet->y- size/2,
			lpPlanet->x+ size/2,
			lpPlanet->y+ size/2
		);
		DeleteObject(hbrushPlanet);
	}
	// 在内存DC中画完，一次输出的窗口DC上。
	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	// 回收资源

	DeleteObject(hdcmem);
	DeleteObject(hdcBitmapSrc);
	DeleteObject(hpen);
	DeleteObject(hOldBrush);

	//释放占用的DC等系统资源。

	ReleaseDC(hwnd, hdc);
}
void FlightCreat(HWND hwnd) {
	hbmpFighter = LoadImage(NULL, "fight1.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmpFighter == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
	}
	SetFocus(hwnd);
}
//【回调函数】
void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;
	PGAME_COORD pCoordBoundary = GetBoundary();

	// 设置游戏边界
	rectBoundary.left =0 ;
	rectBoundary.top = 0;
	rectBoundary.right = pCoordBoundary->x;
	rectBoundary.bottom = pCoordBoundary->y;

	// 计算上下左右角的位置
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,
		0,
		0,
		pCoordBoundary->x,
		pCoordBoundary->y,
		TRUE);
	SetFocus(hwnd);
}
void GameOver(HWND hwnd) {
	HPEN hpen;
	HDC hdc, hdcmem;
	HFONT hFont, hOldFont;//字体
	BITMAP bmp;
	RECT rect;

	GetClientRect(hwnd, &rect);//该函数获取窗口客户区的大小

	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc); //该函数创建一个与指定设备兼容的内存设备上下文环境

	// 创建需要用到的PEN和BRUSH

	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN， PS_NULL表示不可见
	SelectObject(hdcmem, hpen);
	/************************************画背景**********************************************/

	SelectObject(hdcmem, hbmpBackground);

	/**********************************字体*************************************************/
	hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

	// 将这个FONT对象放入DC中
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "用时:%ds", GetTime()/50);
		// 设置输出颜色
		COLORREF crOld=SetTextColor(hdcmem,COLOR_FONT);
		int nOldMode = SetBkMode(hdcmem,TRANSPARENT);
		// 输出字符串。
		TextOut(hdcmem, 200, 250,
			szSourceInfo, lstrlen(szSourceInfo));
		// 输出完成，将原来的字体对象放回DC中
		SelectObject(hdcmem, hOldFont);
	}

	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hFont);
	DeleteObject(hOldFont);
	//释放占用的DC等系统资源。

	ReleaseDC(hwnd, hdc);
}
void BackgroundCreat(HWND hwnd) {
	hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmpBackground == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
	}
	//MoveWindow(hwnd, 0, 0, MAX_X, MAX_Y, TRUE);
	SetFocus(hwnd);
}
LONG CALLBACK MainWndProc(
	HWND hwnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam) {
	switch (msg)
	{
	case WM_CREATE:
		CreateGame(hwnd,
			MAX_X, MAX_Y,
			INIT_X, INIT_Y);
		FlightCreat(hwnd);
		ReSizeGameWnd(hwnd);
		break;
	case WM_PAINT:
		GamePaint(hwnd);
		break;
	case WM_KEYDOWN:
		OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		OnKeyUp(wParam);
		break;
	case WM_TIMER:
		GamePaint(hwnd);
		OnTimer(hwnd);
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}
//【入口函数】
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// 窗口的菜单的资源名。
	wc.lpszMenuName = "MainMenu";
	// 给窗口类起一个名字，在创建窗口时需要这个名字。
	wc.lpszClassName = "MainWClass";

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	// 窗口注册成功，继续运行。


	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",			// 窗口类名，必须是已经注册了的窗口类
		"Sismark!!",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	// 窗口创建成功，继续运行。

	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
