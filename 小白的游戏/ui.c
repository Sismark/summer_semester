#include<windows.h>
#include<tchar.h>
#include "Sismark.h"
#pragma comment (lib, "Winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#define TIMER_ID			12340     
//�����ڱ�����
#define MAX_X 600
#define MAX_Y 600
#define BITMAP_FILE_BK		"cloud.bmp"
#define CLASS_NAME_BK "Sismark"
//�����ڷɻ���
#define INIT_X		300	// �ɻ��ĳ�ʼλ��
#define INIT_Y	 300//�ɻ��ĳ�ʼλ��
#define INIT_DIR	FLIGHT_UP
#define COLOR_FLIGHT RGB(0,255,0)
#define COLOR_BOUNDARY RGB(255,0,0)
//���������ǡ�
#define COLOR_PLANET RGB(rand()%256,rand()%256,rand()%256)
#define TRANS_BK_COLOR		RGB(255,255,255)
//���������塿
#define COLOR_FONT			RGB(0,245,255)
//��ȫ�ֱ�����
HINSTANCE hinst;
RECT rectBoundary;
HBITMAP hbmpFighter;
HBITMAP hbmpBackground;
//������������
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

	GetClientRect(hwnd, &rect);//�ú�����ȡ���ڿͻ����Ĵ�С

	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc); //�ú�������һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
	hdcBitmapSrc = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmapSrc, hbmpFighter);
	
	// ������Ҫ�õ���PEN��BRUSH

	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN�� PS_NULL��ʾ���ɼ�
	SelectObject(hdcmem, hpen);
	/************************************������**********************************************/
		
	    BackgroundCreat(hwnd);
	    SelectObject(hdcmem, hbmpBackground);

		
//�����ɻ���

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
	//�������ǡ�

	for (int i = 0; i < NUMBER_PLANET; i++) {
		hbrushPlanet = CreateSolidBrush(COLOR_PLANET); // RGB��ɫ��ʵ��BRUSH
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
	// ���ڴ�DC�л��꣬һ������Ĵ���DC�ϡ�
	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	// ������Դ

	DeleteObject(hdcmem);
	DeleteObject(hdcBitmapSrc);
	DeleteObject(hpen);
	DeleteObject(hOldBrush);

	//�ͷ�ռ�õ�DC��ϵͳ��Դ��

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
//���ص�������
void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	PGAME_COORD pCoordBoundary = GetBoundary();

	// ������Ϸ�߽�
	rectBoundary.left =0 ;
	rectBoundary.top = 0;
	rectBoundary.right = pCoordBoundary->x;
	rectBoundary.bottom = pCoordBoundary->y;

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
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
	HFONT hFont, hOldFont;//����
	BITMAP bmp;
	RECT rect;

	GetClientRect(hwnd, &rect);//�ú�����ȡ���ڿͻ����Ĵ�С

	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc); //�ú�������һ����ָ���豸���ݵ��ڴ��豸�����Ļ���

	// ������Ҫ�õ���PEN��BRUSH

	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN�� PS_NULL��ʾ���ɼ�
	SelectObject(hdcmem, hpen);
	/************************************������**********************************************/

	SelectObject(hdcmem, hbmpBackground);

	/**********************************����*************************************************/
	hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

	// �����FONT�������DC��
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "��ʱ:%ds", GetTime()/50);
		// ���������ɫ
		COLORREF crOld=SetTextColor(hdcmem,COLOR_FONT);
		int nOldMode = SetBkMode(hdcmem,TRANSPARENT);
		// ����ַ�����
		TextOut(hdcmem, 200, 250,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}

	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hFont);
	DeleteObject(hOldFont);
	//�ͷ�ռ�õ�DC��ϵͳ��Դ��

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
//����ں�����
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// ���ڵĲ˵�����Դ����
	wc.lpszMenuName = "MainMenu";
	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
	wc.lpszClassName = "MainWClass";

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�


	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",			// �����������������Ѿ�ע���˵Ĵ�����
		"Sismark!!",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}

	// ���ڴ����ɹ����������С�

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
