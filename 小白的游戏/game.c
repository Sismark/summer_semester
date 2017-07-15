
/************** 头文件 ****************/
#include <Windows.h>
#include<stdio.h>
#include "Sismark.h"
/************** 宏定义 ****************/
// 计时器ID。
#define TIMER_ID 12340
#define SPEED_TIME 10
int Up;
int Down;
int Left;
int Right;
int Time = 0;
// 游戏控制的一个主要流程。
// 当计时器发生时进行的处理逻辑。
int GetTime() { return Time; }//获得时间
void OnTimer(HWND hwnd)
{
	if (Up == 1) MoveFlight(FLIGHT_UP);
	if(Right==1) MoveFlight(FLIGHT_RIGHT);
	if(Down==1) MoveFlight(FLIGHT_DOWN);
	if(Left==1) MoveFlight(FLIGHT_LEFT);
	switch (IsFlightBoow())
	{
		// 如果飞机炸了
	case FLIGHT_BOOW:
		// 首先关闭计时器，避免在计时器的驱动下再次调用本函数
		KillTimer(hwnd, TIMER_ID);
		// 然后通知玩家，Game Over了，退出进程。
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


// 当用于操作时进行的逻辑处理。
// 本游戏只使用到了键盘上下左右键控制。
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
// 游戏的初始化，
// 创建游戏的内部数据结构和系统对象。
void CreateGame(HWND hwnd, // 主窗口句柄
	int boundary_x, int boundary_y,
	int init_x, int init_y)
{
	//RECT rect;
	//GetClientRect(hwnd,&rect);
	// 设置游戏的边界
	SetBoundary(boundary_x, boundary_y);


	setFlight(init_x, init_y);

	setPlanet();//创建行星

	// 创建一个计时器
	// 每经过 dwTimerElapse 毫秒，hwnd窗口（主窗口）就会收到一个WM_TIMER消息。
	// 计时器是驱动本游戏进行的主要时间线。
	// dwTimerElapse变量影响游戏进行的快慢变化。
	SetTimer(hwnd, TIMER_ID, SPEED_TIME, NULL);

}