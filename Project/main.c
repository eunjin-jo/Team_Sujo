#include <stdio.h>
#include <Windows.h>


//모든 서식을 기본값으로 
#define COLOR_RESET "\x1b[0m"

#define FONT_COLOR_BLACK 30
#define BG_COLOR_BLACK 40
#define FONT_COLOR_RED 31
#define BG_COLOR_RED 41
#define FONT_COLOR_GREEN 32
#define BG_COLOR_GREEN 42
#define FONT_COLOR_YELLOW 33
#define BG_COLOR_YELLOW 43
#define FONT_COLOR_BLUE 34
#define BG_COLOR_BLUE 44
#define FONT_COLOR_MAGENTA 35
#define BG_COLOR_MAGENTA 45
#define FONT_COLOR_CYAN 36
#define BG_COLOR_CYAN 46
#define FONT_COLOR_WHITE 37
#define BG_COLOR_WHITE 47

#define FONT_COLOR_BRIGHTMAGENTA 95
#define BG_COLOR_BRIGHTMAGENTA 105

/*
 * -2: 게임 시작힐때 로고 / GAMESTATE_LOGO
 *
 * -2: 게임종료 화면으로 전환 / GAMESTATE_EXIT_ANIMATION
 * -1: 게임종료 / GAMESTATE_QUIT
 * 0 : 게임 시작 / GAMESTATE_START
 *
 * 1 : 게임 타이틀 화면 / GAMESTATE_TITLE
 * 2 : 게임 타이틀 화면으로 전환 / GAMESTATE_TITLE_ENTER
 * 3 : 게임 타이틀 화면 종료 / GAMESTATE_TITLE_EXIT
 *
 *  4: 게임 플레이 화면으로 전환 / GAMESTATE_GAME_ENTER
 *  5: 게임 플레이 중 / GAMESTATE_GAME
 *  6: 게임 플레이 화면 종료 / GAMESTATE_GAME_EXIT
 *
 * 7 : 플레이 방법 / GAMESTATE_HELP
 * 8 : 플레이 방법 진입 / GAMESTATE_HELP_ENTER
 * 9 : 플레이 방법 종료 / GAMESTATE_HELP_EXIT
 *
 * 10: 팀 소개 / GAMESTATE_CREDITS
 * 11: 팀 소개 진입 / GAMESTATE_CREDITS_ENTER
 * 12: 팀 소개 종료 / GAMESTATE_CREDITS_EXIT
 */
#define GAMESTATE_LOGO -3

#define GAMESTATE_EXIT_ANIMATION -2
#define GAMESTATE_QUIT -1
#define GAMESTATE_START 0

#define GAMESTATE_TITLE 1
#define GAMESTATE_TITLE_ENTER 2
#define GAMESTATE_TITLE_EXIT 3

#define GAMESTATE_GAME_ENTER 4
#define GAMESTATE_GAME 5
#define GAMESTATE_GAME_EXIT 6

#define GAMESTATE_HELP 7
#define GAMESTATE_HELP_ENTER 8
#define GAMESTATE_HELP_EXIT 9

#define GAMESTATE_CREDITS 10
#define GAMESTATE_CREDITS_ENTER 11
#define GAMESTATE_CREDITS_EXIT 12

void set_color(int code)
{
	printf("\x1b[%dm", code);
}

int move_cursor(int x, int y)
{
	printf("\033[%d;%dH", y, x);
	return 0;
}

int ProcessInput();
int Update();
int Render();

int gameState = 0;
int TitleMenu = 1;

int RenderLogo() {
	printf(" 메인로고 \n");
	return 0;
}

int RenderTitle() {


	set_color(FONT_COLOR_WHITE);
	move_cursor(50, 9);
	printf("                     ");
	move_cursor(50, 10);
	printf(" 타이틀 ");
	move_cursor(50, 11);
	printf("                     ");

	printf(COLOR_RESET);

	if (TitleMenu == 1)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(52, 13);
	printf("  1. 게임  시작  ");
	printf(COLOR_RESET);

	if (TitleMenu == 2)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(52, 15);
	printf("  2. 플레이 방법  ");
	printf(COLOR_RESET);

	if (TitleMenu == 3)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(52, 17);
	printf("  3. 팀 소개  ");
	printf(COLOR_RESET);

	if (TitleMenu == 4)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(52, 19);
	printf("  4. 게임 종료  ");
	printf(COLOR_RESET);

	return 0;
}

