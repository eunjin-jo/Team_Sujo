#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

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
 * -3: 게임 시작 로고 / GAMESTATE_LOGO
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
int gameStage = 5;

/*-----------------------------------------------------------------------------------------------------------*/

int main()
{
	printf("\033[?25l"); //마우스 커서 숨김

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
		ProcessMenuInput();
		break;
	case GAMESTATE_CREDITS:
		ProcessMenuInput();
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
		system("cls");
		gameState = GAMESTATE_TITLE_ENTER;
		break;

	case GAMESTATE_TITLE_ENTER:
		system("cls");
		gameState = GAMESTATE_TITLE;
		break;

	case GAMESTATE_HELP_ENTER:
		gameState = GAMESTATE_HELP;
		break;

	case GAMESTATE_CREDITS_ENTER:
		gameState = GAMESTATE_CREDITS;
		break;

	case GAMESTATE_GAME_ENTER:
		system("cls");
		gameState = GAMESTATE_GAME;
		break;

	case GAMESTATE_EXIT_ANIMATION:
		gameState = GAMESTATE_TITLE_EXIT;
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
		system("cls");
		RenderHelp();
		break;

	case GAMESTATE_CREDITS:
		system("cls");
		RenderCredits();
		break;

	case GAMESTATE_GAME:
		RenderGame();
		break;

	case GAMESTATE_TITLE_EXIT:
		printf("\n게임 종료 중...\n");
		break;

	case GAMESTATE_QUIT:
		system("cls");
		printf("\n\n 게임 종료.");
		break;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int ProcessTitleInput() {
	char input = _getch();
	switch (input)
	{
	case 72:
		if (TitleMenu > 1)
		{
			TitleMenu = TitleMenu - 1;
		}
		break;
	case 80:
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

int ProcessMenuInput() {
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
	if (!_kbhit())
		return 0;

	char input = _getch();

	switch (input)
	{
	case 27:
		gameState = GAMESTATE_TITLE_ENTER;
		break;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int RenderGame() {

	AddGameScreen();

	//gameStage -2 : 배드엔딩
	//gameStage 0 : 프롤로그
	//gameStage 1 : 스테이지 1
	//gameStage 2 : 스테이지 2
	//gameStage 3 : 스테이지 3


	switch (gameStage) {
	case -3:
		Ending_bad_CheckPoint_1();
		break;
	case -2:
		Ending_bad();
		break;
	case 0:
		gameStage_prolog();
		break;
	case 1:
		gameStage_1();
		break;
	case 2:
		gameStage_2();
		break;
	case 3:
		gameStage_3();
		break;
	case 4:
		gameStage_4();
		break;
	case 5:
		gameStage_5();
		break;
	//case 6:
	//	gameStage_6();
	//	break;
	//case 7:
	//	gameStage_7();
	//	break;
	}
	return 0;
}
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


int RenderHelp() {
	move_cursor(1, 1);
	printf("                                                          \n");
	printf("                                                                                           ================================\n");
	printf("\n");
	printf("                                                                                                  게임 플레이 가이드\n");
	printf("\n");
	printf("                                                                                           ================================\n");
	printf("\n");
	printf("\n");
	printf("\033[1m                                                                   《30살까지 모솔이면 마법사가 된다는 소문이 사실인 것 같습니다》\033[0m\n");
	printf("\n");

	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");
	printf("                                                                   ■ 이 게임은 뭔가요?\n");
	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");

	printf("\n");
	printf("                                                                   마법사가 되어버린 30살 모솔 남자가\n");
	printf("                                                                   매일 아침으로 리셋되는 타임 루프 속에서\n");
	printf("                                                                   히로인의 마음을 얻어 루프를 탈출하는\n");
	printf("                                                                   선택형 시뮬레이션 게임입니다.\n");
	printf("\n");
	printf(BOLD "                                                                   쉽게 말하면,\n" RESET);
	printf("                                                                   고백 한 번 못 해서 매일 같은 하루를 살고 있습니다.\n");
	printf("                                                                   직접 플레이해서 주인공을 도와주세요.\n");

	printf("\n");
	printf("\n");

	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");
	printf("                                                                   ■ 조작 방법\n");
	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");

	printf("\n");
	printf("                                                                   게임은 키보드를 통해 간편하게 조작할 수 있습니다.\n");
	printf("                                                                   - 선택 및 진행 : " GREEN "Enter" RESET "\n");
	printf("                                                                   - 선택지 이동 : " GREEN "↑ ↓ ← →" RESET " (방향키)\n");

	printf("\n");
	printf("\n");

	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");
	printf("                                                                   ■ 진행 방식\n");
	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");

	printf("\n");

	printf("                                                                   1. 시스템 창의 안내에 따라 퀘스트를 진행하세요.\n");

	printf("\n");
	printf("                                                                   매 파트마다 선택지 3가지가 주어집니다.\n");
	printf("                                                                   그 중 하나를 골라 스토리를 이어가세요.\n");
	printf("                                                                   선택에 따라 결과가 즉시 달라집니다.\n");

	printf("\n");

	printf("                                                                   2. 히로인 공략\n");

	printf("\n");
	printf("                                                                   주변의 히로인들과 마주하며 신중하게 대화를 이어나가세요.\n");
	printf("                                                                   단 한 번이라도 잘못된 선택지를 선택한 순간\n");
	printf(RED "                                                                   다시 처음으로 돌아가게 됩니다.\n" RESET);
	printf("\n");
	printf("                                                                   3. 최종 목표\n");

	printf("\n");
	printf("                                                                   반복되는 루프 속에서\n");
	printf(YELLOW "                                                                   진정한 히로인 공략에 성공하여 Loop를 끝내세요.\n" RESET);

	printf("\n");
	printf("\n");

	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");
	printf("                                                                   ■ 플레이 팁\n");
	printf("                                                                   ────────────────────────────────────────────────────────────────────────────────\n");

	printf("\n");

	printf("                                                                   ▶ 관찰하세요.\n");
	printf("                                                                   히로인의 반응을 보면 힌트가 있습니다.\n");
	printf("                                                                   대사 한 줄도 허투루 읽지 마세요.\n");

	printf("\n");

	printf("                                                                   ▶ 무리하지 마세요.\n");
	printf("                                                                   억지스러운 멘트나 지나친 적극성은\n");
	printf(RED "                                                                   대부분 배드엔딩으로 직결됩니다.\n" RESET);
	printf("                                                                   자연스러운 쪽이 정답인 경우가 많습니다.\n");

	printf("\n");

	printf("                                                                   ▶ 고백은 타이밍입니다.\n");
	printf("                                                                   분위기를 만들어놓고 우물쭈물하면\n");
	printf("                                                                   루프는 하루 더 늘어납니다.\n");
	return 0;
}

int RenderCredits() {
	move_cursor(1, 1);

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("  ================================\n");
	printf("\n");
	printf("             T E A M  수조  \n");
	printf("\n");
	printf("  ================================\n");
	printf("\n");
	printf("\n");
	printf("  조은진(팀장) : \n");
	printf("  윤수아 : \n");
	printf("  이세빈 : \n");
	printf("  송한이 : \n");
	return 0;
}

int RenderLogo() {
	move_cursor(1, 5);
	printf("\n");
	printf("\n");
	printf("                                                         ,!**!,          ,,,                                                                                                                                  \n");
	printf("                                                       ,$!-'~#$=     .=$$;#:$:.                                                                                                                               \n");
	printf("                                                      .#=.   *@@=   #@$= ' !##$,                                                                                                                             \n");
	printf("                                                           ,*@*~  ,$@@,     -#@+,   .   *&            #$         #$                                                                                                   \n");
	printf("                                                        ,;=@#=!   ~@@~      ~@@@,  ~$.  *#'  #$$#!$##$@$ #$#$$#$#@#                                                                                                   \n");
	printf("                                                         ..,=@@= .#@@~      -$@#, ,$~#. *#$@    ,$:$# @$    #$   $#                                                                                                \n");
	printf("                                                             $@@*,#@@~      -$@; ,$' ~& *@    ,$#,~#  #$##4 $$,  #&                                                                                        \n");
	printf("                                                             =@@$-@@@~.    -#@@-   !$$!#$$  ,$' ,#'   @#  ,#''$;,##                                                                                         \n");
	printf("                                                     ~~,    ,$@@!.'!@#,.  ,;$#-    #;'''''            @$ '     ''@$                                                                                        \n");
	printf("                                                      =@@~.=@@:'    -#@~,$$#=,     $#&#&#&'                      $#!,                    ''@#$'                                                                                    \n");
	printf("                                                         ''''          '''                    -#@;##$-@#       ,#';#,              @#&@&&   &#                                                           \n");
	printf("                                                                                              +@;    @#      .&' @ '#,-,  ~==;. $  $   ;$'&$$@                                                                \n");
	printf("                                                                                              +@;    @#  .!$#.&#$@$###@$ ~/''$;.$  $,,,@#   $#                                                                   \n");
	printf("                                                                         .-                   ,##$@*&:#     ,,,,,,,,,,   #.  .*,#  $#$$#$.$$#$                                                                   \n");
	printf("                                                                          .-                     ;@,        ''''''''$&   !@  ~;.$           #@                                                             \n");
	printf("                                                                           :#-                   ;@,        ~&&#&@!=@#    .$#.  $   &$.                                                                       \n");
	printf("                                                                          -:##&,            #$#&$#@#####!,   $@,,,,,,,,          ,  #$@#&@#&&$#@#<,,. .=                                                                    \n");
	printf("                                                                      ~~   :@@-                 ~;#@!                                                                                    \n");
	printf("                                                           '&#@@@#&#@$@@#. :@@-    '$&#~   -@@*  ,$@-            ';#**.                                                                                       \n");
	printf("                                                            .$@@~    *@@;  :@@-     '#@:    @@!  ~#@.       #     .*@#,                                                                                       \n");
	printf("                                                             $@@     *@@   ,$@#@##~ -@@#$$@#@#*##@@@.      *@=     ;@=.                                                                             \n");
	printf("                                                             $@@     =@@   -@@;'    -@@+   @@$   !@;      ~#@:     ;@=!$@;,    .'&*    #@@$#&-$      ;##  #&.                                                  \n");
	printf("                                                            .#@@    ,=@@   -@@~     -##&@$$&@#   !#      ,=@!*     !@!~~~-#!$&$*.#:    $&    ,# @#&#$;$#  &&......                                                  \n");
	printf("                                                            *@@@#$$=#@=@   ~@@~        :$=,     !@#,    -#!. @@*  .!@-       &$  @$#*, &#$$$$-@ #$    ##. ''''''''                                            \n");
	printf("                                                           ''*=      !,    ;@@~         *@@     ;@@,   -@!    $@$ ,=@-      ~$'  @        $$ ~$ #$    @#$'@#&#@&#@;  -~,.~.                                    \n");
	printf("                                                                          ,#@#-         *@@@&#&$;@#, .,#;      @= -$@-     -$'   @    &#@$@$$@$ #$##$:#'  @#                .                                  \n");
	printf("                                                                          ,@#:          *@@,    !@!               ~#@-           @      $$ .-,        #   $#@#$@##       ,,                                 \n");
	printf("                                                                        ,:*!.           !##&@&#@#@*.         =@#   ~*.                  @$#$@$#@                          ~,                                   \n");
	printf("                                                 ,        @&$&@$&                           ~@$-       .~~.  '@@                                                                                             \n");
	printf("                                                ,#:.      #$   @$    ..    &          ,$~   ,@!        -@:    @@;        ,               ,           $        $                                               \n");
	printf("                                               -#*${      #$#$$@$    $#,   $~        -$@;   ;@!       =#=;,   @#    ,#,  $=  .#.   #,   ,#-    @#    #: @$#$@ #                                                \n");
	printf("                                             .='    #@  @&#$&@$@#&!,!#  $!.#        -@@$,    @@=*@- !@'  :@;  @#   ~# &; ## #& '$@##   ,$  @,  #$    #  @$    #                                                \n");
	printf("                                                :=,       , ~#      ;#  = .$       -@!  !@: .@#:      .,,,,,.;!    :#,#! $,  '!' , $ @&#$@&@$@:#$.,. @  #$    #@##^                                            \n");
	printf("                                            @#@#$$#@#!#@ :@~~*       '#   .$      ~@!   .$@ .@$,      @$#$@$##@.    :!:  $.    $ #     $#,,#   $&@$# @  @@#%# #                                               \n");
	printf("                                            ~            :@*;;;;:          ~   -::~      -  .@=              #$          #   ;,*$.;:   $@''#         @        #       . -                                   \n");
	printf("                                                         .~~~~~~~             .,~           .@=       ,@=&@#&@#          ~ '.$ ,$ ,#   @&$#$         ~       .~           ,                                   \n");
	printf("                                 .                                                          *#~       :@*      *                                            -                                                 \n");
	printf("                                ;.                     .                                    #$       .#@@$$$$##@;                                           :            .!                                   \n");
	printf("                                                                                           ;=           -                               , ~=##$*~.                        $                                    \n");
	printf("                                                   .                                     '                                           ,=-           :$=.     ;,         .#.                                     \n");
	printf("                                 :  .,...    ..                                                                                     ,-                 ,!**##=;~--~;:!-                                        \n");
	printf("                                   ,;*!;~.                                                                      ..                 !                     ,;;. ..                                              \n");
	printf("                                                                                                         .      ~-  -.             .                   .~.    --                                              \n");
	printf("                                                                                                                    -, ~-            .                ~.-                                                     \n");
	printf("                                                                                                                      -, -;.                       ~ ,                                                       \n");
	printf("                                                                                                                         ., :!.               .:. .                                                         \n");
	printf("                                                                                                                              ..    -;**!!==:.   .                                                            \n");

	return 0;
}


int RenderTitle() {

	set_color(FONT_COLOR_WHITE);
	move_cursor(90, 16);
	printf("                     ");
	move_cursor(90, 17);
	printf(" 30살 까지 모솔이면");
	move_cursor(82, 18);
	printf("마법사가 된다는 소문이 사실이었습니다 ");
	move_cursor(90, 19);
	printf("                     ");

	printf(COLOR_RESET);

	if (TitleMenu == 1)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(92, 21);
	printf("  1. 게임  시작  ");
	printf(COLOR_RESET);

	if (TitleMenu == 2)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(92, 23);
	printf("  2. 플레이 방법  ");
	printf(COLOR_RESET);

	if (TitleMenu == 3)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(92, 25);
	printf("  3. 팀 소개  ");
	printf(COLOR_RESET);

	if (TitleMenu == 4)
	{
		set_color(BG_COLOR_YELLOW);
	}
	move_cursor(92, 27);
	printf("  4. 게임 종료  ");
	printf(COLOR_RESET);

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int AddGameScreen() {
	int story_left = 1;
	int story_right = 125;
	int story_height = 50;
	int story_top = 1;

	int menu_left = 135;
	int menu_right = 180;
	int menu_height = 35;
	int menu_top = 1;

	int story_bottom = story_top + story_height - 1;
	int menu_bottom = menu_top + menu_height - 1;

	int input_left = menu_left;
	int input_right = menu_right;
	int input_top = menu_bottom + 2;
	int input_bottom = input_top + 6;

	// 왼쪽 스토리창
	for (int x = story_left; x <= story_right; x++)
	{
		move_cursor(x, story_top);

		if (x == story_left) printf("┌");
		else if (x == story_right) printf("┐");
		else printf("─");
	}

	for (int y = story_top + 1; y < story_bottom; y++)
	{
		move_cursor(story_left, y);
		printf("│");

		move_cursor(story_right, y);
		printf("│");
	}

	for (int x = story_left; x <= story_right; x++)
	{
		move_cursor(x, story_bottom);

		if (x == story_left) printf("└");
		else if (x == story_right) printf("┘");
		else printf("─");
	}


	// 오른쪽 선택지창
	for (int x = menu_left; x <= menu_right; x++)
	{
		move_cursor(x, menu_top);

		if (x == menu_left) printf("┌");
		else if (x == menu_right) printf("┐");
		else printf("─");
	}

	for (int y = menu_top + 1; y < menu_bottom; y++)
	{
		move_cursor(menu_left, y);
		printf("│");

		move_cursor(menu_right, y);
		printf("│");
	}

	for (int x = menu_left; x <= menu_right; x++)
	{
		move_cursor(x, menu_bottom);

		if (x == menu_left) printf("└");
		else if (x == menu_right) printf("┘");
		else printf("─");
	}


	// 오른쪽 하단 입력창
	for (int x = input_left; x <= input_right; x++)
	{
		move_cursor(x, input_top);

		if (x == input_left) printf("┌");
		else if (x == input_right) printf("┐");
		else printf("─");
	}

	for (int y = input_top + 1; y < input_bottom; y++)
	{
		move_cursor(input_left, y);
		printf("│");

		move_cursor(input_right, y);
		printf("│");
	}

	for (int x = input_left; x <= input_right; x++)
	{
		move_cursor(x, input_bottom);

		if (x == input_left) printf("└");
		else if (x == input_right) printf("┘");
		else printf("─");
	}



	move_cursor(153, 4);
	printf("< 시스템 >");

	move_cursor(input_left + 2, input_top + 3);
	printf("선택지 > ");

	move_cursor(146, 40);
	printf("                  ");

	move_cursor(137, 45);
	printf("                             ");


	return 0;
}

void RemoveStoryArea()
{
	int story_left = 1;
	int story_right = 125;
	int story_top = 1;
	int story_bottom = 50;

	for (int y = story_top + 1; y < story_bottom; y++)
	{
		for (int x = story_left + 1; x < story_right; x++)
		{
			move_cursor(x, y);
			printf(" ");
		}
	}
}

int RemoveMenuInside()
{
	int menu_left = 135;
	int menu_right = 180;
	int menu_top = 1;
	int menu_bottom = 35;

	for (int y = menu_top + 5; y < menu_bottom; y++)
	{
		for (int x = menu_left + 1; x < menu_right; x++)
		{
			move_cursor(x, y);
			printf(" ");
		}
	}
	move_cursor(146, 40);
	printf("                  ");
	move_cursor(137, 45);
	printf("                                                          ");

}

void Text(int x, int y, const char* text)
{
	move_cursor(x, y);
	printf("%s", text);
	fflush(stdout);
	Sleep(1000);
}


int GetStageChoice_num()
{
	int choice;

	while (1)
	{
		move_cursor(146, 40);
		printf("                  ");
		move_cursor(146, 40);

		if (scanf("%d", &choice) == 1)
		{
			return choice;
		}

		while (getchar() != '\n');

		move_cursor(137, 45);
		printf("선택지 숫자를 입력하세요");
	}
}

void GetStageChoice_str(char top[], size_t topSize,
	char bottom[], size_t bottomSize)
{
	while (1)
	{

		move_cursor(146, 40);
		printf("                  ");
		move_cursor(146, 40);

		int result = scanf_s(
			"%s %s",
			top, (unsigned)topSize,
			bottom, (unsigned)bottomSize
		);

		if (result == 2)
		{
			while (getchar() != '\n');
			return;
		}

		while (getchar() != '\n');
	}
}

/*-----------------------------------------------------------------------------------------------------------*/

int prolog_story_index = 0;

int gameStage_prolog() {

	if (prolog_story_index == 0) {

		Text(5, 3, "프롤로그");

		Text(5, 5, "12 : 59 : 58");
		Text(5, 5, "12 : 59 : 59");
		Text(5, 5, "00 : 00 : 00");
		Text(5, 5, "삐──────────");

		Text(5, 7, "순간 컴퓨터 화면이 번쩍인다.");

		Sleep(3000);

		RemoveStoryArea();
		prolog_story_index = 1;
	}
	if (prolog_story_index == 1) {
		Text(5, 3, "눈을 뜬 당신. ");

		Text(5, 5, "원룸 천장. 널브러진 컵라면, 먼지 쌓인 키보드, ");
		Text(5, 6, "모니터 속 정지된 미연시 게임 화면.");

		Text(5, 8, "그리고 그 위로 보이는 정체 불명의 시스템 창.");

		Text(5, 10, "[히든 조건을 달성하였습니다.]");

		Text(5, 12, "-띠링");

		Text(5, 14, "[모솔로사신지 30년이 되었습니다!]");

		Text(5, 16, "당신은 한참 화면을 바라보다 중얼거린다.");

		Text(5, 18, "“...내가 드디어 미쳤나?”");

		Text(5, 20, "스스로의 정신 상태를 의심하며 중얼거린 순간, 컴퓨터 화면이 지직거리며 노이즈를 일으켰다.");
		Text(5, 21, "이윽고 기존의 게임 화면을 거칠게 밀어내며 새로운 문장들이 떠올랐다.");

		Sleep(3000);

		RemoveStoryArea();
		prolog_story_index = 2;
	}

	if (prolog_story_index == 2) {
		Text(5, 3, "「30년간 연애 경험이 없는 자에게 칭호를 부여합니다.」");

		Text(5, 5, "[칭호를 얻으시겠습니까?]");
		Text(5, 6, "[YES/NO]");

		Text(5, 8, "당신은 흐릿한 시선으로 한참 동안 그 문구를 바라보았다.");
		Text(5, 9, "머릿속이 상황을 따라가지 못해 과부하가 걸릴 지경이었다.");
		Text(5, 10, "30살 생일이 되는 자정에 이런 환각을 보다니.");

		Text(5, 12, "기이한 현실감에 압도당해 손가락이 쉽게 움직이지 않았다.");
		Text(5, 13, "본능적인 경고 신호가 뇌리를 스쳤다.");
		Text(5, 14, "저 버튼을 누르는 순간, 평범했던 일상으로");
		Text(5, 15, "절대 돌이킬 수 없을 것 같다는 강한 예감이 들었다.");

		Text(5, 17, "그러나 망설임도 잠시.");

		Text(5, 19, "[입력이 지연되고 있습니다.]");

		Text(5, 21, "[자동 전직까지 3…]");
		Text(5, 22, "[2…]");
		Text(5, 23, "[1…]");

		RemoveStoryArea();
		prolog_story_index = 3;
	}
	if (prolog_story_index == 3) {
		Text(5, 3, "[일정 시간이 지나 자동으로 전직을 시작합니다.]");

		Text(5, 5, "모니터 속에서 이상한 효과음이 튀어나온다.");

		Text(5, 7, "★  칭호 획득 : 대마법사 ★");
		Text(5, 8, "----띠링.");

		Text(5, 10, "“뭐?.....”");

		Text(5, 12, "황당한 단어에 헛웃음을 터뜨리기도 전,");
		Text(5, 13, "방 안의 전등이 폭발할 듯 격렬하게 깜빡이기 시작했다.");

		Text(5, 15, "쿠르릉거리는 진동과 함께 책상 위에 뒹굴던 빈 페트병들이");
		Text(5, 16, "자석에 이끌리듯 공중으로 둥실 떠올랐다.");

		Text(5, 18, "모니터 표면에서는 아지랑이 같은 보라색 마력이 피어올라");
		Text(5, 19, "당신의 뺨을 스쳤다.");

		Text(5, 21, "서늘하고도 생생한 감각이었다..");

		Text(5, 23, "“잠깐... 이거 진짜야?”");

		Text(5, 25, "--");

		Text(5, 27, "등줄기에 소름이 돋아 자리에서 일어난 그때였다.");

		Text(5, 29, "난데없이 귓가에 서늘한 여성의 목소리가 내꽂혔다.");

		Text(5, 31, "“저기요! 제가 만만해요?!”");

		Text(5, 33, "놀라 고개를 돌리는 순간—");

		Text(5, 35, "-콰---앙!!!-");

		Text(5, 37, "창문이 두꺼운 외벽과 함께 산산조각 나며 흩어졌다.");
		Text(5, 38, "굉음의 정체는 육중한 덤프트럭 한 대였다.");
		Text(5, 39, "아파트 고층일 터인 원룸 안으로 들이닥친 트럭의 헤드라이트가");
		Text(5, 40, "당신의 시야를 하얗게 멀게 했다..");

		Text(5, 42, ".");
		Text(5, 43, ".");
		Text(5, 44, ".");
		Text(5, 45, ".");
		Text(5, 46, "삐──────────");

		Text(5, 48, "귀를 찌르는 이명이 멀어지며, 암흑 속에서 다시 글자들이 점멸했다.");

		Sleep(3000);

		RemoveStoryArea();
		prolog_story_index = 4;
	}
	if (prolog_story_index == 4) {
		Text(5, 3, "시스템 알림.");
		Text(5, 5, "[시스템 활성화 중…]");

		Text(5, 7, "[세계 동기화 완료.]");

		Sleep(3000);

		RemoveStoryArea();
		prolog_story_index = 5;
	}
	if (prolog_story_index == 5) {
		Text(5, 3, "“흡…!”");

		Text(5, 5, "당신은 숨을 몰아쉬며 급히 눈을 떴다.");
		Text(5, 6, "다시 눈에 들어온 것은 익숙하고 낡은 원룸 천장이었다.");
		Text(5, 7, "코끝을 찌르는 컵라면 냄새, 먼지 쌓인 키보드, 그리고 모니터 속 정지된 미연시 화면까지 모든 게 그대로였다.");

		Text(5, 9, "“…어?”");

		Text(5, 11, "당신의 눈동자가 흔들린다.");
		Text(5, 12, "분명 조금 전, 죽었다.");
		Text(5, 13, "그런데...");

		Sleep(3000);

		RemoveStoryArea();
		prolog_story_index = 6;
	}
	if (prolog_story_index == 6) {
		Text(5, 3, "연이은 혼란을 비웃듯, 귓가에 맑은 알림음이 울렸다.");

		Text(5, 5, "-띠링");

		Text(5, 7, "[전직을 성공하였습니다!]");

		Text(5, 8, "[당신은 이제 이 세계의 %@&째 루프 마법사입니다.]");

		Text(5, 9, "당신의 표정이 차갑게 굳어 들어갔다.");

		Text(5, 10, "“…어?”");

		Text(5, 11, "그리고 다시 컴퓨터 화면이 켜진다.");

		Text(5, 12, "[하루가 반복됩니다.]");
		Text(5, 13, "[루프 해제를 위해 히로인들을 공략해주세요.]");

		Text(5, 14, "[주변 히로인 탐색 중…]");

		Text(5, 15, "화면 중앙의 로딩 바가 천천히 차오르더니, 이윽고 거대한 타이틀 로고가 방 안 가득 채웠다.");

		Text(5, 17, "《30살까지 모솔이면 마법사가 된다는 소문이 사실인 것 같습니다》");

		Sleep(3000);

		RemoveStoryArea();
		prolog_story_index = 7;
	}
	if (prolog_story_index == 7) {
		Text(5, 3, "프롤로그 종료.");

		Text(5, 5, "5초 뒤 게임이 시작됩니다.");

		Text(5, 8, "4...");
		Text(5, 9, "3...");
		Text(5, 10, "2...");
		Text(5, 11, "1...");

		gameStage = 1; //스테이지 1로 넘어감

		RemoveStoryArea();
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/


int Stage1_story_index = 0;

int gameStage_1() {
	if (Stage1_story_index == 0) {
		RemoveStoryArea();
		RemoveMenuInside();

		Text(5, 3, "띠링.");

		Text(5, 5, "[첫 번째 퀘스트가 도착했습니다.]");

		Text(5, 7, "퀘스트 : 카페로 이동하시오.");

		Text(5, 9, "[목적지에 도착하면 다음 퀘스트가 개방됩니다.]");

		Text(5, 11, "...");

		Text(5, 13, "당신은 카페로 이동한다.");

		Sleep(3000);

		RemoveStoryArea();

		Stage1_story_index = 1;
	}

	if (Stage1_story_index == 1) {

		Text(5, 3, "1일차.");

		Text(5, 5, "주인공은 시스템의 지시에 따라 집 근처 카페로 향한다.");

		Text(5, 7, "창가 자리에 앉은 채 주변을 둘러보던 순간.");

		Text(5, 9, "-띠링");

		Text(5, 11, "[히로인 탐색 중...]");

		Text(5, 12, "[공략 후보 세 명을 발견했습니다.]");
		
		Sleep(3000);

		RemoveStoryArea();

		Stage1_story_index = 2;		
	}

	if (Stage1_story_index == 2) {
		move_cursor(5, 3);
		printf("      \n");
		printf("      \n");
		printf("      \n");
		printf("                               어딘가 위험해 보이는 그녀   \n");
		printf("                                           ,..                                                                         \n");
		printf("                                        .==*+==:,.                                                                         \n");
		printf("                                       ;#$$!$####$-                                                                         \n");
		printf("                                      =##$;'=$#@@##:                                                                           \n");
		printf("                                      ~#@=   ;-=;##-                                                                         \n");
		printf("                                      !@@-,    . ##!                 단발 머리 그녀                                                    \n");
		printf("                                      @#@!,    -!##$-                                                                    \n");
		printf("                                      $*@# -   ;@@@=,                   ,:;;-,                                              \n");
		printf("                                      ,@$@@*=-~####!                   ~=*==*!-.                                            \n");
		printf("                                     ,~=@@@@@..;@$#~                  -$$=*:::!:                    청순한 그녀                \n");
		printf("                                     .!#@@@@@~,,-#$::                 ;$!!    =;.                                        \n");
		printf("                                      -=@@@#--,.-#@#$                 :#!. - :$*,                    .;=****~               \n");
		printf("                                     .=$##*,!     *$=-                 ,*#.,~*;.                   ~$$=$$$$==;,             \n");
		printf("                                      .=@=.~,.    !$=.                   ...~-                    ,=$$$*##$$=;~=            \n");
		printf("                                     *@#####., .. -$#@=-             ,,,,-!!-                   .;$$##$$$=!;$=!!~           \n");
		printf("                                     @@@#####-,.. -#@$!.            . .!!:==$$$...              ~$#$###=$!,:=!=**-          \n");
		printf("                                    $@@@@####=,.-..;@#=~            ,..:;-$$$#$...              -#$$$$$=;;.!**$=*,          \n");
		printf("                        ,--,       .-@@@@@@@@-,.-.,.$@#~:           ,..-~,###$=:*~              !$#$ ;!=!:,:;!=$*           \n");
		printf("                        ,---       ;.#$@@@@@#,,#..,;#@#:*           -,. ;!@#$@$$#,.            .~$$# :,-:-..=*=$*           \n");
		printf("                        .,-;,,,    =  @@@##@~~,#.  !#@#@,         !~.,..-#######;.             -=*$#@$      ~;$=!.          \n");
		printf("                        =!-::,.  . ~  @@@@#$-~-#-,-~#@#=~        --~--,.,=@##$.;, .,           -!=$###      .!$#$~          \n");
		printf("                        !:-:::-. ,  .**#@##;,;~#. .;###*;        $*:~--,,-*$=;-,.  ---.       .;==$$$#=,  - !#$$=-.         \n");
		printf("                        #=:~!!~  -..-~;#@##=--~#, .!@@@:..       :!, ~-,~~!!!!~,,,.!!*:~      -,#$$#$$~-. ,=@#!$*:-         \n");
		printf("                        #;~-!:;;;.:-~:;#@@@@@~#,,..*#@#~-*   *:::;,,-...~::;!;,;,,-===#!       *@##$=;-,,*@#@##$;:-         \n");
		printf("                        :=;-####=,:::;:$##$$--,.,,.!=@=-,~  :!;;;!!--,-~!**!=;*--,====#-    :$$$=$$$$*-,,!@$#$==.~.         \n");
		printf("                       ::=:.$#=!;. :;!;$=;~-......,=@@*  ~   :::!*!!!!*===#==::,, -;*,#    .!;;;!*===*~.-*@#$$=$!-          \n");
		printf("                       ::=$=##*~~- ..-.,,.-,. . .,;##$!.        .,,~*::::~~-~-:..  ~*,$    *,.- ~*~!:~, ,*$##$==;.          \n");
		printf("                     ,:#$#!##=;::.      ~~-- ,,-:!@:*:!.          ,*-,,,.    .. . :$,!    !.    :..:-~...~=##$$$!.         \n");
		printf(" ;;_+==*,;$==$=$=;;#@@$#$#=$$==$=$=;;#@@$-~,..::~:=#.             ,*-,.      ,...,~$:-,   :.  ,  ---:.  .!*###$*~-         \n");
		printf(" ::::::::;;;;*!*~--~::**!*~--~::**====@@#!!;-~~~~,;!*             ,*-,  ...  ,.,.~:==-,   ;.    . .,-.  ,::=##$=:.         \n");
		printf(" :::::::::::::::::::::::.,:;;;;===***!*#@@###!~~~-,:-,            .,*-,...-!==*...;$$#. -!::..  .  .,.    ,-;##!:.          \n");
		printf(" :::::::::::::::::::::::;:;:#$$$==!!!*=@@###@~,,--,.              .,*:,.;=$#$==~--###,!*$$#=,.   ,  ..     ::$##:           \n");
		printf(" :::::::::::::::::::::::;$$===*;==*!!!!#@@##@--.,-,,              .,**..~$*$*!!.,*$#$;*;,,,!. . .-  .,,,-,.-*$$$$=,         \n");
		printf(" :::::::::::::::::::::::=!!;~:;;*=*!!*!#@@##@,,,~,.,             ,.~=:.. =.=,     :=#$,*===*, , ,.-  .    ,,~*$$=!.         \n");
		printf(" ::::::::::::::::::::::::::~~:;;*=*!;*;#@@##@,.,;,.             ,. -=-.,.=,;       *$$ $===*-.. ..,      . ~-!$$=!,         \n");
		printf(" :::::::::::::::::::::::::::~:;;===*!=*#@@##@..,;,.             ..~-$,,;~=!-       ~#$ $====!, ..-,~        :!$$$~.         \n");
		printf(" :::::::::::::::::::::::~:::~:;:*==*##@@@###@,.,!..            ... -$,,;-=!.       -## @#$$*-,. .:,.   ......,;=      .,,.  \n");
		printf(" ::::::::::::::::~~:::::~~~:~:;;===*@@@@@@@@@!.,: . .         ,-,. -;.,*,=         ,=$ =#$$$!-,..,,.,,,,,,,,-~:,.,---~:!!;~-\n");
		printf(" :::::::::::::::::::::::~::::;;;===#@@@@@@@@@$.,-.. ~        ,-,-. -~.-*.=          !#,~#$$$;~,....,-,-,----~;~::;;;;;;;;;;;\n");
		printf(" ::::::::::::::::::::::~~~:::;;!===#@@@@@@@#@$.-~., -       --.,,: --..! =          :##,###$;~,..:,,--~---~~:;;;;;;;;;;;;;;;\n");
		printf(" :::::::::::::::::::::::~:~::;!;===#@@@@@@@##$.~~..       .--.,,,. ,,..; =          ;#=-@###*~-...*.,-~-~~~~;:!;;;;;;;;;;;;;\n");
		printf(" ::::::::::::::::::::~~~~~~:~:;;===#@@@@@@@@@$.~~.        ,,,,,,---~-,.; =          ;=#:$###*~--~,=.,-~~~~~:!-:;;;;;;;;:;;;;\n");
		printf(" ::::::::::::::::::::::~~~~:::;!===##@@=@@@@@#,~~...       ~!:   ;~-..*=-=          ;~#*!$#$;~-,:,~. .--~::!*:;;;;;!!!~-:;;;\n");

		AddGameScreen();

		move_cursor(5, 3);
		printf("선택지는 항상 키보드로 입력하세요.");

		move_cursor(139, 8);
		printf("당신의 진짜 운명의 상대를 찾으세요");

		move_cursor(139, 12);
		printf("1. 어딘가 위험해보이는 그녀");

		move_cursor(139, 17);
		printf("2. 단발 머리 그녀");

		move_cursor(139, 22);
		printf("3. 청순한 그녀");

		int choice;
		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 3)
				break;

			move_cursor(137, 45);
			printf("1~3 사이를 입력하세요");
		}


		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "평범한 후드티.");
			Text(5, 5, "평범한 청바지.");
			Text(5, 7, "노트북을 펴고 혼자 커피를 마시는 여성.");
			Text(5, 9, "특별할 것 없어 보인다.");

			Text(5, 11, "-띠링");

			Text(5, 13, "[적합한 히로인을 발견했습니다.]");
			Text(5, 15, "[이름 : ???]");

			Text(5, 17, "주인공은 긴장한 채 다가간다.");
			Text(5, 19, "\"저... 여기 자리 비었나요?\"");

			Text(5, 21, "여성이 고개를 들더니 눈을 깜빡인다.");
			Text(5, 23, "\"...어?\"");

			Text(5, 25, "잠시 침묵.");
			Text(5, 27, "그리고.");

			Text(5, 29, "\"혹시... 우리 같은 동네 사는 분 아니에요?\"");

			Text(5, 31, "주인공도 기억이 난다.");
			Text(5, 33, "동네에서 몇 번 마주쳤던 이웃이었다.");

			Text(5, 35, "[첫 접촉 성공!]");
			Text(5, 37, "[히로인 데이터가 등록되었습니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 2;
			Stage1_story_index = 0;
		}
		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "검은 가죽 재킷.");

			Text(5, 5, "짙은 화장.");

			Text(5, 7, "묘하게 위압적인 분위기.");

			Text(5, 9, "주인공은 떨리는 목소리로 말을 건넸다.");

			Text(5, 11, "\"저... 혹시 번호...\"");

			Text(5, 13, "여성이 천천히 고개를 든다.");

			Text(5, 15, "\"...번호?\"");
			Text(5, 16, "여성은 피식 웃었다.");
			Text(5, 17, "\"용감하네.\"");

			Text(5, 19, "주인공은 속으로 안도의 한숨을 내쉬었다.");
			Text(5, 20, "생각보다 반응이 나쁘지 않은데?");

			Text(5, 22, "하지만 다음 순간.");
			Text(5, 23, "여성이 고개를 돌리며 말했다.");

			Text(5, 25, "\"자기야.\"");

			Text(5, 27, "순간 카페 안 공기가 싸늘해진다.");

			Text(5, 28, "뒤쪽 테이블.");
			Text(5, 29, "팔짱을 낀 건장한 남성이 자리에서 일어났다.");

			Text(5, 31, "\"...?\"");

			Text(5, 32, "남성의 시선이 정확히 자신을 향하고 있었다.");

			Text(5, 34, "\"...아.\"");

			Text(5, 36, "-콰직");

			Text(5, 38, "[사망하였습니다.]");

			Text(5, 39, "[사망 원인 : 눈치 없음]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
			Stage1_story_index = 0;
		}
		if (choice == 3) {
			RemoveStoryArea();

			Text(5, 3, "긴 생머리.");

			Text(5, 5, "순한 인상.");

			Text(5, 7, "완벽한 미소.");

			Text(5, 9, "주인공은 용기를 내 말을 건다.");

			Text(5, 11, "\"저기... 괜찮으시면...\"");

			Text(5, 13, "\"아, 안녕하세요.\"");

			Text(5, 15, "생각보다 반응이 좋다.");

			Text(5, 17, "주인공이 안도한 순간.");

			Text(5, 19, "여성의 목소리가 귓가에 들린다.");

			Text(5, 21, "\"...근데 저 요새 일이 잘 안 풀리지 않나요?\"");

			Text(5, 23, "가방에서 두꺼운 교재가 나온다.");

			Text(5, 25, "\"잠시만 시간 괜찮으세요?\"");

			Text(5, 27, "\"네?\"");

			Text(5, 29, "세 시간 후.");

			Text(5, 31, "주인공은 정체불명의 수련원 버스에 탑승 중이었다.");

			Text(5, 33, "[정신력이 0이 되었습니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
			Stage1_story_index = 0;
		}

	}


	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage2_story_index = 0;

int gameStage_2() {

	if (Stage2_story_index == 0) {
		Text(5, 3, "-띠링");

		Text(5, 5, "[당신의 운명의 상대가 맞습니다.]");

		Text(5, 7, "[접근하시겠습니까?]");

		move_cursor(145, 8);
		printf("행동을 선택해주세요");

		move_cursor(139, 12);
		printf("1. 말을 건다");

		move_cursor(139, 17);
		printf("2. 쪽지를 건넨다");

		move_cursor(139, 22);
		printf("3. 지나간다");

		int choice;
		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 3)
				break;

			move_cursor(137, 45);
			printf("1~3 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "\"저기…\"");

			Text(5, 5, "여자가 한 번 보고 바로 표정 굳힌다.");
			Text(5, 6, "\"…아니요.\"");

			Text(5, 8, "더 들을 필요도 없다는 얼굴.");
			Text(5, 9, "고개 돌리고 끝.");

			Text(5, 11, "-띠링");

			Text(5, 13, "[거절당했습니다.]");
			Text(5, 14, "[잘못된 선택입니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "쪽지를 본다.");

			Text(5, 5, "\"…저기요.\"");

			Text(5, 7, "구겨서 테이블에 툭.");

			Text(5, 9, "\"제가 만만해요?!\"");

			Text(5, 11, "\"좀 역겹네.\"");

			Text(5, 13, "그리고 바로 시선 차단.");

			Text(5, 15, "-띠링");

			Text(5, 17, "[정신 데미지]");
			Text(5, 18, "[이미지 붕괴]");
			Text(5, 19, "[잘못된 선택입니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 3;
		}
		Stage2_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage3_story_index = 0;

int gameStage_3() {


	if (Stage3_story_index == 0) {
		RemoveStoryArea();
		RemoveMenuInside();

		Text(5, 3, "주인공은 잠시 그녀를 바라보다가 고개를 저었다.");

		Text(5, 5, "\"아무리 생각해도 초면에 말 거는 건 무리야...\"");

		Text(5, 7, "그는 그대로 그녀의 옆을 지나쳐 걸어갔다.");

		Text(5, 9, "그 순간.");

		Text(5, 11, "\"앗!\"");

		Text(5, 13, "여성이 급히 자리에서 일어나다 주인공과 부딪혔다.");

		Text(5, 15, "철퍽.");

		Text(5, 17, "손에 들고 있던 아이스커피가 주인공의 옷에 쏟아졌다.");

		Text(5, 19, "\"죄, 죄송해요!\"");

		Text(5, 21, "당황한 여성이 연신 고개를 숙였다.");

		move_cursor(145, 8);
		printf("행동을 선택해주세요");

		move_cursor(139, 12);
		printf("1. 직접 닦아주세요");

		move_cursor(139, 17);
		printf("2. 돈 있으세요?");

		move_cursor(139, 22);
		printf("3. 당황하고 있다");

		int choice;
		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 3)
				break;

			move_cursor(137, 45);
			printf("1~3 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "여자가 당황하며 연신 사과한다.");

			Text(5, 5, "\"죄송해요! 제가 진짜…!\"");

			Text(5, 7, "주인공이 티슈를 꺼내며 말한다.");

			Text(5, 9, "\"아니요, 괜찮아요. 여기… 직접 닦아주세요.\"");

			Text(5, 11, "순간 여자 표정이 멈춘다.");

			Text(5, 13, "\"...제가요?\"");

			Text(5, 15, "\"네.\"");

			Text(5, 17, "\"…….\"");

			Text(5, 19, "아주 짧은 침묵.");

			Text(5, 21, "그리고 살짝 뒤로 물러난다.");

			Text(5, 23, "\"아니 이건 좀… 이상하잖아요.\"");

			Text(5, 25, "\"아니 그냥 옷이 젖어서…\"");

			Text(5, 27, "\"제가 왜요?\"");

			Text(5, 29, "표정 완전히 굳음.");

			Text(5, 31, "\"죄송한데 세탁비만 드리고 갈게요.\"");

			Text(5, 33, "-띠링");

			Text(5, 35, "[호의 → 수상한 요구로 판정]");
			Text(5, 36, "[관계 즉시 종료]");
			Text(5, 37, "[잘못된 선택입니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "여자가 계속 사과한다.");

			Text(5, 5, "\"세탁비 드릴게요! 정말 죄송해요!\"");

			Text(5, 7, "주인공이 말한다.");

			Text(5, 9, "\"돈 있으세요?\"");

			Text(5, 11, "여자: \"네?\"");

			Text(5, 13, "\"돈으로 주시면…\"");

			Text(5, 15, "여자가 얼어붙는다.");

			Text(5, 17, "\"...아.\"");

			Text(5, 19, "잠깐 정적.");

			Text(5, 21, "지갑을 꺼내며 말한다.");

			Text(5, 23, "\"얼마요?\"");

			Text(5, 25, "주인공: \"아니 그게 아니라 연락처를…\"");

			Text(5, 27, "여자: \"아, ….\"");

			Text(5, 29, "그리고 바로 지갑 닫는다.");

			Text(5, 31, "\"그냥, 세탁비 드릴게요.\"");

			Text(5, 33, "고개 돌림.");

			Text(5, 35, "대화 종료.");

			Text(5, 37, "-띠링");

			Text(5, 39, "[의도 전달 실패]");
			Text(5, 40, "[만남 이벤트 종료]");
			Text(5, 41, "[잘못된 선택입니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 3) {
			RemoveStoryArea();

			Text(5, 3, "주인공은 갑작스러운 상황에 아무 말도 하지 못했다.");

			Text(5, 5, "\"...어?\"");

			Text(5, 7, "그저 멍하니 젖은 옷을 바라볼 뿐이었다.");

			Text(5, 9, "오히려 여성이 더 안절부절못했다.");

			Text(5, 11, "\"세탁비라도 드릴게요! 정말 죄송해요!\"");

			Text(5, 13, "주인공은 손사래를 쳤지만, 그녀는 끝까지 미안한 표정을 지었다.");

			Text(5, 15, "잠시 후.");

			Text(5, 17, "\"그... 혹시 연락처 알려주실 수 있나요? 배상은 꼭 해드리고 싶어서...\"");

			Sleep(3000);


			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "얼떨결에 서로 연락처를 교환하게 된다.");

			Text(5, 5, "번호를 저장한 그녀는 안도의 한숨을 내쉰다.");

			Text(5, 7, "\"다시 한번 죄송해요.\"");

			Text(5, 9, "주인공은 아직도 상황을 이해하지 못한 채 고개만 끄덕였다.");

			Text(5, 11, "\"아, 네...\"");

			Text(5, 13, "잠시 어색한 침묵.");

			Text(5, 15, "그리고 그녀가 먼저 미소 지었다.");

			Text(5, 17, "\"그럼 연락드릴게요.\"");

			Text(5, 19, "그녀는 가볍게 인사하고 카페를 떠난다.");

			Text(5, 21, "-띠링");

			Text(5, 23, "[히로인과의 첫 만남에 성공했습니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 4;
			

		}
		Stage3_story_index = 0;

		Sleep(3000);

	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage4_story_index = 0;

int gameStage_4() {

	if (Stage4_story_index == 0) {
		Text(5, 3, "집으로 돌아온 주인공.");

		Text(5, 5, "침대에 누워 시간을 보낸다.");

		Text(5, 7, "-띠링");

		Text(5, 9, "휴대폰이 울린다.");

		Text(5, 11, "안녕하세요. 아까 카페에서 커피 쏟은 ‘김민지’입니다.");
		Text(5, 12, "어떻게 배상해드릴까요…?");

		Text(5, 14, "\"…아 진짜 오네?\"");

		Text(5, 16, "잠깐 고민 후, 선택지가 떠오른다.");

		move_cursor(147, 8);
		printf("대답을 선택하세요");

		move_cursor(139, 12);
		printf("1. 돈");

		move_cursor(139, 17);
		printf("2. 괜찮아요");

		move_cursor(139, 22);
		printf("3. 씹는다");

		int choice;
		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 3)
				break;

			move_cursor(137, 45);
			printf("1~3 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "\"돈으로 주세요.\"");

			Text(5, 5, "아… 네. 알겠습니다.");

			Text(5, 7, "잠시 후 입금 알림.");

			Text(5, 9, "-띠링");

			Text(5, 11, "[배상 완료]");

			Text(5, 13, "화면은 조용해진다.");

			Text(5, 15, "그날 이후 연락 없음.");

			Text(5, 17, "-띠링");

			Text(5, 19, "[관계 종료]");
			Text(5, 20, "[잘못된 선택입니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "주인공은 잠시 고민하다가 답장을 보냈다.");

			Text(5, 5, "\"아, 배상은 정말 안 해주셔도 괜찮습니다.\"");

			Text(5, 7, "곧바로 답장이 돌아온다.");
			Text(5, 8, "설렘이었다.");

			Text(5, 10, "아니에요. 옷도 많이 젖으셨는데");
			Text(5, 11, "제가 너무 죄송해서요...ㅠㅠ");

			Text(5, 13, "주인공은 피식 웃었다.");

			Text(5, 15, "\"세탁비 얼마 안 나와요.");
			Text(5, 16, "진짜로 괜찮으니까 신경 쓰지 마세요!\"");

			Text(5, 18, "하지만 상대는 쉽게 물러서지 않았다.");

			Text(5, 20, "그래도 제 마음이 너무 불편해서요...");
			Text(5, 21, "기어코 안 받으시면 제가 밤에 잠을 못 잘 것 같아요.ㅠㅠ");

			Text(5, 23, "잠시 대화가 이어지던 중…");

			Text(5, 25, "상대가 조심스럽게 말을 꺼냈다.");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "그럼… 차라리 제가 내일 간단하게 밥이라도 대접해드려도 될까요?");
			Text(5, 4, "돈으로 드리는 것보다 그게 마음이 편할 것 같아서요..!");

			Text(5, 6, "주인공은 순간 머릿속이 새하얘졌다.");
			Text(5, 7, "30년 인생, 생각지도 못한 전개였다.");

			Text(5, 9, "심장이 미친 듯이 뛰기 시작했다.");
			Text(5, 10, "타이핑하는 손가락이 꼬여 오타를 연발하다가,");
			Text(5, 11, "겨우 정신을 부여잡고 답장을 보냈다.");

			Text(5, 13, "\"아, 넵! 내일 마침 일정이 비어있어서 괜찮습니다.\"");

			Text(5, 15, "답장을 보내기가 무섭게 상대의 메시지가 도착했다.");
			Text(5, 16, "와, 다행이다!");

			Text(5, 18, "그럼 내일 OO역 앞에서 12시에 만나요 :)");

			Text(5, 20, "주인공은 자신도 모르게 시뻘게진 얼굴을 이불에 파묻었다.");
			Text(5, 21, "미연시 게임 화면을 볼 때와는 비교도 안 되는 생생한 현실적 설렘이었다.");

			Text(5, 23, "-띠링");

			Text(5, 25, "[돌발 퀘스트 : '김민지'와의 첫 데이트가 생성되었습니다.]");
			Text(5, 27, "[목표 : 무사히 식사를 마치고 호감도 쌓기]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "[DAY 1 종료]");

			Text(5, 5, "-띠링");

			Text(5, 7, "[ ★ 세이브 포인트가 생성되었습니다 ★ ]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 5;
		}
		if (choice == 3) {
			RemoveStoryArea();

			Text(5, 3, "메시지를 본 주인공.");

			Text(5, 5, "\"…귀찮은데.\"");

			Text(5, 7, "읽음 처리만 남기고 아무 답도 하지 않는다.");

			Text(5, 9, "잠시 후—");

			Text(5, 12, "…바쁘신가요?");

			Text(5, 14, "음..");

			Text(5, 16, "그리고 마지막 메시지.");

			Text(5, 18, "많이 바쁘신가 봐요...");
			Text(5, 19, "나중에라도 시간 괜찮으실 때 꼭 연락 주세요!");

			Text(5, 21, "-띠링");

			Text(5, 23, "[연락 이벤트 소멸]");
			Text(5, 24, "[잘못된 선택입니다.]");

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		Stage4_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int isValidTop(char* top)
{
	return (strcmp(top, "후드티") == 0 ||
		strcmp(top, "나시") == 0 ||
		strcmp(top, "셔츠") == 0);
}

int isValidBottom(char* bottom)
{
	return (strcmp(bottom, "정장바지") == 0 ||
		strcmp(bottom, "반바지") == 0 ||
		strcmp(bottom, "츄리닝바지") == 0);
}

int Stage5_story_index = 0;

int gameStage_5() {
	char top[30];
	char bottom[30];

	if (Stage5_story_index == 0) {
		Text(5, 3, "2일차");
		Text(5, 4, "좋은 아침입니다.");
		Text(5, 5, "오늘은 김민지와의 만남이 약속된 날입니다.");

		Text(5, 7, "당신은 샤워를 마치고 옷장 앞에 섰습니다.");

		Text(5, 9, "옷장을 열면 옷들이 있습니다.");

		Text(5, 11, "상의");

		Text(5, 13, "후드티, 나시, 셔츠");

		Text(5, 15, "하의");

		Text(5, 17, "정장바지, 반바지, 츄리닝바지");

		move_cursor(148, 7);
		printf("옷을 골라 입으세요.");

		move_cursor(151, 10);
		printf("선택지 입력은");

		move_cursor(152, 12);
		printf("> 상의 하의");

		move_cursor(149, 14);
		printf("순으로 입력하세요.");

		while (1)
		{
			GetStageChoice_str(top, sizeof(top), bottom, sizeof(bottom));


			if (!isValidTop(top) && !isValidBottom(bottom))
			{
				move_cursor(5, 42);
				printf("존재하지 않는 옷입니다. 다시 선택하세요.");
				continue;
			}
			else if (strcmp(top, "셔츠") == 0 &&
				strcmp(bottom, "정장바지") == 0)
			{
				move_cursor(5, 42);
				printf("정답입니다!");
				break;
			}
			else {
				move_cursor(5, 42);
				printf("옷 선택 실패... 게임 오버");
				break;
			}

		}
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Ending_bad() {

	Text(5, 3, "베드엔딩");
	Text(5, 5, "[루프를 시작합니다.]");
	Text(5, 7, "3...");
	Text(5, 8, "2...");
	Text(5, 9, "1...");

	Sleep(1000);

	gameStage = 1;

	return 0;
}

int Ending_bad_CheckPoint_1() {

	Text(5, 3, "베드엔딩");
	Text(5, 5, "[루프를 시작합니다.]");
	Text(5, 6, "[체크포인트로 이동합니다.]");
	Text(5, 8, "3...");
	Text(5, 9, "2...");
	Text(5, 10, "1...");

	Sleep(1000);

	gameStage = 5;

	return 0;
}