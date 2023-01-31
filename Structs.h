#pragma once

typedef struct
{
	int x;	// X-axis position (column)
	int y;	// Y-axis position (row)

}Position;

typedef struct Stats
{
	int dmg;	
	int hp;		
	int maxHp;	
	int lvl;	
	int xp;		
}Stats;

struct Player
{
	int countFood;
	int countOfCoin;
	Position pos;	
	Stats stats;	
} link;

struct Enemy
{
	char type;		// Enemy symbol
	Position pos;	
	Stats stats;	
} *enemy = NULL;

struct Map
{
	char** map = NULL;				// Map array
	int mapRowSize = 0;		// Y-axis size (row)
	int mapColSize = 0;		// X-axis size (column)
	int countNumberOfEnemy = 0;
}pointOnMap;

struct MapSizes			// This structure is made to simulate the character lighting his way with a torch
{
	int minRow = 0;		// The minimum Y-axis coordinates of the points that the player can see
	int minCol = 0;		// The minimum coordinates of the points on the X axis that the player can see
	int maxRow;			// The maximum coordinates of the points along the Y axis that the player can see
	int maxCol;			// The maximum coordinates of the points on the X axis that the player can see
}newMapSize;

struct Ranking
{
	char gameOver[6];
	char playerName[20];
	int countOfKilledEnemys;
	int countOfCoins;
	int lvl;
	int countResivetHits = 0;
} rank, *arrRank;

struct Message
{
	char mess[80];
} message;

int sizeRank = 0;

/* Creating map functions */
void SetDefaultMapSizes();		
void CreateMap();				
void FillMap();					
void CreateEnemy();
void SetObjectParameters();

/* Gameplay functions */
void GamePlayProcessing();
void SetPlayerVision();				// The function of changing the field of view of the character
void DyeingSymbols(int i, int j);
void PrintMap();
void OpenDoors(int flag);

/* Player functions */
void MovePlayer(char movement);
void AttackPlayer(int id);
int DeathPlayer();
void SystemOfLevelUps();
void GameOver(int param);

/* Enemy functions */
void MoveEnemy();
void AttackEnemy(int id);
void DeathEnemy(int id);

/* Menu functions */
void GameMenu();
void OutputRankingTable();
void TittleArt();
void OutputInfo();
void ChoiceMenu(int x, int y);
void ReadRank();
void WriteRank();
void CreateRank();

/* Frame and Update screen functions */
void ClearScreen();
void PrintFrameTop(int lenght);
void PrintFrameSide();
void PrintFrameBottom(int lenght);
void Cursor();