int RenderGame() {
	move_cursor(0, 0);

	printf("게임플레이화면\n");



	return 0;
}

int RenderHelp() {
	move_cursor(0, 0);

	printf("게임설명 페이지\n");



	return 0;
}

int RenderCredits() {
	move_cursor(0, 0);

	printf("팀 소개 페이지\n");



	return 0;
}


int ProcessTitleInput() {
	char input = _getch();
	switch (input)
	{
	case 'w':
		if (TitleMenu > 1)
		{
			TitleMenu = TitleMenu - 1;
		}
		break;
	case 's':
		if (TitleMenu < 4)
		{
			TitleMenu = TitleMenu + 1;
		}
		break;
	case 13:
		if (TitleMenu == 1)
			gameState = GAMESTATE_GAME_ENTER;
		if (TitleMenu == 2)
			gameState = GAMESTATE_HELP_ENTER;
		if (TitleMenu == 3)
			gameState = GAMESTATE_CREDITS_ENTER;
		if (TitleMenu == 4)
			gameState = GAMESTATE_EXIT_ANIMATION;
		break;
	case 27:
		gameState = GAMESTATE_EXIT_ANIMATION;
		break;
	}

	return 0;
}

int ProcessMeunInput() {
	char input = _getch();
	switch (input)
	{
	case 27:
		gameState = GAMESTATE_TITLE_ENTER;
		break;
	}

	return 0;
}

int ProcessGameInput() {
	char input = getch();
	switch (input)
	{
	case 27:
		gameState = GAMESTATE_TITLE_ENTER;
		break;
	}

	return 0;
}



int main()
{
	gameState = GAMESTATE_START;

	while (gameState != GAMESTATE_QUIT)
	{
		ProcessInput();
		Update();
		Render();
		Sleep(300);
	}

	return 0;
}

int ProcessInput()
{
	switch (gameState)
	{
	case GAMESTATE_TITLE:
		ProcessTitleInput();
		break;
	case GAMESTATE_GAME:
		ProcessGameInput();
		break;
	case GAMESTATE_HELP:
		ProcessMeunInput();
		break;
	case GAMESTATE_CREDITS:
		ProcessMeunInput();
		break;
	}

	return 0;
}

int Update()
{
	switch (gameState)
	{
	case GAMESTATE_START:
		gameState = GAMESTATE_LOGO;
		break;
	case GAMESTATE_LOGO:
		Sleep(5000);
		gameState = GAMESTATE_TITLE_ENTER;
		break;
	case GAMESTATE_TITLE_ENTER:
		system("cls");
		gameState = GAMESTATE_TITLE;
		break;
	case GAMESTATE_HELP_ENTER:
		system("cls");
		gameState = GAMESTATE_HELP;
		break;
	case GAMESTATE_CREDITS_ENTER:
		system("cls");
		gameState = GAMESTATE_CREDITS;
		break;
	case GAMESTATE_GAME_ENTER:
		system("cls");
		gameState = GAMESTATE_GAME;
		break;
	case GAMESTATE_EXIT_ANIMATION:
		gameState = GAMESTATE_TITLE_EXIT;
		system("cls");
		break;
	case GAMESTATE_TITLE_EXIT:
		Sleep(2000);
		gameState = GAMESTATE_QUIT;
		break;

	}

	return 0;
}

int Render()
{
	switch (gameState)
	{
	case GAMESTATE_LOGO:
		RenderLogo();
		break;
	case GAMESTATE_TITLE:
		RenderTitle();
		break;
	case GAMESTATE_HELP:
		RenderHelp();
		break;
	case GAMESTATE_CREDITS:
		RenderCredits();
		break;
	case GAMESTATE_TITLE_EXIT:
		printf("\n게임 종료 중...\n");
		break;
	case GAMESTATE_QUIT:
		system("cls");
		printf("\n\n 게임 종료.");
		break;
	case GAMESTATE_GAME:
		RenderGame();
		break;
	}

	return 0;
}