#include<windows.h>
#define FLIGHT_MOVED		0
#define FLIGHT_BOOW			1
#define NUMBER_PLANET 50
#define SIZE_PLANET (3 + (rand()%2 ? 3 : 0))
#define HIGH_FLIGHT 60
#define WIDTH_FLIGHT 60
#define FLIGHT_MOVE 3
#define PLANET_MOVE 0.01


// �ɻ��ƶ��ķ���
typedef enum _dirction
{
	FLIGHT_UP,
	FLIGHT_DOWN,
	FLIGHT_LEFT,
	FLIGHT_RIGHT,
}dirction;

// ��Ϸ����
typedef struct _GAME_COORD
{
	int x;
	int y;
}GAME_COORD, *PGAME_COORD;

int CoordEqual(PGAME_COORD one, PGAME_COORD two);//�ж����������Ƿ��غ�
void SetBoundary(int x, int y);//���ñ߽�����
PGAME_COORD GetBoundary();//��ñ߽�����
PGAME_COORD setFlight(int head_x, int head_y);//�����ɻ�
PGAME_COORD GetFlight();//��÷ɻ�����
void setPlanet();//��������
PGAME_COORD GetPlanet();//�����������
int IsFlightBoow();
void ListDistoryAndFree();//��������
void MoveFlight(dirction dir);//�ɻ��ƶ�
int GetTime();
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk);
void OnKeyUp(DWORD vk);
void CreateGame(HWND hwnd,  int boundary_x, int boundary_y, int init_x, int init_y);