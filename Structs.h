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

struct MapSizes			// Ця структура зроблена для імітації того, що персонаж підсвітлює собі шлях смолоскипом
{
	int minRow = 0;		// Мінімальні координати точок по осі Y, що бачить гравець
	int minCol = 0;		// Мінімальні координати точок по осі Х, що бачить гравець
	int maxRow;			// Максимальні координати точок по осі Y, що бачить гравець
	int maxCol;			// Максимальні координати точок по осі Х, що бачить гравець
}newMapSize;

/* Створення мапи */
void SetDefaultMapSizes();		// Функція для визначення розмірів мапи
void CreateMap();				// Функція для створення динамічного масиву
void FillMap();					// Функція що записує мапу з файла в двовимірний масив мапи
/* Ігровий процес */
void GamePlayProcessing();			// Основна функція
void MovePlayer(char movement);		// Функція пересування персонажа
void PrintMap();					// Функцція Виводу
void SetPlayerVision();				// Функція зміни області видимості персонажа
void DyeingSymbols(int i, int j);	// Функція фарбування символів
void SetObjectParameters();			// Функція де створюються об'єкти структур
void MoveEnemy();