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
	char** map = NULL;		
	int mapRowSize = 0;		
	int mapColSize = 0;		
	int countNumberOfEnemy = 0;
}pointOnMap;

struct MapSizes			// This structure is made to simulate the character lighting his way with a torch
{
	int minRow = 0;		
	int minCol = 0;		
	int maxRow;			
	int maxCol;			
}newMapSize;

struct Ranking
{
	char gameOver[6];
	char playerName[20];
	int countOfKilledEnemys;
	int countOfCoins;
	int lvl;
	int countResivetHits = 0;
	float time;
	int score = 0;
} rank, *arrRank = NULL;

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
void SortRank();
void CreateRank();

/* Frame and Update screen functions */
void ClearScreen();
void HideCursor();
void PrintFrameTop(int lenght);
void PrintFrameSide();
void PrintFrameBottom(int lenght);
void Cursor();