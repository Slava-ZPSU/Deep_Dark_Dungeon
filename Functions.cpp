#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include "Structs.h"

int main()
{
	Map map;
	Map* pointOnMap = &map;
	SetDefaultMapSizes(pointOnMap);
	CreateMap(pointOnMap);
	FillingMap(pointOnMap);
	PrintMap(pointOnMap);
	return 0;
}

void SetDefaultMapSizes(Map* map)
{
	char ch;
	FILE* fp = fopen("DungeonMap.txt", "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	while ((ch = getc(fp)) != EOF) {
		map->Col++;
		if (ch == '\n') {
			map->Row++;
			map->Col = 1;
		}
	}
	fclose(fp);
}

void CreateMap(Map* map)
{
	map->Map = (char**)malloc(sizeof(char*) * map->Row);
	for (int i = 0; i < map->Row; i++) {
		map->Map[i] = (char*)malloc(sizeof(char) * map->Col);
	}
}

void FillingMap(Map* map)
{
	FILE* fp = fopen("DungeonMap.txt", "r");

	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	for (int i = 0; i < map->Row; i++)
	{
		for (int j = 0; j < map->Col; j++) {
			map->Map[i][j] = getc(fp);
			if (map->Map[i][j] == '\n') {
				map->Map[i][j] = ' ';
			}
		}
	}
	fclose(fp);
}

void PrintMap(Map* map)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < map->Row; i++) {
		for (int j = 0; j < map->Col; j++) {
				if (map->Map[i][j] == '@') {
					printf("\033[0;36m");
				}
				else if (map->Map[i][j] == '~') {
					SetConsoleTextAttribute(hConsole, 12);
				}
				else if (map->Map[i][j] == 'R' || map->Map[i][j] == 'S' || map->Map[i][j] == 'K' || map->Map[i][j] == 'O') {
					SetConsoleTextAttribute(hConsole, 13);
				}
				else if (map->Map[i][j] == 'D') {
					SetConsoleTextAttribute(hConsole, 2);
				}
				else if (map->Map[i][j] == 'E') {
					printf("\033[0;32m");
				}
				else if (map->Map[i][j] == '.') {
					SetConsoleTextAttribute(hConsole, 8);
				}
				else if (map->Map[i][j] == '=' || map->Map[i][j] == '+') {
					printf("\033[0;33m");
				}
				else {
					printf("\033[0m");
				}
			printf("%2c", map->Map[i][j]);
		}
		printf("\n");
	}

}