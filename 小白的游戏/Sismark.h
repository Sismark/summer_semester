#include<windows.h>
#define FLIGHT_MOVED		0
#define FLIGHT_BOOW			1
#define NUMBER_PLANET 50
#define SIZE_PLANET (3 + (rand()%2 ? 3 : 0))
#define HIGH_FLIGHT 60
#define WIDTH_FLIGHT 60
#define FLIGHT_MOVE 3
#define PLANET_MOVE 0.01


// 飞机移动的方向
typedef enum _dirction
{
	FLIGHT_UP,
	FLIGHT_DOWN,
	FLIGHT_LEFT,
	FLIGHT_RIGHT,
}dirction;

// 游戏坐标
typedef struct _GAME_COORD
{
	int x;
	int y;
}GAME_COORD, *PGAME_COORD;

int CoordEqual(PGAME_COORD one, PGAME_COORD two);//判断两个坐标是否重合
void SetBoundary(int x, int y);//设置边界坐标
PGAME_COORD GetBoundary();//获得边界坐标
PGAME_COORD setFlight(int head_x, int head_y);//创建飞机
PGAME_COORD GetFlight();//获得飞机坐标
void setPlanet();//创建行星
PGAME_COORD GetPlanet();//获得行星坐标
int IsFlightBoow();
void ListDistoryAndFree();//销毁行星
void MoveFlight(dirction dir);//飞机移动
int GetTime();
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk);
void OnKeyUp(DWORD vk);
void CreateGame(HWND hwnd,  int boundary_x, int boundary_y, int init_x, int init_y);