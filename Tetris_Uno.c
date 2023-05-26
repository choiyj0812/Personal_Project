// 라이브러리
#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// 키보드 키값
#define KEY_A		'a'
#define KEY_S		's'
#define KEY_D		'd'
#define KEY_W		'w'
#define KEY_SPACE	' '

#define KEY_J	75
#define KEY_K	80
#define KEY_L	77
#define KEY_I		72
#define KEY_ESC		27

// 맵 사이즈
#define POS_X		0
#define POS_Y		0
#define WIDTH		12
#define HEIGHT		22

// 색깔
enum COLOR {
	BLACK = 0x00,
	BLUE,
	GREEN,
	TURQUOISE,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	BLUE_L,
	GREEN_L,
	TURQUOISE_L,
	RED_L,
	PURPLE_L,
	YELLOW_L,
	WHITE_L
};

// 좌표 이동 함수
void Gotoxy(int x, int y, const char* word) {
	COORD pos = { (short)x * 2, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", word);
	return;
}

// 출력 색 지정 함수
void Setcolor(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void GotoColorXY(int x, int y, const char* word, int c) {
	Setcolor(c);
	Gotoxy(x, y, word);
}

// 맵 배열
int Game_Display[22][12] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 블록 배열
int Blocks[7][4][4][4] = {
	// I자형
	{
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0}
		}
	},
	// L자형
	{
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		}
	},
	// J자형
	{
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		}
	},
	// T자형
	{
		{
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		}
	},
	// O자형
	{
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}
	},
	// S자형
	{
		{
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		}
	},
	// Z자형
	{
		{
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}
	}
};

// 블록에 대한 색
int BlockColor[7] = {
	BLUE,
	GREEN,
	RED,
	YELLOW,
	PURPLE,
	GRAY,
	TURQUOISE
};

int bnum = 0;
int brotate = 0;
int bx = 4, by = 1;
int score = 0;

void drawScreen() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (Game_Display[i][j] > 1) {
				int color_index = Game_Display[i][j] - 2;
				int color = BlockColor[color_index];
				GotoColorXY(POS_X + j, POS_Y + i, "■", color);
			}
			else if (Game_Display[i][j] == 1) {
				GotoColorXY(POS_X + j, POS_Y + i, "■", 0x07);
			}
			else {
				GotoColorXY(POS_X + j, POS_Y + i, "□", 0x07);
			}
		}
	}

	Gotoxy(POS_X, POS_Y + HEIGHT + 2, "SCORE : ");
	printf("%d", score);
}

void createBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum][brotate][i][j] == 1 && Game_Display[i + by][j + bx] == 0) {
				GotoColorXY(POS_X + j + bx, POS_Y + i + by, "■", BlockColor[bnum]);
			}
		}
	}
}

void deleteBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum][brotate][i][j] == 1 && Game_Display[i + by][j + bx] == 0) {
				GotoColorXY(POS_X + j + bx, POS_Y + i + by, "□", 0x07);
			}
		}
	}
}

void insertBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum][brotate][i][j] == 1 && Game_Display[i + by][j + bx] == 0) {
				Game_Display[i + by][j + bx] = bnum + 2;
			}
		}
	}
}

int checkCrash(int x, int y) {
	int cnt_crash = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum][brotate][i][j] == 1 && Game_Display[i + y + by][j + x + bx] > 0) {
				cnt_crash++;
			}
		}
	}
	return cnt_crash;
}

int checkCrashRotate() {
	int cnt_crash = 0;
	int tmp_rotate = brotate;
	tmp_rotate++;
	if (tmp_rotate == 4) tmp_rotate = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum][tmp_rotate][i][j] == 1 && Game_Display[i + by][j + bx] > 0) {
				cnt_crash++;
			}
		}
	}
	return cnt_crash;
}

void checkLine(int line) {
	int check = 0;
	for (int i = 0; i < 10; i++) {
		if (Game_Display[line][i + 1] > 1) {
			check++;
		}
	}

	if (check == 10) {
		for (int i = line; i > 1; i--) {
			for (int j = 1; j < 11; j++) {
				Game_Display[i][j] = Game_Display[i - 1][j];
			}
		}
		score++;
		drawScreen();
	}
}

void main() {
	int cnt = 0;
	int key = 0;

	srand((unsigned int)time(NULL));
	system("cls");
	drawScreen();
	while (1) {
		key = 0;
		if (kbhit()) {
			do key = getch();
			while (key == 224);
		}

		if (key == KEY_A) {
			if (checkCrash(-1, 0) == 0) {
				deleteBlock();
				bx--;
				createBlock();
			}
		}
		else if (key == KEY_S) {
			if (checkCrash(0, 1) == 0) {
				deleteBlock();
				by++;
				createBlock();
			}
		}
		else if (key == KEY_D) {
			if (checkCrash(1, 0) == 0) {
				deleteBlock();
				bx++;
				createBlock();
			}
		}
		else if (key == KEY_W) {
			if (checkCrashRotate() == 0) {
				deleteBlock();
				brotate++;
				if (brotate == 4) brotate = 0;
				createBlock();
			}
		}
		else if (key == KEY_SPACE) {
			while (checkCrash(0, 1) == 0) {
				deleteBlock();
				by++;
				Sleep(5);
				createBlock();
			}
		}

		if (cnt == 50) {
			cnt = 0;

			if (checkCrash(0, 1) == 0) {
				deleteBlock();
				by++;
				createBlock();
			}
			else {
				deleteBlock();
				insertBlock();
				drawScreen();
				Sleep(250);

				for (int i = 1; i < 21; i++) {
					checkLine(i);
				}

				bx = 4;
				by = 1;
				brotate = 0;
				bnum = rand() % 7;
				createBlock();
			}
		}

		cnt++;
		Sleep(10);
	}
	return;
}
