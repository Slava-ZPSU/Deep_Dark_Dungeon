#pragma once

typedef struct
{
	int x;	// X-axis position (column)
	int y;	// Y-axis position (row)

}Position;

typedef struct Stats
{
public:
	int dmg;	
	int hp;		
	int maxHp;	
	int lvl;	
	int xp;		
	int maxXp;	
}Stats;

struct Player
{
	int foodCount;	
	Position pos;	
	Stats stats;	
} link;

struct Enemy
{
	char type;		// Enemy symbol
	Position pos;	
	Stats stats;	
} enemy[16];

struct Map
{
	char** map;				// Map array
	int mapRowSize = 0;		// Y-axis size (row)
	int mapColSize = 0;		// X-axis size (column)
}pointOnMap;

struct MapSizes			// �� ��������� �������� ��� ������� ����, �� �������� �������� ��� ���� �����������
{
	int minRow = 0;		// ̳������ ���������� ����� �� �� Y, �� ������ �������
	int minCol = 0;		// ̳������ ���������� ����� �� �� �, �� ������ �������
	int maxRow;			// ���������� ���������� ����� �� �� Y, �� ������ �������
	int maxCol;			// ���������� ���������� ����� �� �� �, �� ������ �������
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