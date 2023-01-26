#pragma once

typedef struct
{
	int x;	// ������� �� �� � (��������)
	int y;	// ������� �� �� Y (�����)

}Position;

typedef struct Stats
{
public:
	int dmg;	// ���� 
	int hp;		// ���� �����
	int maxHp;	// ����������� �-���� ���� �����
	int lvl;	// г����
	int xp;		// ���� ������
	int maxXp;	// ����������� �-���� ���� ������
}Stats;

struct Player
{
	int foodCount;	// ˳������� �� (����� ������ ��� ���� ����������� ���� �����)
	Position pos;	// ����������� ��������� ���������
	Stats stats;	// ����������� ��������� ���������
} link;

struct Enemy
{
	char type;		// ������ ������
	Position pos;	// ����������� ��������� ���������
	Stats stats;	// ����������� ��������� ���������
	//Enemy* next;	// �������� �� ���������� ������ (������� ����� �� �����)
} enemy[4];

struct Map
{
	char** map;				// ����� ��� ����
	int mapRowSize = 0;		// ����� ���� �� �� Y (������)
	int mapColSize = 0;		// ����� ���� �� �� � (��������)
}pointOnMap;

struct DinamicMapSizes	// �� ��������� �������� ��� ������� ����, �� �������� �������� ��� ���� �����������
{
	int rowMin = 0;		// ̳������ ���������� ����� �� �� Y, �� ������ �������
	int colMin = 0;		// ̳������ ���������� ����� �� �� �, �� ������ �������
	int rowMax;			// ���������� ���������� ����� �� �� Y, �� ������ �������
	int colMax;			// ���������� ���������� ����� �� �� �, �� ������ �������
}newMapSize;

/* ��������� ���� */
void SetDefaultMapSizes();		// ������� ��� ���������� ������ ����
void CreateMap();				// ������� ��� ��������� ���������� ������
void FillMap();					// ������� �� ������ ���� � ����� � ���������� ����� ����
/* ������� ������ */
void GamePlayProcessing();			// ������� �������
void MovePlayer(char movement);		// ������� ����������� ���������
void PrintMap();					// �������� ������
void SetPlayerVision();				// ������� ���� ������ �������� ���������
void DyeingSymbols(int i, int j);	// ������� ���������� �������
void SetObjectParameters();			// ������� �� ����������� ��'���� ��������
void MoveEnemy();