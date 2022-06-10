#pragma warning(disable:4996)
#pragma warning(disable:6001)
#pragma warning(disable:6031)
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

#define ESC 27
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void Gotoxy(int x, int y, const char* str);		//원하는 좌표로 이동
void Setting();									//기본 세팅
int Random();									//랜덤 수
void Print_Score();
void Arrow_Up();								//위쪽 화살표 출력
void Arrow_Down();								//아래쪽 화살표 출력
void Arrow_Left();								//왼쪽 화살표 출력
void Arrow_Right();								//오른쪽 화살표 출력
void Arrow_Center();							//가운데 원 출력
void Game_Over();								//게임 종료
void Defense();									//수비 상황
void Attack();									//공격 상황

int Score, Last_Score, Best_Score, Worst_Score;
int key;
int AI_Choose;
bool Win, mode;

int main() {
	Setting();
	while (1) {
		Win = false;
		mode = false;
		while (1) {
			if (mode == true) {
				Attack();
				if (key == AI_Choose) {
					Win = true;
					break;
				}
				Sleep(1500);
				mode = false;
			}
			else if (mode == false) {
				Defense();
				if (key == AI_Choose) break;
				else Score++;
				Sleep(1500);
				mode = true;
			}
		}
		Game_Over();
		while (1) {
			if (kbhit()) {
				_getch();
				break;
			}
		}
		key = getch();
		if (key == ESC) break;
	}
	return 0;
}

void Gotoxy(int x, int y, const char* str) {
	COORD POS = { (short)x * 2, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
	printf("%s", str);
	return;
}

void Setting() {
	system("cls");
	system("title Cham*3");
	system("mode con: cols=28 lines=27");
	Score = Last_Score = Worst_Score = 0;
	Best_Score = 1000;
	Win = mode = false;
	return;
}

int Random() {
	srand((unsigned int)time(NULL));
	int R = rand() % 4;
	if (R == 0) return UP;
	else if (R == 1) return LEFT;
	else if (R == 2) return RIGHT;
	else if (R == 3) return DOWN;
	return 0;
}

void Print_Score() {
	Gotoxy(0, 16, "");
	printf("      Score : %d", Score);
	Gotoxy(0, 17, "");
	printf(" Last_score : %d", Last_Score);
	Gotoxy(0, 18, "");
	printf(" Best_score : %d", Best_Score);
	Gotoxy(0, 19, "");
	printf("Worst_score : %d", Worst_Score);
	Gotoxy(0, 20, "");
	if (mode)
		printf("현재 당신은 공격입니다.");
	else
		printf("현재 당신은 수비입니다.");
	return;
}

void Arrow_Up() {
	Gotoxy(0, 0, "");
	printf("            ■■            \n");
	printf("            ■■            \n");
	printf("        ■■■■■■        \n");
	printf("        ■■■■■■        \n");
	printf("    ■■■■    ■■■■    \n");
	printf("    ■■■■    ■■■■    \n");
	printf("■■    ■■    ■■    ■■\n");
	printf("■■    ■■    ■■    ■■\n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	return;
}

void Arrow_Down() {
	Gotoxy(0, 0, "");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("■■    ■■    ■■    ■■\n");
	printf("■■    ■■    ■■    ■■\n");
	printf("    ■■■■    ■■■■    \n");
	printf("    ■■■■    ■■■■    \n");
	printf("        ■■    ■■        \n");
	printf("        ■■    ■■        \n");
	printf("            ■■            \n");
	printf("            ■■            \n");
	return;
}

void Arrow_Left() {
	Gotoxy(0, 0, "");
	printf("            ■■            \n");
	printf("            ■■            \n");
	printf("        ■■                \n");
	printf("        ■■                \n");
	printf("    ■■■■■■■■■■■■\n");
	printf("    ■■■■■■■■■■■■\n");
	printf("■■■■                    \n");
	printf("■■■■                    \n");
	printf("    ■■■■■■■■■■■■\n");
	printf("    ■■■■■■■■■■■■\n");
	printf("        ■■                \n");
	printf("        ■■                \n");
	printf("            ■■            \n");
	printf("            ■■            \n");
	return;
}

void Arrow_Right() {
	Gotoxy(0, 0, "");
	printf("            ■■            \n");
	printf("            ■■            \n");
	printf("                ■■        \n");
	printf("                ■■        \n");
	printf("■■■■■■■■■■■■    \n");
	printf("■■■■■■■■■■■■    \n");
	printf("                    ■■■■\n");
	printf("                    ■■■■\n");
	printf("■■■■■■■■■■■■    \n");
	printf("■■■■■■■■■■■■    \n");
	printf("                ■■        \n");
	printf("                ■■        \n");
	printf("            ■■            \n");
	printf("            ■■            \n");
	return;
}

void Arrow_Center() {
	Gotoxy(0, 0, "");
	printf("        ■■■■■■        \n");
	printf("        ■■■■■■        \n");
	printf("    ■■■■■■■■■■    \n");
	printf("    ■■■■■■■■■■    \n");
	printf("■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■\n");
	printf("    ■■■■■■■■■■    \n");
	printf("    ■■■■■■■■■■    \n");
	printf("        ■■■■■■        \n");
	printf("        ■■■■■■        \n");
	return;
}

void Game_Over() {
	system("cls");
	if (Win) {
		if (Score < Best_Score)
			Best_Score = Score;
		if (Score > Worst_Score)
			Worst_Score = Score;
	}
	if (Win) Last_Score = Score;
	Score = 0;
	Print_Score();
	Gotoxy(0, 8, "다시 하시겠습니까?");
	return;
}

void Defense() {
	Arrow_Center();
	Print_Score();

	Gotoxy(0, 15, "참              ");
	Sleep(500);
	Gotoxy(0, 15, "       참       ");
	Sleep(500);
	AI_Choose = Random();
	Gotoxy(0, 15, "              참");
	Sleep(500);

	Gotoxy(0, 15, "방향을 정하세요!");
	while (1) {
		if (kbhit()) {
			_getch();
			break;
		}
	}
	key = getch();

	system("cls");
	switch (AI_Choose) {
	case UP:
		Arrow_Up();
		break;
	case LEFT:
		Arrow_Left();
		break;
	case RIGHT:
		Arrow_Right();
		break;
	case DOWN:
		Arrow_Down();
		break;
	}
	Print_Score();
	Sleep(500);
	return;
}

void Attack() {
	Arrow_Center();
	Gotoxy(0, 15, "방향을 정하세요!");
	Print_Score();

	while (1) {
		if (kbhit()) {
			_getch();
			break;
		}
	}
	key = getch();

	Gotoxy(0, 15, "참              ");
	Sleep(500);
	Gotoxy(0, 15, "       참       ");
	Sleep(500);
	AI_Choose = Random();
	Gotoxy(0, 15, "              참");
	Sleep(500);

	system("cls");
	switch (AI_Choose) {
	case UP:
		Arrow_Up();
		break;
	case LEFT:
		Arrow_Left();
		break;
	case RIGHT:
		Arrow_Right();
		break;
	case DOWN:
		Arrow_Down();
		break;
	}
	Print_Score();
	Sleep(500);
	return;
}
