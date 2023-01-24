#pragma once

typedef struct
{
	int X;
	int Y;

}Position;

typedef struct Stats
{
public:
	int DMG;
	int HP;
	int MaxHP;
	int LVL;
	int XP;
	int MaxXP;
}Stats;

typedef struct
{
	int FoodCount;
	Position Post;
	Stats Stats;
} Player;

typedef struct Enemy
{
	Position Post;
	Stats Stats;
	Enemy* Next;
} Enemy;

typedef struct Map
{
	char** Map;
	int Row = 0;
	int Col = 0;
} Map;

void SetDefaultMapSizes(Map* map);
void CreateMap(Map* map);
void FillingMap(Map* map);
void PrintMap(Map* map);