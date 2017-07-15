
/************** ͷ�ļ� ****************/
#include <Windows.h>
#include<stdio.h>
#include "Sismark.h"
/************** �궨�� ****************/
// ��ʱ��ID��
#define TIMER_ID 12340
#define SPEED_TIME 10
int Up;
int Down;
int Left;
int Right;
int Time = 0;
// ��Ϸ���Ƶ�һ����Ҫ���̡�
// ����ʱ������ʱ���еĴ����߼���
int GetTime() { return Time; }//���ʱ��
void OnTimer(HWND hwnd)
{
	if (Up == 1) MoveFlight(FLIGHT_UP);
	if(Right==1) MoveFlight(FLIGHT_RIGHT);
	if(Down==1) MoveFlight(FLIGHT_DOWN);
	if(Left==1) MoveFlight(FLIGHT_LEFT);
	switch (IsFlightBoow())
	{
		// ����ɻ�ը��
	case FLIGHT_BOOW:
		// ���ȹرռ�ʱ���������ڼ�ʱ�����������ٴε��ñ�����
		KillTimer(hwnd, TIMER_ID);
		// Ȼ��֪ͨ��ң�Game Over�ˣ��˳����̡�
		GameOver(hwnd);
		MessageBox(0, "Game Over", "Game Over", 0);
		ExitProcess(0);
		break;
	case FLIGHT_MOVED:
		Time+=1;
		break;
	}
	return;

}


// �����ڲ���ʱ���е��߼�����
// ����Ϸֻʹ�õ��˼����������Ҽ����ơ�
void OnKeyDown(DWORD vk)
{
	switch (vk) // virtual key value
	{
	case VK_LEFT:
		Left = 1;
		break;
	case VK_RIGHT:
		Right = 1;
		break;
	case VK_UP:
		Up = 1;
		break;
	case VK_DOWN:
		Down = 1;
		break;
	}
	return;
}
void OnKeyUp(DWORD vk)
{
	switch (vk) // virtual key value
	{
	case VK_LEFT:
		Left = 0;
		break;
	case VK_RIGHT:
		Right = 0;
		break;
	case VK_UP:
		Up = 0;
		break;
	case VK_DOWN:
		Down = 0;
		break;
	}
	return;
}
// ��Ϸ�ĳ�ʼ����
// ������Ϸ���ڲ����ݽṹ��ϵͳ����
void CreateGame(HWND hwnd, // �����ھ��
	int boundary_x, int boundary_y,
	int init_x, int init_y)
{
	//RECT rect;
	//GetClientRect(hwnd,&rect);
	// ������Ϸ�ı߽�
	SetBoundary(boundary_x, boundary_y);


	setFlight(init_x, init_y);

	setPlanet();//��������

	// ����һ����ʱ��
	// ÿ���� dwTimerElapse ���룬hwnd���ڣ������ڣ��ͻ��յ�һ��WM_TIMER��Ϣ��
	// ��ʱ������������Ϸ���е���Ҫʱ���ߡ�
	// dwTimerElapse����Ӱ����Ϸ���еĿ����仯��
	SetTimer(hwnd, TIMER_ID, SPEED_TIME, NULL);

}