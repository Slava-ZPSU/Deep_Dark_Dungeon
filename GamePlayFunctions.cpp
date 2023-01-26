#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <conio.h>
#include "Structs.h"

int main()
{
	SetDefaultMapSizes(); // ��������� ����

	GamePlayProcessing(); // ������� ������

	free(pointOnMap.map); // ��������� ���������� ���'��
	return 0;
}

void SetDefaultMapSizes()
{
	char ch;	// �����, �� ������� ��� ������� ��������� �-�� ����� �� ��������
	FILE* fp = fopen("DungeonMap.txt", "r");	// ³������� ����� � �����
	
	/* �������� �� ��������� */
	if (fp == NULL) {							
		printf("Error opening file\n");			
		exit(1);								
	}

	/* ������ ��������� ������ ���� */
	while ((ch = fgetc(fp)) != EOF) {
		pointOnMap.mapColSize++;
		if (ch == '\n') {
			pointOnMap.mapRowSize++;
			pointOnMap.mapColSize = 1;
		}
	}
	
	fclose(fp);		// �������� �����
	CreateMap();	// ������� �� ��������� ������ ����
}
void CreateMap()
{
	/* �������� ���������� ���'�� �� ���� */
	pointOnMap.map = (char**)malloc(sizeof(char*) * pointOnMap.mapRowSize);
	for (int i = 0; i < pointOnMap.mapRowSize; i++) {
		pointOnMap.map[i] = (char*)malloc(sizeof(char) * pointOnMap.mapColSize);
	}
	FillMap(); // ������� �� ���������� ����
}
void FillMap()
{
	FILE* fp = fopen("DungeonMap.txt", "r");	// ³������� ����� � �����

	/* �������� �� ��������� */
	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	/* ������ ���������� ���� */
	for (int i = 0; i < pointOnMap.mapRowSize; i++)
	{
		for (int j = 0; j < pointOnMap.mapColSize; j++) {
			pointOnMap.map[i][j] = getc(fp);
			if (pointOnMap.map[i][j] == '\n') {
				pointOnMap.map[i][j] = ' ';
			}
		}
	}
	fclose(fp);		// �������� �����
}

void GamePlayProcessing()
{
	char movement = ' ';	// ����� ��� ���������� �������� ���� ������

	SetObjectParameters();	// ��������� ��'����

	do
	{
		system("cls");		// ��������� ������ (�������� ������)
		PrintMap();			// ���� ����

		movement = (char)tolower(_getch());		// ���������� �������� ���� ������
		MovePlayer(movement);					// ��� ��������� ������
		MoveEnemy();
	} while (link.pos.y != 14 || link.pos.x != 25);		// ��� ���������� ��� ����� �������� ������
}
void MovePlayer(char movement)
{
	pointOnMap.map[link.pos.y][link.pos.x] = '.';		// �������� ����������� �� ���� �������, ���� ����� ����� ������

	/* ������ ���� ��������� */
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

	/* �������� �� �������� ������� �� � ������� */
	if (pointOnMap.map[link.pos.y][link.pos.x] == '=') {
		/* ������� ����� ���� */
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
	pointOnMap.map[link.pos.y][link.pos.x] = '@';	// �������� ����������� �� ���� �������
}

void PrintMap()
{
	/* ������� ���������� ������ ���� � ���� ��������� �� ������ ������� �������� ������ */
	newMapSize.rowMax = pointOnMap.mapRowSize;		
	newMapSize.colMax = pointOnMap.mapColSize;

	int row = 0;
	int col = 0;

	//SetPlayerVision();	// ���� ������ �������� ���������

	/* ���� ���� �� ����� */
	for (int i = newMapSize.rowMin; i < newMapSize.rowMax; i++) {
		for (int j = newMapSize.colMin; j < newMapSize.colMax; j++) {
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
	/* ���� ������ �������� ������ � ��������� �� ������� ��������� */
	newMapSize.rowMin = link.pos.y - 3;
	newMapSize.colMin = link.pos.x - 3;
	newMapSize.rowMax = link.pos.y + 4;
	newMapSize.colMax = link.pos.x + 4;
}
void DyeingSymbols(int i, int j)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	/* ���������� ������� */
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
	/* Player */
	link = { 1, 35, 13, 5, 10, 10, 1, 0, 2 };
	/* Enemys */
	enemy[0] = { 'R', 53, 22, 2, 15 };
	enemy[1] = { 'R', 62, 19, 2, 15 };
	enemy[2] = { 'R', 53, 22, 2, 15 };
	enemy[3] = { 'R', 62, 19, 2, 15 };
}
void MoveEnemy()
{
	for (int i = 0; i < 17; i++) {

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