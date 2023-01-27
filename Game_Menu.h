#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void TittleArt()
{
	FILE* fp = fopen("Art.txt", "r");
	char ch;

	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	/* The process of calculating map dimensions */
	while ((ch = fgetc(fp)) != EOF) {
		printf("%c", ch);
	}

	fclose(fp);
}