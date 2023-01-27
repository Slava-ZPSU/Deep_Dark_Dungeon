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
	Position pos;	
	Stats stats;	
} link;

struct Enemy
{
	char type;		// Enemy symbol
	Position pos;	
	Stats stats;	
} enemy[17];

struct Map
{
	char** map;				// Map array
	int mapRowSize = 0;		// Y-axis size (row)
	int mapColSize = 0;		// X-axis size (column)
}pointOnMap;

struct MapSizes			// This structure is made to simulate the character lighting his way with a torch
{
	int minRow = 0;		// The minimum Y-axis coordinates of the points that the player can see
	int minCol = 0;		// The minimum coordinates of the points on the X axis that the player can see
	int maxRow;			// The maximum coordinates of the points along the Y axis that the player can see
	int maxCol;			// The maximum coordinates of the points on the X axis that the player can see
}newMapSize;

/* Creating map */
void SetDefaultMapSizes();		// Function for determining map dimensions
void CreateMap();				// Function for creating a dynamic array for a map
void FillMap();					// Function that writes a map from a file into a two-dimensional map array
/* Gameplay */
void GamePlayProcessing();			// Main function
void MovePlayer(char movement);		// Player move function
void PrintMap();					// Output function
void SetPlayerVision();				// The function of changing the field of view of the character
void DyeingSymbols(int i, int j);	// Character coloring function
void SetObjectParameters();			// Function where structure objects are created
void MoveEnemy();					// Enemy move function
void AttackPlayer(int id);
void AttackEnemy(int id);
int DeathPlayer();
int DeathEnemy(int id, int enemyCount);
void OpenDoors(int flag);
void SystemOfLevelUps();