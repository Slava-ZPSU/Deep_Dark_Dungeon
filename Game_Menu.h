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
				FillMap();
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

	if (fgetc(fp) == EOF) {
		printf("___________.__             __________               __     ___________     ___.   .__           .___         ___________               __             \n");
		printf("\\__    ___/|  |__   ____   \\______   \\____    ____ |  | __ \\__    ___/____ \\_ |__ |  |   ____   |   | ______ \\_   _____/ _____ _______/  |_ ___.__.    \n");
		printf("  |    |   |  |  \\_/ __ \\   |       _|__  \\  /    \\|  |/ /   |    |  \\__  \\ | __ \\|  | _/ __ \\  |   |/  ___/  |    __)_ /     \\\\____ \\   __<   |  |  \n");
		printf("  |    |   |   Y  \\  ___/   |    |   \\/ __ \\|   |  \\    <    |    |   / __ \\| \\_\\ \\  |_\\  ___/  |   |\\___ \\   |        \\  Y Y  \\  |_> >  |  \\___  | \n");
		printf("  |____|   |___|  /\\___  >  |____|_  (____  /___|  /__|_ \\   |____|  (____  /___  /____/\\___  > |___/____  > /_______  /__|_|  /   __/|__|  / ____|\n");
		printf("                \\/     \\/          \\/     \\/     \\/     \\/                \\/    \\/          \\/           \\/          \\/      \\/|__| \n");
		printf("  _________          _________ __                 __    __________.__                .__                  \n");
		printf(" /   _____/ ____    /   _____//  |______ ________/  |_  \\______   \\  | _____  ___.__.|__| ____    ____    \n");
		printf(" \\_____  \\ /  _ \\   \\_____  \\\\   __\\__  \\\\_  __ \\   __\\  |     ___/  | \\__  \\<   |  ||  |/    \\  / ___\\   \n");
		printf(" /        (  <_> )  /        \\|  |  / __ \\|  | \\/|  |    |    |   |  |__/ __ \\___  ||  |   |  \\/ /_/  >  \n");
		printf("/_______  /\\____/  /_______  /|__| (____  /__|   |__|    |____|   |____(____  / ____||__|___|  /\\___  /   \n");
		printf("        \\/                 \\/           \\/                                  \\/\\/             \\//_____/    \n");
		system("pause");
	}

	/* the process of calculating map dimensions */
	else {
		SortRank();
		printf("\t\t\t\t");		PrintFrameTop(50);		printf("\t\t\t\t");	
		PrintFrameSide();	printf("\t\t   RANKING TABLE\t\t   ");	PrintFrameSide();
		printf("\n\t\t\t\t");		PrintFrameBottom(50);
		for (int i = 0; i < sizeRank; i++)
		{
			printf("\t\t\t\t");		PrintFrameTop(50);		printf("\t\t\t\t");
			PrintFrameSide();	printf("Game Over:                   %21s", arrRank[i].gameOver);				PrintFrameSide();	printf("\n\t\t\t\t\t\t\t");
			PrintFrameSide();	printf("Player Name:                 %21s", arrRank[i].playerName);				PrintFrameSide();	printf("\n\t\t\t\t\t\t\t");
			PrintFrameSide();	printf("Player level:                %21d", arrRank[i].lvl);					PrintFrameSide();	printf("\n\t\t\t\t\t\t\t");
			PrintFrameSide();	printf("The Number Of Killed Enemys: %21d", arrRank[i].countOfKilledEnemys);	PrintFrameSide();	printf("\n\t\t\t\t\t\t\t");
			PrintFrameSide();	printf("The Number Of Hits Received: %21d", arrRank[i].countResivetHits);		PrintFrameSide();	printf("\n\t\t\t\t\t\t\t");
			PrintFrameSide();	printf("The Number Of Coins:         %21d", arrRank[i].countOfCoins);			PrintFrameSide();	printf("\n\t\t\t\t\t\t\t");
			PrintFrameSide();	printf("The passage time:            %21.2f", arrRank[i].time);					PrintFrameSide();	printf("\n\t\t\t\t\t\t\t");
			PrintFrameSide();	printf("The Total Number Of Points:  %21d", arrRank[i].score);					PrintFrameSide();	printf("\n\t\t\t\t");
			
			PrintFrameBottom(50);
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

void SortRank()
{
	Ranking tmp;
	for (int i = 0; i < sizeRank; i++) {
		tmp = arrRank[i];
		for (int j = i - 1; j >= 0 && arrRank[j].score < tmp.score; j--) {
			arrRank[j + 1] = arrRank[j];
			arrRank[j] = tmp;
		}
	}
}