#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include "Structs.h"
#include "Game_Menu.h"

int main()
{
	srand(time(NULL));

	//TittleArt();
	//system("pause");

	SetDefaultMapSizes(); // Creating map

	GamePlayProcessing(); // Gameplay
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		free(pointOnMap.map[i]);
	}
	free(pointOnMap.map);
	return 0;
}

void SetDefaultMapSizes()
{
	char ch;	// A variable that is needed to accurately count the number of rows and columns
	FILE* fp = fopen("DungeonMap.txt", "r");

	/* Integrity check */
	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	/* The process of calculating map dimensions */
	while ((ch = fgetc(fp)) != EOF) {
		pointOnMap.mapColSize++;
		if (ch == '\n') {
			pointOnMap.mapRowSize++;
			pointOnMap.mapColSize = 1;
		}
	}

	fclose(fp);
	CreateMap();	// Creating array
}
void CreateMap()
{
	pointOnMap.map = (char**)malloc(sizeof(char*) * pointOnMap.mapRowSize);
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		pointOnMap.map[i] = (char*)malloc(sizeof(char) * pointOnMap.mapColSize);
	}
	FillMap(); // Filling the array
}
void FillMap()
{
	FILE* fp = fopen("DungeonMap.txt", "r");

	/* Integrity check */
	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	/* The process of filling the array */
	for (int i = 0; i < pointOnMap.mapRowSize; i++)
	{
		for (int j = 0; j < pointOnMap.mapColSize; j++) {
			pointOnMap.map[i][j] = getc(fp);
			if (pointOnMap.map[i][j] == '\n') {
				pointOnMap.map[i][j] = ' ';
			}
		}
	}
	fclose(fp);
}

void GamePlayProcessing()
{
	int deathFlag = 0;

	SetObjectParameters();	// Creation of objects

	do
	{
		SystemOfLevelUps();

		system("cls");
		PrintMap();

		MovePlayer((char)tolower(_getch()));					// Reading the player's direction of movement
		MoveEnemy();
		//deathFlag = DeathPlayer();
	} while ((link.pos.y != 14 || link.pos.x != 25) && deathFlag == 0);		// To complete the game, you need to reach the treasures
}

