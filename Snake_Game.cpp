//Snake_Game
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define X 3
#define Y 2
#define WIDTH 30
#define HEIGHT 20

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

//원하는 음악의 파일 주소(WAVE 파일만 가능!)
#define Song "Megalovania.wav"


typedef struct Snake {
	int x;
	int y;
}snake;

snake S[100];
snake food;
int length;
int score;
int best_score;
int last_score;
int direction;
int key;
int speed;

void Gotoxy(int x, int y, const char* word) {
	COORD pos = { (short)x * 2,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", word);
	return;
}

void Normal_Mode();
void Setting();
void Title();
void Reset();
void Draw_map();
void Move();
void Game_over();
void Food();

void Sans_Mode();
void S_Setting();
void S_Title();
void S_Reset();
void S_Draw_map();
void S_Move();
void S_Game_over();
void S_Food();

//////////MAIN START//////////
int main() {
	int choose = 0;
	printf("고르시오\n(0:normal 1:hard) : ");
	scanf("%d", &choose);
	if (choose == 0) Normal_Mode();
	else Sans_Mode();
	return 0;
}
///////////MAIN END///////////

//////////Normal Start//////////
void Normal_Mode() {
	Setting();
	Title();

	while (1) {
		if (kbhit()) {
			do key = getch();
			while (key == 224);
		}
		Sleep(150);

		switch (key) {
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((direction == LEFT && key != RIGHT) ||
				(direction == RIGHT && key != LEFT) ||
				(direction == UP && key != DOWN) ||
				(direction == DOWN && key != UP)) direction = key;
			key = 0;
			break;
		case ESC:
			Gotoxy(X, Y + HEIGHT + 1, "");
			exit(0);
		}
		Move();
	}
	return;
}

void Setting() {
	system("cls");
	system("mode con: cols=72 lines=26");
	system("title Snake");
	return;
}

void Title() {
	system("cls");
	Draw_map();

	Gotoxy(X + (WIDTH / 2) - 4, Y + (HEIGHT / 2) - 3, "+----------------+");
	Gotoxy(X + (WIDTH / 2) - 4, Y + (HEIGHT / 2) - 2, "S N A K E  G A M E");
	Gotoxy(X + (WIDTH / 2) - 4, Y + (HEIGHT / 2) - 1, "+----------------+");

	Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 1, "<PRESS ANY KEY TO START>");
	Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 3, "◇ ←,→,↑,↓ : Move");
	Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 4, "◇ ESC : Exit");

	while (1) {
		if (kbhit()) {
			key = getch();
			if (key == ESC) {
				Gotoxy(X, Y + HEIGHT + 1, "");
				exit(0);
			}
			else break;
		}
		Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 1, "<PRESS ANY KEY TO START>");
		Sleep(200);
		Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 1, "                        ");
		Sleep(200);
	}
	Reset();
	return;
}

