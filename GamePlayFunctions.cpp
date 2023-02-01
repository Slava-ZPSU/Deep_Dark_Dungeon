#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <io.h>
#include "Structs.h"
#include "Game_Menu.h"

int main()
{
	srand(time(NULL));
	HideCursor();
	SetDefaultMapSizes();

	GameMenu();
	free(arrRank);
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		free(pointOnMap.map[i]);
	}
	free(pointOnMap.map);
	return 0;
}

void SetDefaultMapSizes()
{
	char ch;	
	FILE* fp = fopen("DungeonMap.txt", "r");
	
	/* Integrity check */
	if (fp == NULL) {							
		perror("Error: ");			
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
	CreateMap();
}
void CreateMap()
{
	pointOnMap.map = (char**)malloc(sizeof(char*) * pointOnMap.mapRowSize);
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		pointOnMap.map[i] = (char*)malloc(sizeof(char) * pointOnMap.mapColSize);
	}
}
void FillMap()
{
	FILE* fp = fopen("DungeonMap.txt", "r");	

	/* Integrity check */
	if (fp == NULL) {
		perror("Error: ");
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
	CreateEnemy();
}
void CreateEnemy()
{
	pointOnMap.countNumberOfEnemy = 0;
	for (int i = 0; i < pointOnMap.mapRowSize; i++)
	{
		for (int j = 0; j < pointOnMap.mapColSize; j++) {
			if (pointOnMap.map[i][j] == 'R' || pointOnMap.map[i][j] == 'S' || pointOnMap.map[i][j] == 'K' || pointOnMap.map[i][j] == 'O' || pointOnMap.map[i][j] == 'D') {
				pointOnMap.countNumberOfEnemy++;
			}
		}
	}
	enemy = (Enemy*)malloc(pointOnMap.countNumberOfEnemy * sizeof(Enemy));
}

void ClearScreen()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void GamePlayProcessing()
{	
	int deathFlag = 0;
	
	SetObjectParameters();
	clock_t start, finish;
	start = clock();
	do
	{
		SystemOfLevelUps();
		
		PrintMap();

		ClearScreen();
	
		MovePlayer((char)tolower(_getch()));				
		MoveEnemy();
		deathFlag = DeathPlayer();
	} while ((link.pos.y != 14 || link.pos.x != 27) && deathFlag == 0);	
	finish = clock();
	rank.time = (float)(finish - start) / CLOCKS_PER_SEC;
	GameOver(deathFlag);
}

void SetObjectParameters()
{
	int id = 0;
	char type = NULL;
	int hp = NULL;
	int dmg = NULL;
	int xp = NULL;

	/* Player */
	link = { 1, 0, 37, 13, 5, 10, 10, 1, 0 };
	
	/* Enemys */
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		for (int j = 0; j < pointOnMap.mapColSize; j++) {
			if (pointOnMap.map[i][j] == 'R' || pointOnMap.map[i][j] == 'S' || pointOnMap.map[i][j] == 'K' || pointOnMap.map[i][j] == 'O' || pointOnMap.map[i][j] == 'D') {
				if (pointOnMap.map[i][j] == 'K') {
					type = 'K';
					dmg = 4;
					hp = 35;
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
					dmg = 4;
					hp = 50;
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
					hp = 80;
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

	/* Coloring symbols */
	if (pointOnMap.map[i][j] == '@') {
		printf("\033[0;36m");
	}
	else if (pointOnMap.map[i][j] == 'R' || pointOnMap.map[i][j] == 'S' || pointOnMap.map[i][j] == 'K' || pointOnMap.map[i][j] == 'O') {
		SetConsoleTextAttribute(hConsole, 13);
	}
	else if (pointOnMap.map[i][j] == 'D') {
		SetConsoleTextAttribute(hConsole, 2);
	}
	else if (pointOnMap.map[i][j] == 'G' || pointOnMap.map[i][j] == 'C') {
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
	else if (pointOnMap.map[i][j] == 'F') {
		printf("\033[0;32m");
	}
	else {
		printf("\033[0;37m");
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

	SetPlayerVision();	// Change the character's viewport

	/* Printing Messages */
	PrintFrameTop(95);
	PrintFrameSide();
	if (strcmp(message.mess, "\0") == 1) {
		printf("\t%-80s\t", message.mess);
	}
	else {
		printf("                                                                                               ");
	}
	PrintFrameSide();	printf("\n");
	PrintFrameBottom(95);

	/* Output map in console */
	printf("\t\t\t\t\t");
	PrintFrameTop(14);
	printf("\t\t\t\t\t");
	for (int i = newMapSize.minRow; i < newMapSize.maxRow; i++) {
		for (int j = newMapSize.minCol; j < newMapSize.maxCol; j++) {
			if (j == newMapSize.minCol) {
				PrintFrameSide();
			}

			DyeingSymbols(i, j);

			printf("%2c", pointOnMap.map[i][j]);

			if (j == newMapSize.maxCol - 1) {
				PrintFrameSide();
			}
		}
		if (i < newMapSize.maxRow - 1) {
			printf("\n\033[0;37m\t\t\t\t\t\t\t\t");
		}
		else {
			printf("\n\033[0;37m\t\t\t\t\t");
		}
	}

	PrintFrameBottom(14);
	/* Printing Player Characteristics */
	PrintFrameTop(95);
	PrintFrameSide();
	if (link.stats.hp < 10) {
		printf("    HP - 0%d/%-6d", link.stats.hp, link.stats.maxHp);
	}
	else {
		printf("    HP - %d/%-6d", link.stats.hp, link.stats.maxHp);
	}
	printf("DMG - %-6dLVL - %-6dXP - %-6dCOUNT OF COIN - %-6dCOUNT OF FOOD - %-4d", link.stats.dmg, link.stats.lvl, link.stats.xp, link.countOfCoin, link.countFood);
	PrintFrameSide();
	printf("\n");
	PrintFrameBottom(95);
	message = { "" };
}
void MovePlayer(char movement)
{
	int row = link.pos.y;
	int col = link.pos.x;
	int value = 0;
	pointOnMap.map[link.pos.y][link.pos.x] = '.';	

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
			if (link.stats.hp + 10 <= link.stats.maxHp) {
				link.stats.hp += 10;
			}
			else {
				link.stats.hp += link.stats.maxHp - link.stats.hp;
			}
		}
	}
	Beep(150, 100);
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
		message = { "You Picked Up The Food" };
		Beep(300, 100);
	}

	if (pointOnMap.map[link.pos.y][link.pos.x] == 'C') {
		value = rand() % 3;
		switch (value) {
		case 0: 
			link.countOfCoin += 1;
			message = { "You Picked Up 1 Coin" };
			break;
		case 1:
			link.countOfCoin += 5;
			message = { "You Picked Up 5 Coin" };
			break;
		case 3:
			message = { "You Picked Up 10 Coin" };
			link.countOfCoin += 10;
		}
		Beep(400, 100);
	}

	for (int i = 0; i < pointOnMap.countNumberOfEnemy; i++) {
		if (link.pos.x == enemy[i].pos.x && link.pos.y == enemy[i].pos.y) {
			AttackPlayer(i);
			link.pos.x = col;
			link.pos.y = row;
			Beep(100, 100);
		}
	}
	pointOnMap.map[link.pos.y][link.pos.x] = '@';	
}
void MoveEnemy()
{
	int enemyRadius = 6;	
	int dx;					
	int dy;					
	int row;
	int col;
	/* Enemy Movement */
	for (int i = 0; i < pointOnMap.countNumberOfEnemy; i++) {
		dx = enemy[i].pos.x - link.pos.x;
		dy = enemy[i].pos.y - link.pos.y;
		row = enemy[i].pos.y;
		col = enemy[i].pos.x;

		pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x] = '.';
		/* Determining whether a player is in sight */
		if (sqrt(dx * dx + dy * dy) <= enemyRadius) {
			if (enemy[i].pos.y < link.pos.y && pointOnMap.map[enemy[i].pos.y + 1][enemy[i].pos.x] == '.' || pointOnMap.map[enemy[i].pos.y + 1][enemy[i].pos.x] == '@' ) {
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
		/* Determine if there are no doors ahead of the enemy*/
		if (pointOnMap.map[enemy[i].pos.y - 1][enemy[i].pos.x] == '=') {
			enemy[i].pos.y++;
		}
		else if (pointOnMap.map[enemy[i].pos.y + 1][enemy[i].pos.x] == '=') {
			enemy[i].pos.y--;
		}
		else if (pointOnMap.map[enemy[i].pos.y ][enemy[i].pos.x - 1] == '=') {
			enemy[i].pos.x++;
		}
		else if (pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x + 1] == '=') {
			enemy[i].pos.x--;
		}
		/* Determining whether there is a player ahead of the enemy */
		if (enemy[i].pos.x == link.pos.x && enemy[i].pos.y == link.pos.y) {
			AttackEnemy(i);
			enemy[i].pos.x = col;
			enemy[i].pos.y = row;
		}

		DeathEnemy(i);
		if (pointOnMap.countNumberOfEnemy > 0) {
			pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x] = enemy[i].type;
		}
	}
}
void AttackPlayer(int id)
{
	int chance = rand() % 100; // Chance of a successful attack
	if (chance < 50) {
		enemy[id].stats.hp -= link.stats.dmg;
		if (enemy[id].type == 'R') {
			message = { "You Hit The Rat" };
		}
		else if (enemy[id].type == 'S') {
			message = { "You Hit The Skeleton" };
		}
		else if (enemy[id].type == 'K') {
			message = { "You Hit The Knight" };
		}
		else if (enemy[id].type == 'O') {
			message = { "You Hit The Ork" };
		}
		else {
			message = { "You Hit The Dragon" };
		}
	}
	else {
		message = { "You Missed" };
	}
}
void AttackEnemy(int id)
{
	int chance = rand() % 100; // Chance of a successful attack
	if (chance > 49) {
		link.stats.hp -= enemy[id].stats.dmg;
		strcat(message.mess, ", And You Get Damage");
		rank.countResivetHits++;
	}
}
int DeathPlayer()
{
	if (link.stats.hp <= 0) {
		return 1;
	}
	return 0;
}
void DeathEnemy(int id)
{
	int chance;
	if (enemy[id].stats.hp <= 0) {
		if (enemy[id].type == 'R') {
			message = { "You Kill The Rat" };
		}
		else if (enemy[id].type == 'S') {
			message = { "You Kill The Skeleton" };
		}
		else if (enemy[id].type == 'K') {
			message = { "You Kill The Knight" };
		}
		else if (enemy[id].type == 'O') {
			message = { "You Kill The Ork" };
		}
		else {
			message = { "You Kill The Dragon" };
		}
		if (id == 0) {
			OpenDoors(1);
			message = { ", The Door Opened" };
		}
		if (enemy[id].type == 'D') {
			OpenDoors(2);
			message = { ", The Door Opened" };
		}
		link.stats.xp += enemy[id].stats.xp;
		chance = rand() % 2;
		if (chance == 1) {
			pointOnMap.map[enemy[id].pos.y][enemy[id].pos.x] = 'C';
			strcat(message.mess, ", And He Drop Coin");
		}
		for (int i = id; i < pointOnMap.countNumberOfEnemy - 1; i++) {
			enemy[i] = enemy[i + 1];
		}
		pointOnMap.countNumberOfEnemy--;
		enemy = (Enemy*)realloc(enemy, pointOnMap.countNumberOfEnemy * sizeof(Enemy));
	}
}
void OpenDoors(int flag)
{
	if (flag == 1) {
		pointOnMap.map[5][34] = '=';
	}
	if (flag == 2) {
		pointOnMap.map[22][29] = '=';
	}
}
void SystemOfLevelUps()
{
	if (link.stats.xp >= 40 && link.stats.lvl <= 6) {
		link.stats.xp -= 40;
		link.stats.lvl++;
		if (link.stats.hp + link.stats.maxHp <= link.stats.maxHp + 7) {
			link.stats.hp += link.stats.maxHp;
		}
		else {
			link.stats.hp += link.stats.maxHp - link.stats.hp;
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
void GameOver(int param)
{
	rank.countOfCoins = link.countOfCoin;
	rank.countOfKilledEnemys = 17 - pointOnMap.countNumberOfEnemy;
	rank.lvl = link.stats.lvl;

	system("cls");
	if (param == 0) {
		_setmode(_fileno(stdout), _O_U16TEXT);
		wprintf(L"\033[0;35m\n\n                   ▄████████  ▄██████▄  ███▄▄▄▄      ▄██████▄     ▄████████    ▄████████     ███     ███    █▄   ▄█          ▄████████     ███      ▄█   ▄██████▄  ███▄▄▄▄                               \n");
		wprintf(L"                  ███    ███ ███    ███ ███▀▀▀██▄   ███    ███   ███    ███   ███    ███ ▀█████████▄ ███    ███ ███         ███    ███ ▀█████████▄ ███  ███    ███ ███▀▀▀██▄                             \n");
		wprintf(L"                  ███    █▀  ███    ███ ███   ███   ███    █▀    ███    ███   ███    ███    ▀███▀▀██ ███    ███ ███         ███    ███    ▀███▀▀██ ███▌ ███    ███ ███   ███                             \n");
		wprintf(L"                  ███        ███    ███ ███   ███  ▄███         ▄███▄▄▄▄██▀   ███    ███     ███   ▀ ███    ███ ███         ███    ███     ███   ▀ ███▌ ███    ███ ███   ███                             \n");
		wprintf(L"                  ███        ███    ███ ███   ███ ▀▀███ ████▄  ▀▀███▀▀▀▀▀   ▀███████████     ███     ███    ███ ███       ▀███████████     ███     ███▌ ███    ███ ███   ███                             \n");
		wprintf(L"                  ███    █▄  ███    ███ ███   ███   ███    ███ ▀███████████   ███    ███     ███     ███    ███ ███         ███    ███     ███     ███  ███    ███ ███   ███                             \n");
		wprintf(L"                  ███    ███ ███    ███ ███   ███   ███    ███   ███    ███   ███    ███     ███     ███    ███ ███▌    ▄   ███    ███     ███     ███  ███    ███ ███   ███                             \n");
		wprintf(L"                  ████████▀   ▀██████▀   ▀█   █▀    ████████▀    ███    ███   ███    █▀     ▄████▀   ████████▀  █████▄▄██   ███    █▀     ▄████▀   █▀    ▀██████▀   ▀█   █▀                              \n");
		wprintf(L"                                                                 ███    ███                                     ▀                                                                                        \n\n");
		wprintf(L"\033[0;31m     ▄██   ▄    ▄██████▄  ███    █▄         ▄█   ▄█▄  ▄█   ▄█        ▄█               ███        ▄█    █▄       ▄████████     ████████▄     ▄████████    ▄████████    ▄██████▄   ▄██████▄  ███▄▄▄▄       \n");
		wprintf(L"     ███   ██▄ ███    ███ ███    ███       ███ ▄███▀ ███  ███       ███           ▀█████████▄   ███    ███     ███    ███     ███   ▀███   ███    ███   ███    ███   ███    ███ ███    ███ ███▀▀▀██▄     \n");
		wprintf(L"     ███▄▄▄███ ███    ███ ███    ███       ███▐██▀   ███▌ ███       ███              ▀███▀▀██   ███    ███     ███    █▀      ███    ███   ███    ███   ███    ███   ███    █▀  ███    ███ ███   ███     \n");
		wprintf(L"     ▀▀▀▀▀▀███ ███    ███ ███    ███      ▄█████▀    ███▌ ███       ███               ███   ▀  ▄███▄▄▄▄███▄▄  ▄███▄▄▄         ███    ███  ▄███▄▄▄▄██▀   ███    ███  ▄███        ███    ███ ███   ███     \n");
		wprintf(L"     ▄██   ███ ███    ███ ███    ███     ▀▀█████▄    ███▌ ███       ███               ███     ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀         ███    ███ ▀▀███▀▀▀▀▀   ▀███████████ ▀▀███ ████▄  ███    ███ ███   ███     \n");
		wprintf(L"     ███   ███ ███    ███ ███    ███       ███▐██▄   ███  ███       ███               ███       ███    ███     ███    █▄      ███    ███ ▀███████████   ███    ███   ███    ███ ███    ███ ███   ███     \n");
		wprintf(L"     ███   ███ ███    ███ ███    ███       ███ ▀███▄ ███  ███▌    ▄ ███▌    ▄         ███       ███    ███     ███    ███     ███   ▄███   ███    ███   ███    ███   ███    ███ ███    ███ ███   ███     \n");
		wprintf(L"      ▀█████▀   ▀██████▀  ████████▀        ███   ▀█▀ █▀   █████▄▄██ █████▄▄██        ▄████▀     ███    █▀      ██████████     ████████▀    ███    ███   ███    █▀    ████████▀   ▀██████▀   ▀█   █▀      \n");
		wprintf(L"                                           ▀              ▀         ▀                                                                      ███    ███                                                    \n\n");
		wprintf(L"\033[0;33m             ▄████████ ███▄▄▄▄   ████████▄         ▄████████  ▄█  ███▄▄▄▄   ████████▄          ███        ▄████████    ▄████████    ▄████████    ▄████████ ███    █▄     ▄████████    ▄████████ \n");
		wprintf(L"            ███    ███ ███▀▀▀██▄ ███   ▀███       ███    ███ ███  ███▀▀▀██▄ ███   ▀███     ▀█████████▄   ███    ███   ███    ███   ███    ███   ███    ███ ███    ███   ███    ███   ███    ███ \n");
		wprintf(L"            ███    ███ ███   ███ ███    ███       ███    █▀  ███▌ ███   ███ ███    ███        ▀███▀▀██   ███    ███   ███    █▀    ███    ███   ███    █▀  ███    ███   ███    ███   ███    █▀  \n");
		wprintf(L"            ███    ███ ███   ███ ███    ███      ▄███▄▄▄     ███▌ ███   ███ ███    ███         ███   ▀  ▄███▄▄▄▄██▀  ▄███▄▄▄       ███    ███   ███        ███    ███  ▄███▄▄▄▄██▀  ▄███▄▄▄     \n");
		wprintf(L"          ▀███████████ ███   ███ ███    ███     ▀▀███▀▀▀     ███▌ ███   ███ ███    ███         ███     ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ▀███████████ ▀███████████ ███    ███ ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     \n");
		wprintf(L"            ███    ███ ███   ███ ███    ███       ███        ███  ███   ███ ███    ███         ███     ▀███████████   ███    █▄    ███    ███          ███ ███    ███ ▀███████████   ███    █▄  \n");
		wprintf(L"            ███    ███ ███   ███ ███   ▄███       ███        ███  ███   ███ ███   ▄███         ███       ███    ███   ███    ███   ███    ███    ▄█    ███ ███    ███   ███    ███   ███    ███ \n");
		wprintf(L"            ███    █▀   ▀█   █▀  ████████▀        ███        █▀    ▀█   █▀  ████████▀         ▄████▀     ███    ███   ██████████   ███    █▀   ▄████████▀  ████████▀    ███    ███   ██████████ \n");
		wprintf(L"                                                                                                         ███    ███                                                     ███    ███              \n");
		_setmode(_fileno(stdout), _O_TEXT);
		strcpy(rank.gameOver, "Win");
		rank.score = rank.countOfCoins * 5 + rank.countOfKilledEnemys * 10 + rank.lvl * 3 + link.countFood * 6 + 1000;
	}
	else {
		_setmode(_fileno(stdout), _O_U16TEXT);
		wprintf(L"\033[0;31m\n\n\t\t▓██   ██▓ ▒█████   █    ██    ▓█████▄  ██▓▓█████ ▓█████▄ \n");
		wprintf(L"\t\t ▒██  ██▒▒██▒  ██▒ ██  ▓██▒   ▒██▀ ██▌▓██▒▓█   ▀ ▒██▀ ██▌\n");
		wprintf(L"\t\t  ▒██ ██░▒██░  ██▒▓██  ▒██░   ░██   █▌▒██▒▒███   ░██   █▌\n");
		wprintf(L"\t\t  ░ ▐██▓░▒██   ██░▓▓█  ░██░   ░▓█▄   ▌░██░▒▓█  ▄ ░▓█▄   ▌\n");
		wprintf(L"\t\t  ░ ██▒▓░░ ████▓▒░▒▒█████▓    ░▒████▓ ░██░░▒████▒░▒████▓ \n");
		wprintf(L"\t\t   ██▒▒▒ ░ ▒░▒░▒░ ░▒▓▒ ▒ ▒     ▒▒▓  ▒ ░▓  ░░ ▒░ ░ ▒▒▓  ▒ \n");
		wprintf(L"\t\t ▓██ ░▒░   ░ ▒ ▒░ ░░▒░ ░ ░     ░ ▒  ▒  ▒ ░ ░ ░  ░ ░ ▒  ▒ \n");
		wprintf(L"\t\t ▒ ▒ ░░  ░ ░ ░ ▒   ░░░ ░ ░     ░ ░  ░  ▒ ░   ░    ░ ░  ░ \n");
		wprintf(L"\t\t ░ ░         ░ ░     ░           ░     ░     ░  ░   ░    \n");
		wprintf(L"\t\t ░ ░                           ░                  ░      \n");
		_setmode(_fileno(stdout), _O_TEXT);
		strcpy(rank.gameOver, "Dead");
		rank.score = rank.countOfCoins * 5 + rank.countOfKilledEnemys * 10 + rank.lvl * 3 + link.countFood * 6;
	}
	SortRank();
	WriteRank();
	free(enemy);
	system("pause");
}