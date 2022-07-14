#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h>
#include <time.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char mas[20][41];
	int x = 10, y = 5, ax1 = 5, ay1 = 3, ax2 = 8, ay2 = 11, score = 0;
	char key;
	int ox, oy;
	srand(time(NULL));
	do
	{
		sprintf(mas[0], "#######################################");
		for (int i = 1; i < 19; i++)
			sprintf(mas[i], "#                                     #");
		sprintf(mas[19], "#######################################");
		mas[y][x] = '@';
		mas[ay1][ax1] = '*';
		mas[ay2][ax2] = '*';
		system("cls");
		printf("Score : %d\n", score);
		for (int i = 0; i < 20; i++)
			printf("%s\n", mas[i]);

		key = _getch();
		ox = x;
		oy = y;

		if (key == 'w') y--;
		if (key == 's') y++;
		if (key == 'a') x--;
		if (key == 'd') x++;
		if (mas[y][x] == '#')
		{
			x = ox;
			y = oy;
		}
		if (x == ax1 && y == ay1)
		{
			ax1 = rand() * 1.0 / RAND_MAX * 38 + 1;
			ay1 = rand() * 1.0 / RAND_MAX * 18 + 1;
			score++;
		}
		if (x == ax2 && y == ay2)
		{
			ax2 = rand() * 1.0 / RAND_MAX * 38 + 1;
			ay2 = rand() * 1.0 / RAND_MAX * 18 + 1;
			score++;
		}
	} while (key != 'i');
	return 0;
}