void Reset() {
	int i;
	system("cls");
	Draw_map();

	direction = LEFT;
	length = 3;
	score = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	for (i = 0; i < length; i++) {
		S[i].x = WIDTH / 2 + i;
		S[i].y = HEIGHT / 2;
		Gotoxy(X + S[i].x, Y + S[i].y, "□");
	}
	Gotoxy(X + S[0].x, Y + S[0].y, "■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	Food();
	return;
}

void Draw_map() {
	int i;
	for (i = X; i < X + WIDTH; i++) Gotoxy(i, Y, "■");
	for (i = Y; i <= Y + HEIGHT; i++) {
		Gotoxy(X, i, "■");
		Gotoxy(X + WIDTH, i, "■");
	}
	for (i = X; i < X + WIDTH; i++) Gotoxy(i, Y + HEIGHT, "■");
	return;
}

void Move() {
	int i;

	if (S[0].x == food.x && S[0].y == food.y) {
		score++;
		Food();
		if (length < 100) length++;
		S[length - 1].x = S[length - 2].x;
		S[length - 1].y = S[length - 2].y;
	}

	if (S[0].x == X - 3 || S[0].x == X + WIDTH - 3) {
		Game_over();
		return;
	}
	else if (S[0].y == Y - 2 || S[0].y == Y + HEIGHT - 2) {
		Game_over();
		return;
	}

	for (i = 1; i < length; i++) {
		if (S[0].x == S[i].x && S[0].y == S[i].y) {
			Game_over();
			return;
		}
	}

	Gotoxy(X + S[length - 1].x, Y + S[length - 1].y, "  ");
	for (i = length - 1; i > 0; i--) {
		S[i].x = S[i - 1].x;
		S[i].y = S[i - 1].y;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	Gotoxy(X + S[i].x, Y + S[i].y, "□");
	if (direction == LEFT) S[0].x--;
	else if (direction == RIGHT) S[0].x++;
	else if (direction == UP) S[0].y--;
	else if (direction == DOWN) S[0].y++;
	Gotoxy(X + S[i].x, Y + S[i].y, "■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	return;
}

void Game_over() {
	Gotoxy(X + (WIDTH / 2) - 4, Y + 5, "+------------+");
	Gotoxy(X + (WIDTH / 2) - 4, Y + 6, "| GAME OVER. |");
	Gotoxy(X + (WIDTH / 2) - 4, Y + 7, "+------------+");
	Gotoxy(X + (WIDTH / 2) - 4, Y + 8, "Your Score : ");
	printf("%d", last_score = score);

	Gotoxy(X + (WIDTH / 2) - 6, Y + 12, " Press any keys to Restart.. ");

	if (score > best_score) {
		best_score = score;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
		Gotoxy(X + (WIDTH / 2) - 4, Y + 10, "☆ BEST SCORE ☆");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	}
	Sleep(100);
	key = getch();
	Title();
	return;
}

void Food() {
	int i;
	int r = 0;
	int food_crush = 0;
	Gotoxy(X, Y + HEIGHT + 1, "YOUR SCORE : ");
	printf("%3d, LAST SCORE : %3d, BEST SCORE : %3d", score, last_score, best_score);

	while (1) {
		food_crush = 0;
		srand((unsigned)time(NULL) + r);
		food.x = (rand() % (WIDTH - 2)) + 1;
		food.y = (rand() % (HEIGHT - 2)) + 1;

		for (i = 0; i < length; i++) {
			if (food.x == S[i].x && food.y == S[i].y) {
				food_crush = 1;
				r++;
				break;
			}
		}

		if (food_crush == 1) continue;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
		Gotoxy(X + food.x, Y + food.y, "●");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		break;
	}
	return;
}
//////////Normal End//////////

//////////Sans Start//////////
void Sans_Mode() {
	S_Setting();
	S_Title();

	PlaySound(TEXT(Song), NULL, SND_FILENAME || SND_ASYNC || SND_LOOP);

	while (1) {
		if (kbhit()) {
			do key = getch();
			while (key == 224);
		}
		Sleep(200 - speed);

		switch (key) {
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((direction == LEFT && key != RIGHT) ||
				(direction == RIGHT && key != LEFT) ||
				(direction == UP && key != DOWN) ||
				(direction == DOWN && key != UP)) direction = key;
			key = 0;
			break;
		case ESC:
			Gotoxy(X, Y + HEIGHT + 1, "");
			exit(0);
		}
		S_Move();
	}
	return;
}

void S_Setting() {
	system("cls");
	system("mode con: cols=72 lines=26");
	system("title Snake SANS");
	speed = 0;
	return;
}

void S_Title() {
	system("cls");
	S_Draw_map();

	Gotoxy(X + (WIDTH / 2) - 4, Y + (HEIGHT / 2) - 3, "+----------------+");
	Gotoxy(X + (WIDTH / 2) - 4, Y + (HEIGHT / 2) - 2, "S N A K E  G A M E");
	Gotoxy(X + (WIDTH / 2) - 4, Y + (HEIGHT / 2) - 1, "+----------------+");

	Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 1, "<PRESS ANY KEY TO START>");
	Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 3, "◇ ←,→,↑,↓ : Move");
	Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 4, "◇ ESC : Exit");

	while (1) {
		if (kbhit()) {
			key = getch();
			if (key == ESC) {
				Gotoxy(X, Y + HEIGHT + 1, "");
				exit(0);
			}
			else break;
		}
		Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 1, "<PRESS ANY KEY TO START>");
		Sleep(200);
		Gotoxy(X + (WIDTH / 2) - 5, Y + (HEIGHT / 2) + 1, "                        ");
		Sleep(200);
	}
	S_Reset();
	return;
}

