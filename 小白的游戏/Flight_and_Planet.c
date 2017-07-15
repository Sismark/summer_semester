
#include"Sismark.h"

#define NEWNODE (Linklist)malloc(sizeof(LNode))
int flag;
typedef struct LNode {
	int x;
	int y;
	int Type;
	int TypeY;
	struct LNode *next;
}LNode, *Linklist;
/*************************************************/

/************* ȫ�ֱ��� ****************/
// ����
Linklist planet;
GAME_COORD FPlanet;
// �ɻ�
GAME_COORD flight;
// �ɻ��ƶ�����
//dirction flight_dir;
// ��Ϸ�߽磨�������£�����Ϊ0,0��
GAME_COORD boundary;
/*********** �ڲ��������� **************/
/// �ж����������Ƿ���ȡ�
int CoordEqual(PGAME_COORD one, PGAME_COORD two);
/// �жϷɻ��Ƿ�ײ
int IsFlightBoow();

/**************��������****************/
// �ж��������� GAME_COORD �Ƿ��غ�
int CoordEqual(PGAME_COORD one, PGAME_COORD two)
{
	if (one->x == two->x && one->y == two->y)
		return 1;
	return 0;
}

// ���ñ߽�����
void SetBoundary(int x, int y)
{
	flag = 0;
	boundary.x = x;
	boundary.y = y;
}
//��ñ߽�����
PGAME_COORD GetBoundary() {
	return &boundary;
}
//��÷ɻ�����
PGAME_COORD GetFlight() {
	return &flight;
}
//������ǵ�����
PGAME_COORD GetPlanet() {
	if (planet->Type == 1)  planet->x--;  
	if (planet->Type == 0)  planet->x++; 
	if (planet->x <= 0 && planet->Type == 1) planet->Type = 0;
	if (planet->x >= 600 && planet->Type == 0) planet->Type = 1;

	if (planet->TypeY == 1) planet->y--;
	if (planet->TypeY == 0) planet->y++;
	if (planet->y <= 0 && planet->TypeY == 1) planet->TypeY = 0;
	if (planet->y >= 600 && planet->TypeY == 0)planet->TypeY = 1;

	FPlanet.x = planet->x;
	FPlanet.y = planet->y;
	planet = planet->next;
	return &FPlanet;
}
// �����ɻ�
PGAME_COORD setFlight(int head_x, int head_y)
{
	flight.x = head_x;
	flight.y = head_y;

	return &flight;
}
//��������
void setPlanet() {
	int flag = 1;
	PGAME_COORD posplanet=(GAME_COORD*)malloc(sizeof(PGAME_COORD));
	planet = NEWNODE;
	planet->next = NULL;
	planet->x = planet->y=planet->Type=planet->TypeY = 0;
	Linklist temp;
	Linklist q;
	q = planet;
	
	for (int i = 0; i < NUMBER_PLANET;i++) {
		temp = NEWNODE;
		temp->x = temp->y =temp->Type=temp->TypeY= 0;
		temp->next = NULL;

		temp->x = rand() % boundary.x;
		temp->y = rand() % boundary.y;
		if (temp->x >= 200 && temp->x <= 350 && temp->y >= 200 && temp->y <= 350) { temp->x -= 150; temp->y -= 150; }
		if (temp->x > 350 && temp->x <= 500 && temp->y > 350 && temp->y <= 500) { temp->x += 150; temp->y += 150; }
		posplanet->x = temp->x;
		posplanet->y = temp->y;

		if (temp->x > 250) temp->Type = 1;
		if (temp->x < 250) temp->Type = 0;
		if (temp->y > 250) temp->TypeY = 1;
		if (temp->y < 250) temp->TypeY = 0;

		q->next = temp;
		q = q->next;
	}
	q->next = planet;
	//Fuck = planet->next;
}
//�жϷɻ��Ƿ�ը
int IsFlightBoow()
{
	LNode * p = planet->next;
	/// �ж��Ƿ�����ǽ
	if (flight.x < 0 || flight.x + WIDTH_FLIGHT / 2 > boundary.x ||
		flight.y < 0 || flight.y + HIGH_FLIGHT / 2> boundary.y)
	{
		return FLIGHT_BOOW;
	}
	/// �ж��Ƿ���������
	for (int i = 0; i<NUMBER_PLANET; i++) {
		if (planet->x > flight.x - WIDTH_FLIGHT / 2 &&planet->x < flight.x+WIDTH_FLIGHT/2 && planet->y >(flight.y - HIGH_FLIGHT / 2) &&planet->y < (flight.y + HIGH_FLIGHT/2)) 
			return FLIGHT_BOOW;
		p = p->next;
	}
	return FLIGHT_MOVED;
}
//��������
void ListDistoryAndFree()
{
	LNode *p = planet;
	while (planet != NULL) {
		planet = planet->next;
		free(p);
		p = planet;
	}
}
//�ı�ɻ��ķ���
void MoveFlight(dirction dir){
	switch (dir) {
	case FLIGHT_UP:
		flight.y = flight.y - FLIGHT_MOVE;
		flight.x = flight.x;
		break;
	case FLIGHT_DOWN:
		flight.y = flight.y + FLIGHT_MOVE;
		flight.x = flight.x;
		break;
	case FLIGHT_LEFT:
		flight.y = flight.y ;
		flight.x = flight.x - FLIGHT_MOVE;
		break;
	case FLIGHT_RIGHT:
		flight.y = flight.y;
		flight.x = flight.x + FLIGHT_MOVE;
		break;
	}			
}