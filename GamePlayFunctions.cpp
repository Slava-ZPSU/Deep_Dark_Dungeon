#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <conio.h>
#include <math.h>
#include "Structs.h"

int main()
{
	SetDefaultMapSizes(); // Creating map

	GamePlayProcessing(); // Gameplay

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
	char movement = NULL;	// 	A variable for reading the direction of movement of the player

	SetObjectParameters();	// Creation of objects

	do
	{
		system("cls");
		PrintMap();

		movement = (char)tolower(_getch());		// Reading the player's direction of movement
		MovePlayer(movement);					// Character movement
		MoveEnemy();
	} while (link.pos.y != 14 || link.pos.x != 25);		// To complete the game, you need to reach the treasures
}
void MovePlayer(char movement)
{
	pointOnMap.map[link.pos.y][link.pos.x] = '.';		// The character has moved to a new position, so the floor occupies the previous position

	/* The process of character movement */
	switch (movement) {
	case 'w':
		if (pointOnMap.map[link.pos.y - 1][link.pos.x] != '#' && pointOnMap.map[link.pos.y - 1][link.pos.x] != '~') {
			link.pos.y--;
		}
		break;
	case 's':
		if (pointOnMap.map[link.pos.y + 1][link.pos.x] != '#' && pointOnMap.map[link.pos.y + 1][link.pos.x] != '~') {
			link.pos.y++;
		}
		break;
	case 'a':
		if (pointOnMap.map[link.pos.y][link.pos.x - 1] != '#' && pointOnMap.map[link.pos.y][link.pos.x - 1] != '~') {
			link.pos.x--;
		}
		break;
	case 'd':
		if (pointOnMap.map[link.pos.y][link.pos.x + 1] != '#' && pointOnMap.map[link.pos.y][link.pos.x + 1] != '~') {
			link.pos.x++;
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
	pointOnMap.map[link.pos.y][link.pos.x] = '@';	// The character has moved to a new position
}

void PrintMap()
{
	/* I transfer the maximum map size to the structure fields, which reduces the player's visibility */
	newMapSize.maxRow = pointOnMap.mapRowSize;		
	newMapSize.maxCol = pointOnMap.mapColSize;

	int row = 0;
	int col = 0;

	//SetPlayerVision();	// Change the character's viewport

	/* Output map in console */
	for (int i = newMapSize.minRow; i < newMapSize.maxRow; i++) {
		for (int j = newMapSize.minCol; j < newMapSize.maxCol; j++) {
			if (pointOnMap.map[i][j] == '@') {
				row = i;
				col = j;
			}
			DyeingSymbols(i, j);
			printf("%2c", pointOnMap.map[i][j]);
		}
		printf("\n");
	}
	printf("row - %d col - %d", row, col);
}
void SetPlayerVision()
{
	/* Change the player's view depending on the character's position */
	newMapSize.minRow = link.pos.y - 3;
	newMapSize.minCol = link.pos.x - 3;
	newMapSize.maxRow = link.pos.y + 4;
	newMapSize.maxCol = link.pos.x + 4;
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
	else {
		printf("\033[0m");
	}
}
void SetObjectParameters()
{
	int id = 0;
	char type = NULL;
	/* Player */
	link = { 1, 35, 13, 5, 10, 10, 1, 0, 2 };
	/* Enemys */
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		for (int j = 0; j < pointOnMap.mapColSize; j++) {
			if (pointOnMap.map[i][j] == 'R' || pointOnMap.map[i][j] == 'S' || pointOnMap.map[i][j] == 'K' || pointOnMap.map[i][j] == 'O') {
				if (pointOnMap.map[i][j] == 'S') {
					type = 'S';
				}
				else if (pointOnMap.map[i][j] == 'K') {
					type = 'K';
				}
				else if (pointOnMap.map[i][j] == 'O') {
					type = 'O';
				}
				else {
					type = 'R';
				}
				enemy[id] = { type, j, i };
				id++;
			}
		}
	}
}
void MoveEnemy()
{
	for (int i = 0; i < 16; i++) {
		if (fabs(link.pos.x - enemy[i].pos.x < 5) && fabs(link.pos.y - enemy[i].pos.y < 5)) {
			
			pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x] = '.';

			if (enemy[i].pos.x < link.pos.x && pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x + 1] == '.') {
				enemy[i].pos.x++;
			}
			else if (enemy[i].pos.y < link.pos.y && pointOnMap.map[enemy[i].pos.y + 1][enemy[i].pos.x] == '.') {
				enemy[i].pos.y++;
			}
			else if (enemy[i].pos.x > link.pos.x && pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x - 1] == '.') {
				enemy[i].pos.x--;
			}
			else if (enemy[i].pos.y > link.pos.y && pointOnMap.map[enemy[i].pos.y - 1][enemy[i].pos.x] == '.') {
				enemy[i].pos.y--;
			}
			pointOnMap.map[enemy[i].pos.y][enemy[i].pos.x] = enemy[i].type;
		}
	}
}