void S_Reset() {
	int i;
	system("cls");
	S_Draw_map();

	direction = LEFT;
	length = 3;
	score = 0;

	for (i = 0; i < length; i++) {
		S[i].x = WIDTH / 2 + i;
		S[i].y = HEIGHT / 2;
		Gotoxy(X + S[i].x, Y + S[i].y, "▲");
	}
	Gotoxy(X + S[0].x, Y + S[0].y, "▼");
	S_Food();
	return;
}

void S_Draw_map() {
	int i;
	for (i = X; i < X + WIDTH; i++) Gotoxy(i, Y, "■");
	for (i = Y; i <= Y + HEIGHT; i++) {
		Gotoxy(X, i, "■");
		Gotoxy(X + WIDTH, i, "■");
	}
	for (i = X; i < X + WIDTH; i++) Gotoxy(i, Y + HEIGHT, "■");
	return;
}

void S_Move() {
	int i;

	if (S[0].x == food.x && S[0].y == food.y) {
		score++;
		S_Food();
		if (length < 100) length++;
		if (speed < 150) speed++;
		S[length - 1].x = S[length - 2].x;
		S[length - 1].y = S[length - 2].y;
	}

	if (S[0].x == X - 3 || S[0].x == X + WIDTH - 3) {
		S_Game_over();
		return;
	}
	else if (S[0].y == Y - 2 || S[0].y == Y + HEIGHT - 2) {
		S_Game_over();
		return;
	}

	for (i = 1; i < length; i++) {
		if (S[0].x == S[i].x && S[0].y == S[i].y) {
			S_Game_over();
			return;
		}
	}

	Gotoxy(X + S[length - 1].x, Y + S[length - 1].y, "  ");
	for (i = length - 1; i > 0; i--) {
		S[i].x = S[i - 1].x;
		S[i].y = S[i - 1].y;
	}
	Gotoxy(X + S[i].x, Y + S[i].y, "▲");
	if (direction == LEFT) S[0].x--;
	else if (direction == RIGHT) S[0].x++;
	else if (direction == UP) S[0].y--;
	else if (direction == DOWN) S[0].y++;
	Gotoxy(X + S[i].x, Y + S[i].y, "▼");
	return;
}

void S_Game_over() {
	Gotoxy(X + (WIDTH / 2) - 4, Y + 5, "+------------+");
	Gotoxy(X + (WIDTH / 2) - 4, Y + 6, "| GAME OVER. |");
	Gotoxy(X + (WIDTH / 2) - 4, Y + 7, "+------------+");
	Gotoxy(X + (WIDTH / 2) - 4, Y + 8, "Your Score : ");
	printf("%d", last_score = score);

	Gotoxy(X + (WIDTH / 2) - 6, Y + 12, " Press any keys to Restart.. ");

	if (score > best_score) {
		best_score = score;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
		Gotoxy(X + (WIDTH / 2) - 4, Y + 10, "☆ BEST SCORE ☆");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	}
	Sleep(100);
	key = getch();
	S_Title();
	return;
}

void S_Food() {
	int i;
	int r = 0;
	int food_crush = 0;
	Gotoxy(X, Y + HEIGHT + 1, "YOUR SCORE : ");
	printf("%3d, LAST SCORE : %3d, BEST SCORE : %3d", score, last_score, best_score);

	while (1) {
		food_crush = 0;
		srand((unsigned)time(NULL) + r);
		food.x = (rand() % (WIDTH - 2)) + 1;
		food.y = (rand() % (HEIGHT - 2)) + 1;

		for (i = 0; i < length; i++) {
			if (food.x == S[i].x && food.y == S[i].y) {
				food_crush = 1;
				r++;
				break;
			}
		}

		if (food_crush == 1) continue;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
		Gotoxy(X + food.x, Y + food.y, "♥");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		break;
	}
	return;
}
//////////Sans End//////////