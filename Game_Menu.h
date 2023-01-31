#pragma once
#include "Structs.h"

void GameMenu()
{
	SetConsoleCP(CP_UTF8);	SetConsoleOutputCP(CP_UTF8);
	int choice = 0;
	char move;

	TittleArt();

	while (1) {
		ClearScreen();
		OutputInfo();

		printf("\t\t\t");
		PrintFrameTop(71);

		ChoiceMenu(0, choice);	printf("Play\t\t\t\t\t\t");				PrintFrameSide();	printf("\n\t\t\t");
		ChoiceMenu(1, choice);	printf("Ranking Table\t\t\t\t");		PrintFrameSide();	printf("\n\t\t\t");
		ChoiceMenu(2, choice);	printf("Exit\t\t\t\t\t\t");				PrintFrameSide();	printf("\n\t\t\t");
		
		PrintFrameBottom(71);
		
		move = (char)tolower(_getch());
		if (move == 'w') {
			choice--;
		}
		else if (move == 's') {
			choice++;
		}
		if (choice < 0) {
			choice++;
		}
		if (choice > 2) {
			choice--;
		}
		if (move == '\r') {
			switch (choice) {
			case 0:
				ReadRank();
				printf("\n\n\n\t\t\tEnter Your Name: ");	scanf("%s", rank.playerName);
				system("cls");
				GamePlayProcessing();
				
				system("cls");
				break;
			case 1:
				system("cls");
				ReadRank();
				OutputRankingTable();
				system("cls");
				break;
			case 2:
				exit(0);
			}
		}
	}
}

void ChoiceMenu(int x, int y)
{
	if (x == y) {
		printf("\t\t\t");
		PrintFrameSide();	Cursor();
	}
	else {
		printf("\t\t\t");
		PrintFrameSide();	printf("\033[0;37m\t\t\t   ");
	}
}

void OutputInfo()
{
	printf("\033[0;37m");
	char c;
	FILE* fp = fopen("GameMenu.txt", "r");

	/* The process of calculating map dimensions */
	printf("\t\t\t\t\t\t");
	while ((c = fgetc(fp)) != EOF) {
		printf("%c", c);
		if (c == '\n') {
			printf("\t\t\t\t\t\t");
		}
	}

	fclose(fp);
	printf("\n");
}

void TittleArt()
{
	FILE* fp = fopen("ASCII_Art.txt", "r");
	char ch;
	printf("\t\t\t\t\t\t");
	while ((ch = fgetc(fp)) != EOF) {
		printf("%c", ch);
		if (ch == '\n') {
			printf("\t\t\t\t\t\t");
		}
	}

	fclose(fp);
	system("pause");
	system("cls");
}

void OutputRankingTable()
{
	FILE* fp = fopen("RankingTable.txt", "r");
	char ch;

	if (fgetc(fp) == EOF) {
		printf("The Rank Table Is Empty\nSo Start Playing\n");
		system("pause");
	}

	/* the process of calculating map dimensions */
	else {
		for (int i = 0; i < sizeRank; i++)
		{
			printf("=============================================");
			printf("\nGame Over: %s", arrRank[i].gameOver);
			printf("\nPlayer Name: %s ", arrRank[i].playerName);
			printf("\nPlayer level: %d", arrRank[i].lvl);
			printf("\nThe Number Of Killed Enemys: %d", arrRank[i].countOfKilledEnemys);
			printf("\nThe Number Of Hits Received : %d", arrRank[i].countResivetHits);
			printf("\nThe Number Of Coins: %d\n", arrRank[i].countOfCoins);
		}
		system("pause");
	}
	fclose(fp);
}

void PrintFrameTop(int lenght) 
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"\033[0;37m\t\t\t╔");
	for (int i = 0; i < lenght; i++) {
		wprintf(L"═");
	}
	wprintf(L"╗\n\t\t\t");
	_setmode(_fileno(stdout), _O_TEXT);
}
void PrintFrameSide()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"\033[0;37m║");
	_setmode(_fileno(stdout), _O_TEXT);
}
void PrintFrameBottom(int lenght)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"\033[0;37m\t\t\t╚");
	for (int i = 0; i < lenght; i++) {
		wprintf(L"═");
	}
	wprintf(L"╝\n");
	_setmode(_fileno(stdout), _O_TEXT);
}
void Cursor()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"\033[0;32m\t\t\t ☻ ");
	_setmode(_fileno(stdout), _O_TEXT);
}

void ReadRank()
{
	FILE* fp = fopen("RankingTable.txt", "r");
	
	if (fp == NULL) {
		printf("Sorry, Creating File With Ranking");
		CreateRank();
	}
	else {
		fseek(fp, 0, SEEK_END);
		sizeRank = ftell(fp) / sizeof(Ranking);
		rewind(fp);
		arrRank = (Ranking*)malloc(sizeof(Ranking) * sizeRank);
		fread(arrRank, sizeof(Ranking), sizeRank, fp);
	}
	fclose(fp);
}

void WriteRank()
{
	FILE* fp = fopen("RankingTable.txt", "a");
	fwrite(&rank, sizeof(Ranking), 1, fp);
	fclose(fp);
}

void CreateRank()
{
	FILE* fp = fopen("RankingTable.txt", "w");
	fclose(fp);
}