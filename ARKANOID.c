#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#define _USE_MATH_DEFINES // CONNECTING MATH LIBRARY
#include <math.h>
#include <conio.h> 

#define width 85 // THNAKS TO THESE CONSTANTS WE CAN CHANGE PARAMETRS IN FEW STEPS
#define heigth 35

typedef struct // STRUCTURE OF PANNEL
{
	int x, y, w;

}TRocket;

typedef struct // STRUCTURE OF BALL
{
	float x, y;
	int ix, iy;
	float alfa;
	float speed;
}TBall;

char mas[heigth][width + 1]; // ARRAY WHICH BASICALLY REPRESENTS FIELD
TRocket rocket; // VARIABLE OF STRUCTURE 
TBall ball, coin;
int hitCnt = 0;// GLOBAL VARIBLES STARTING FROM THIS ONE
int maxHitCnt = 0;
int HitCoin = 0;
int MaxHitCoin = 0;
int lvl = 0;


void initRocket()// INITIALIZATION OF FIELD
{
	rocket.w = 7;
	rocket.x = (width - rocket.w) / 2;
	rocket.y = heigth - 1;
}

void MoveBall(float x, float y) // Move ball
{
	ball.x = x;
	ball.y = y;
	ball.ix = (int)round(ball.x);
	ball.iy = (int)round(ball.y);
}

void initBall() // INITIALIZATION OF BALL
{
	MoveBall(2, 2);
	ball.alfa = -1;
	ball.speed = 0.5;
	coin.ix = 42;
	coin.iy = 30;
}

void putBall() // Putting BALL on field
{
	mas[ball.iy][ball.ix] = '*';
	mas[coin.iy][coin.ix] = '0';
}

void AutoMoveBall() // Physics
{
	if (ball.alfa < 0) ball.alfa += M_PI * 2;
	if (ball.alfa > M_PI * 2) ball.alfa -= M_PI * 2;

	TBall bl = ball; 
	MoveBall(ball.x + cos(ball.alfa) * ball.speed
		, ball.y + sin(ball.alfa) * ball.speed); // function to calculate ball`s current location
	if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '@'))
	{
		if (mas[ball.iy][ball.ix] == '@')
		{
			hitCnt++;
			if (hitCnt == 10)
			{
				if (lvl < 3)
					lvl++;
				if (maxHitCnt < hitCnt)
					maxHitCnt = hitCnt;
				hitCnt = 0;
			}
		}
		if ((ball.ix != bl.ix) && (ball.iy != bl.iy))
		{
			if (mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix])
				bl.alfa = bl.alfa + M_PI;
			else
			{
				if (mas[bl.iy][ball.ix] == '#')
					bl.alfa = (2 * M_PI - bl.alfa) + M_PI;
				else
					bl.alfa = (2 * M_PI - bl.alfa);
			}
		}
		else if (ball.iy == bl.iy)
			bl.alfa = (2 * M_PI - bl.alfa) + M_PI;
		else
			bl.alfa = (2 * M_PI - bl.alfa);
		ball = bl;
		AutoMoveBall();// looping
	}
}

void PutRocket() // Putting rocket
{
	for (int i = rocket.x; i < rocket.x + rocket.w; i++)
		mas[rocket.y][i] = '@';
}

void init() // INITIALIZATION 
{
	for (int i = 0; i < width; i++)
		mas[0][i] = '#';
	mas[0][width] = '\0';

	strncpy(mas[1], mas[0], width + 1);
	for (int i = 1; i < width - 1; i++)
		mas[1][i] = ' ';

	for (int i = 2; i < heigth; i++)
		strncpy(mas[i], mas[1], width + 1);
	switch (lvl) //  DEPENDS ON LEVEL
	{
	case 1:
		break;
	case 2:
		for (int i = 30; i < 50; i++)
			mas[19][i] = '#';
		for (int i = 5; i < 10; i++)
		{
			mas[i][10] = '#';
			mas[i][70] = '#';
		}
		break;
	case 3:
		for (int i = 30; i < 50; i++)
		{
			mas[19][i] = '#';
			mas[10][i] = '#';
		}
		for (int i = 5; i < 20; i++)
		{
			mas[i][10] = '#';
			mas[i][76] = '#';
			mas[i][73] = '#';
		}
		for (int i = 2; i < 29; i++)
			mas[i][20] = '#';
		for (int i = 43; i < 70; i++)
		{
			mas[16][i] = '0';
			mas[22][i] = '#';
		}
		break;
	}
}

void show() // Вывод поля и всякой статистики справа от поля
{
	for (int i = 0; i < heigth; i++)
	{
		printf("%s", mas[i]);
		if (i == 2)
			printf("    Level %i   ", lvl);
		if (i == 3)
			printf("    hit %i   ", hitCnt);
		if (i == 4)
			printf("    max %i   ", maxHitCnt);
		if (i == 5)
			printf("    Coins Gained %i   ", HitCoin);
		if (i == 6)
			printf("    Max Coins Gained %i   ", MaxHitCoin);
		if (i < heigth - 1)
			printf("\n");
	}
}
void moveRocket(int x) //Function of moving filed
{
	rocket.x = x;
	if (rocket.x < 1)
		rocket.x = 1;
	if (rocket.x + rocket.w >= width)
		rocket.x = width - 1 - rocket.w;
}
void sercur(int x, int y) // Place CURSOR
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	HANDLE  handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}
int main()
{
	rand(time(NULL));
	BOOL run = FALSE;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	initRocket();
	initBall();
	printf("Выберете уровень :\n 1 - Simple \n 2 - Sad Smile \n 3 - Labirinth \n");
	scanf("%d", &lvl);

	do
	{
		sercur(0, 0); 
		init();
		PutRocket();
		putBall();
		show();
		if (run)
			AutoMoveBall();
		if (ball.iy > heigth)
		{
			run = FALSE;
			if (hitCnt > maxHitCnt)
				maxHitCnt = hitCnt;
			if (HitCoin > MaxHitCoin)
				MaxHitCoin = HitCoin;
			hitCnt = 0;
			HitCoin = 0;
		}

		if (GetKeyState('A') < 0) moveRocket(rocket.x - 1); //Function GetKeyState from library "Windows.h"
		if (GetKeyState('D') < 0) moveRocket(rocket.x + 1);
		if (GetKeyState('W') < 0) run = TRUE;
		if (mas[ball.iy][ball.ix] == '0')
		{
			coin.ix = rand() * 1.0 / RAND_MAX * 85;
			coin.iy = rand() * 1.0 / RAND_MAX * 35;
			HitCoin++;
		}
		if (!run)
			MoveBall(rocket.x + rocket.w / 2, rocket.y - 1);
		Sleep(10); 
	} while (GetKeyState(VK_ESCAPE) >= 0); // PRESS ESC TO STOP GAME
	return 0;
}