void SetObjectParameters()
{
	int id = 0;
	char type = NULL;
	int hp = NULL;
	int dmg = NULL;
	int xp = NULL;

	/* Player */
	link = { 1, 35, 13, 5, 10, 10, 1, 0 };

	/* Enemys */
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		for (int j = 0; j < pointOnMap.mapColSize; j++) {
			if (pointOnMap.map[i][j] == 'R' || pointOnMap.map[i][j] == 'S' || pointOnMap.map[i][j] == 'K' || pointOnMap.map[i][j] == 'O' || pointOnMap.map[i][j] == 'D') {
				if (pointOnMap.map[i][j] == 'K') {
					type = 'K';
					dmg = 4;
					hp = 40;
					xp = 20;
				}
				else if (pointOnMap.map[i][j] == 'S') {
					type = 'S';
					dmg = 2;
					hp = 10;
					xp = 15;
				}
				else if (pointOnMap.map[i][j] == 'O') {
					type = 'O';
					dmg = 6;
					hp = 60;
					xp = 10;
				}
				else if (pointOnMap.map[i][j] == 'R') {
					type = 'R';
					dmg = 1;
					hp = 7;
					xp = 20;
				}
				else {
					type = 'D';
					dmg = 10;
					hp = 100;
				}

				enemy[id] = { type, j, i, dmg, hp };
				enemy[id].stats.xp = xp;
				id++;
			}
		}
	}
}
void DyeingSymbols(int i, int j)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Coloring characters */
	if (pointOnMap.map[i][j] == '@') {
		printf("\033[0;36m");
	}
	else if (pointOnMap.map[i][j] == 'R' || pointOnMap.map[i][j] == 'S' || pointOnMap.map[i][j] == 'K' || pointOnMap.map[i][j] == 'O') {
		SetConsoleTextAttribute(hConsole, 13);
	}
	else if (pointOnMap.map[i][j] == 'D') {
		SetConsoleTextAttribute(hConsole, 2);
	}
	else if (pointOnMap.map[i][j] == 'G') {
		SetConsoleTextAttribute(hConsole, 6);
	}
	else if (pointOnMap.map[i][j] == '.') {
		SetConsoleTextAttribute(hConsole, 14);
	}
	else if (pointOnMap.map[i][j] == '=' || pointOnMap.map[i][j] == '+') {
		SetConsoleTextAttribute(hConsole, 14);
	}
	else if (pointOnMap.map[i][j] == '~') {
		SetConsoleTextAttribute(hConsole, 4 | BACKGROUND_RED | BACKGROUND_INTENSITY);
	}
	else if (pointOnMap.map[i][j] == '#') {
		SetConsoleTextAttribute(hConsole, 8);
	}
	else if (pointOnMap.map[i][j] == ' ') {
		SetConsoleTextAttribute(hConsole, 15);
	}
}
void SetPlayerVision()
{
	/* Change the player's view depending on the character's position */
	newMapSize.minRow = link.pos.y - 3;
	newMapSize.minCol = link.pos.x - 3;
	newMapSize.maxRow = link.pos.y + 4;
	newMapSize.maxCol = link.pos.x + 4;
}
void PrintMap()
{
	/* I transfer the maximum map size to the structure fields, which reduces the player's visibility */
	newMapSize.maxRow = pointOnMap.mapRowSize;
	newMapSize.maxCol = pointOnMap.mapColSize;

	//SetPlayerVision();	// Change the character's viewport

	/* Output map in console */
	for (int i = newMapSize.minRow; i < newMapSize.maxRow; i++) {
		for (int j = newMapSize.minCol; j < newMapSize.maxCol; j++) {
			DyeingSymbols(i, j);
			printf("%2c", pointOnMap.map[i][j]);
		}
		printf("\n");
	}
	printf("\nHP - %d/%d\tDMG - %d\tLVL - %d\tXP - %d\tCOUNT OF FOOD - %d", link.stats.hp, link.stats.maxHp, link.stats.dmg, link.stats.lvl, link.stats.xp, link.countFood);
}
void MovePlayer(char movement)
{
	int row = link.pos.y;
	int col = link.pos.x;

	pointOnMap.map[link.pos.y][link.pos.x] = '.';		// The character has moved to a new position, so the floor occupies the previous position

	/* The process of character movement */
	switch (movement) {
	case 'w':
		if (pointOnMap.map[link.pos.y - 1][link.pos.x] != '#' && pointOnMap.map[link.pos.y - 1][link.pos.x] != '~' && pointOnMap.map[link.pos.y - 1][link.pos.x] != '+') {
			link.pos.y--;
		}
		break;
	case 's':
		if (pointOnMap.map[link.pos.y + 1][link.pos.x] != '#' && pointOnMap.map[link.pos.y + 1][link.pos.x] != '~' && pointOnMap.map[link.pos.y + 1][link.pos.x] != '+') {
			link.pos.y++;
		}
		break;
	case 'a':
		if (pointOnMap.map[link.pos.y][link.pos.x - 1] != '#' && pointOnMap.map[link.pos.y][link.pos.x - 1] != '~' && pointOnMap.map[link.pos.y][link.pos.x - 1] != '+') {
			link.pos.x--;
		}
		break;
	case 'd':
		if (pointOnMap.map[link.pos.y][link.pos.x + 1] != '#' && pointOnMap.map[link.pos.y][link.pos.x + 1] != '~' && pointOnMap.map[link.pos.y][link.pos.x + 1] != '+') {
			link.pos.x++;
		}
		break;
	case 'e':
		if (link.countFood > 0) {
			link.countFood--;
			if (link.stats.hp + 5 <= link.stats.maxHp) {
				link.stats.hp += 5;
			}
			else {
				link.stats.hp += link.stats.maxHp - link.stats.hp;
			}
		}
	}

	/* Check if the next cell is not a door */
	if (pointOnMap.map[link.pos.y][link.pos.x] == '=') {
		/* Going through the door */
		if (movement == 'w' && pointOnMap.map[link.pos.y - 1][link.pos.x] == '.') {
			link.pos.y--;
		}
		else if (movement == 's' && pointOnMap.map[link.pos.y + 1][link.pos.x] == '.') {
			link.pos.y++;
		}
		else if (movement == 'a' && pointOnMap.map[link.pos.y][link.pos.x - 1] == '.') {
			link.pos.x--;
		}
		else {
			link.pos.x++;
		}
	}

	if (pointOnMap.map[link.pos.y][link.pos.x] == 'F') {
		link.countFood++;
	}

	for (int i = 0; i < 17; i++) {
		if (link.pos.x == enemy[i].pos.x && link.pos.y == enemy[i].pos.y) {
			AttackPlayer(i);
			link.pos.x = col;
			link.pos.y = row;
		}
	}
	pointOnMap.map[link.pos.y][link.pos.x] = '@';	// The character has moved to a new position
}
void MoveEnemy()
{
	int enemyRadius = 6;	// enemy vision radius
	int dx;					// delta column
	int dy;					// delta row
	int row;
	int col;
	int enemyCount = 17;

	for (int i = 0; i < enemyCount; i++) {
		dx = enemy[i].pos.x - link.pos.x;
		dy = enemy[i].pos.y - link.pos.y;
		row = enemy[i].pos.y;
		col = enemy[i].pos.x;

		pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x] = '.';

		if ( sqrt(dx*dx + dy*dy) <= enemyRadius) {
			if (enemy[i].pos.y < link.pos.y && pointOnMap.map[enemy[i].pos.y + 1][enemy[i].pos.x] == '.' || pointOnMap.map[enemy[i].pos.y + 1][enemy[i].pos.x] == '@') {
				enemy[i].pos.y++;
			}
			else if (enemy[i].pos.x < link.pos.x && pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x + 1] == '.' || pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x + 1] == '@') {
				enemy[i].pos.x++;
			}
			else if (enemy[i].pos.y > link.pos.y && pointOnMap.map[enemy[i].pos.y - 1][enemy[i].pos.x] == '.' || pointOnMap.map[enemy[i].pos.y - 1][enemy[i].pos.x] == '@') {
				enemy[i].pos.y--;
			}
			else if (enemy[i].pos.x > link.pos.x && pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x - 1] == '.' || pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x - 1] == '@') {
				enemy[i].pos.x--;
			}
		}

		if (enemy[i].pos.x == link.pos.x && enemy[i].pos.y == link.pos.y) {
			AttackEnemy(i);
			enemy[i].pos.x = col;
			enemy[i].pos.y = row;
		}

		enemyCount = DeathEnemy(i, enemyCount);

		pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x] = enemy[i].type;
	}
}
void AttackPlayer(int id)
{
	int chance = rand() % 101; // Chance of a successful attack
	//if (chance < 51) {
		enemy[id].stats.hp -= link.stats.dmg;
	//}
}
void AttackEnemy(int id)
{
	int chance = rand() % 101; // Chance of a successful attack
	if (chance > 49) {
		link.stats.hp -= enemy[id].stats.dmg;
	}
}
int DeathPlayer()
{
	if (link.stats.hp <= 0) {
		return 1;
	}
	return 0;
}
int DeathEnemy(int id, int enemyCount)
{
	if (enemy[id].stats.hp <= 0) {
		if (id == 0) {
			OpenDoors(1);
		}
		if (enemy[id].type == 'D') {
			OpenDoors(2);
		}
		enemy[id].pos.x = 100;
		enemy[id].pos.y = 100;
		link.stats.xp += enemy[id].stats.xp;
		for (int i = id; i < enemyCount - 1; i++) {
			enemy[i] = enemy[i + 1];
		}
		enemyCount--;
	}
	return enemyCount;
}
void OpenDoors(int flag)
{
	if (flag == 1) {
		pointOnMap.map[5][32] = '=';
	}
	if (flag == 2) {
		pointOnMap.map[22][27] = '=';
	}
}
void SystemOfLevelUps()
{
	if (link.stats.xp >= 40 && link.stats.lvl <= 6) {
		link.stats.xp -= 40;
		link.stats.lvl++;
		if (link.stats.hp + link.stats.maxHp / 3 <= link.stats.maxHp) {
			link.stats.hp += link.stats.maxHp / 3;
		}
		else {
			link.stats.hp += link.stats.maxHp / 3 - link.stats.hp;
		}
	}
	switch (link.stats.lvl) {
	case 2:
		link.stats.dmg = 7;
		link.stats.maxHp = 18;
		break;
	case 3:
		link.stats.dmg = 10;
		link.stats.maxHp = 36;
		break;
	case 4:
		link.stats.dmg = 14;
		link.stats.maxHp = 42;
		break;
	case 5:
		link.stats.dmg = 16;
		link.stats.maxHp = 50;
		break;
	case 6:
		link.stats.dmg = 18;
		link.stats.maxHp = 60;
	}
}