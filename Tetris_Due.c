//===================================== library =====================================

#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

//===================================== define =====================================

// 키보드 키값
#define KEY_A		'a'
#define KEY_S		's'
#define KEY_D		'd'
#define KEY_W		'w'
#define KEY_X		'x'

#define KEY_J		'j'
#define KEY_K		'k'
#define KEY_L		'l'
#define KEY_I		'i'
#define KEY_M		'm'

// 맵 사이즈
#define POS_X		0
#define POS_Y		0
#define POS_X2		32
#define POS_Y2		0
#define WIDTH		12
#define HEIGHT		22

#define ATTACK		5

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

//===================================== Base Function =====================================

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

//===================================== variable =====================================

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
int Game_Display2[22][12] = {
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
int Blocks2[7][4][4][4] = {
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

int bnum = 0, bnum2 = 0;
int brotate = 0, brotate2 = 0;
int bx = 4, by = 1;
int bx2 = 4, by2 = 1;
int score = 0, score2 = 0;
int flag1 = 0, flag2 = 0;

//===================================== P1's Function =====================================

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
		if (Game_Display[line][i + 1] > 0) {
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
		if (score % ATTACK == 0) {
			flag2 = 1;
		}
		drawScreen();
	}
}

void createTrashline() {
	for (int i = 0; i < 20; i++) {
		for (int j = 1; j < 11; j++) {
			Game_Display[i][j] = Game_Display[i + 1][j];
		}
	}

	int blank = rand() % 10;
	for (int i = 1; i < 11; i++) {
		Game_Display[20][i] = 1;
	}
	Game_Display[20][blank + 1] = 0;
	drawScreen();
}

//===================================== P2's Function =====================================

void drawScreen2() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (Game_Display2[i][j] > 1) {
				int color_index = Game_Display2[i][j] - 2;
				int color = BlockColor[color_index];
				GotoColorXY(POS_X2 + j, POS_Y2 + i, "■", color);
			}
			else if (Game_Display2[i][j] == 1) {
				GotoColorXY(POS_X2 + j, POS_Y2 + i, "■", 0x07);
			}
			else {
				GotoColorXY(POS_X2 + j, POS_Y2 + i, "□", 0x07);
			}
		}
	}

	Gotoxy(POS_X2, POS_Y2 + HEIGHT + 2, "SCORE : ");
	printf("%d", score2);
}

void createBlock2() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum2][brotate2][i][j] == 1 && Game_Display2[i + by2][j + bx2] == 0) {
				GotoColorXY(POS_X2 + j + bx2, POS_Y2 + i + by2, "■", BlockColor[bnum2]);
			}
		}
	}
}

void deleteBlock2() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum2][brotate2][i][j] == 1 && Game_Display2[i + by2][j + bx2] == 0) {
				GotoColorXY(POS_X2 + j + bx2, POS_Y2 + i + by2, "□", 0x07);
			}
		}
	}
}

void insertBlock2() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum2][brotate2][i][j] == 1 && Game_Display2[i + by2][j + bx2] == 0) {
				Game_Display2[i + by2][j + bx2] = bnum2 + 2;
			}
		}
	}
}

int checkCrash2(int x, int y) {
	int cnt_crash = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum2][brotate2][i][j] == 1 && Game_Display2[i + y + by2][j + x + bx2] > 0) {
				cnt_crash++;
			}
		}
	}
	return cnt_crash;
}

int checkCrashRotate2() {
	int cnt_crash = 0;
	int tmp_rotate = brotate2;
	tmp_rotate++;
	if (tmp_rotate == 4) tmp_rotate = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Blocks[bnum2][tmp_rotate][i][j] == 1 && Game_Display2[i + by2][j + bx2] > 0) {
				cnt_crash++;
			}
		}
	}
	return cnt_crash;
}

void checkLine2(int line) {
	int check = 0;
	for (int i = 0; i < 10; i++) {
		if (Game_Display2[line][i + 1] > 1) {
			check++;
		}
	}

	if (check == 10) {
		for (int i = line; i > 1; i--) {
			for (int j = 1; j < 11; j++) {
				Game_Display2[i][j] = Game_Display2[i - 1][j];
			}
		}
		score2++;
		if (score2 % ATTACK == 0) {
			flag1 = 1;
		}
		drawScreen2();
	}
}

void createTrashline2() {
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j < 11; j++) {
			Game_Display2[i][j] = Game_Display2[i + 1][j];
		}
	}

	int blank = rand() % 10;
	for (int i = 1; i < 11; i++) {
		Game_Display2[20][i] = 1;
	}
	Game_Display2[20][blank + 1] = 0;
	drawScreen2();
}

//===================================== MAIN =====================================

void main() {
	int cnt = 0;
	int key = 0;

	srand((unsigned int)time(NULL));
	system("cls");
	drawScreen();
	drawScreen2();
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
		else if (key == KEY_X) {
			while (checkCrash(0, 1) == 0) {
				deleteBlock();
				by++;
				createBlock();
			}
		}

		if (key == KEY_J) {
			if (checkCrash2(-1, 0) == 0) {
				deleteBlock2();
				bx2--;
				createBlock2();
			}
		}
		else if (key == KEY_K) {
			if (checkCrash2(0, 1) == 0) {
				deleteBlock2();
				by2++;
				createBlock2();
			}
		}
		else if (key == KEY_L) {
			if (checkCrash2(1, 0) == 0) {
				deleteBlock2();
				bx2++;
				createBlock2();
			}
		}
		else if (key == KEY_I) {
			if (checkCrashRotate2() == 0) {
				deleteBlock2();
				brotate2++;
				if (brotate2 == 4) brotate2 = 0;
				createBlock2();
			}
		}
		else if (key == KEY_M) {
			while (checkCrash2(0, 1) == 0) {
				deleteBlock2();
				by2++;
				createBlock2();
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
					if (flag1) {
						createTrashline();
						flag1 = 0;
					}
				}

				bx = 4;
				by = 1;
				brotate = 0;
				bnum = rand() % 7;
				createBlock();
			}

			if (checkCrash2(0, 1) == 0) {
				deleteBlock2();
				by2++;
				createBlock2();
			}
			else {
				deleteBlock2();
				insertBlock2();
				drawScreen2();
				Sleep(250);

				for (int i = 1; i < 21; i++) {
					checkLine2(i);
					if (flag2) {
						createTrashline2();
						flag2 = 0;
					}
				}

				bx2 = 4;
				by2 = 1;
				brotate2 = 0;
				bnum2 = rand() % 7;
				createBlock2();
			}
		}

		cnt++;
		Sleep(10);
	}
	return;
}
