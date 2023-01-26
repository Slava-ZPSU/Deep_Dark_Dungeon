#pragma once

typedef struct
{
	int x;	// Позиція по осі Х (стовпець)
	int y;	// Позиція по осі Y (рядок)

}Position;

typedef struct Stats
{
public:
	int dmg;	// Урон 
	int hp;		// Очки життя
	int maxHp;	// Максимальна к-ість очків життя
	int lvl;	// Рівень
	int xp;		// Очки досвіду
	int maxXp;	// Максимальна к-ість очків досвіду
}Stats;

struct Player
{
	int foodCount;	// Лічильник їжі (трохи згодом їжа буде відновлювати очки життя)
	Position pos;	// Ініціалізація вкладенної структури
	Stats stats;	// Ініціалізація вкладенної структури
} link;

struct Enemy
{
	char type;		// Символ ворога
	Position pos;	// Ініціалізація вкладенної структури
	Stats stats;	// Ініціалізація вкладенної структури
	//Enemy* next;	// Вказівник на наступного ворога (можливо заміню на масив)
} enemy[4];

struct Map
{
	char** map;				// Масив для мапи
	int mapRowSize = 0;		// Розмір мари по осі Y (рядках)
	int mapColSize = 0;		// Розмір мари по осі Х (стовпцях)
}pointOnMap;

struct DinamicMapSizes	// Ця структура зроблена для імітації того, що персонаж підсвітлює собі шлях смолоскипом
{
	int rowMin = 0;		// Мінімальні координати точок по осі Y, що бачить гравець
	int colMin = 0;		// Мінімальні координати точок по осі Х, що бачить гравець
	int rowMax;			// Максимальні координати точок по осі Y, що бачить гравець
	int colMax;			// Максимальні координати точок по осі Х, що бачить гравець
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