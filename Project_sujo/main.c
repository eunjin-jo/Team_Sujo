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

int RenderHelp();
int RenderCredits();

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
		Ending_bad_CheckPoint_2();
		break;
	case -2:
		Ending_bad_CheckPoint_1();
		break;
	case -1:
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
	case 6:
		gameStage_6();
		break;
	case 7:
		gameStage_7();
		break;
	case 8:
		gameStage_8();
		break;
	case 9:
		gameStage_9();
		break;
	case 10:
		gameStage_10();
		break;
	case 11:
		gameStage_11();
		break;
	case 12:
		gameStage_12();
		break;
	case 13:
		gameStage_13();
		break;
	case 14:
		gameStage_14();
		break;
	case 15:
		gameStage_15();
		break;
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


int RenderHelp(){
	move_cursor(1, 1);
	printf("                                                          \n");
	printf("                                                                                           ================================\n");
	printf("\n");
	printf("                                                                                                  게임 플레이 가이드\n");
	printf("\n");
	printf("                                                                                           ================================\n");
	printf("\n");
	printf("\n");
	printf("\033[1m                                                                            《30살까지 모솔이면 마법사가 된다는 소문이 사실인 것 같습니다》\033[0m\n");
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
	printf("================================\n");
	printf("\n");
	printf("  T E A M  수조  \n");
	printf("\n");
	printf("================================\n");
	printf("\n");
	printf("\n");
	printf("저희는 어느 날 갑자기 '루프 마법사'가 되어 무한히 하루를 반복하게 된\n");
	printf("주인공의 처절한 탈출기를 그린 Team_Sujo(수조팀)입니다.\n");
	printf("\n");
	printf("지독한 모솔 저주를 깨뜨리고 내일(Next Day)을 맞이하려는\n");
	printf("주인공의 여정을 게임으로 구현하기 위해 각자의 자리에서 고민했습니다.\n");
	printf("\n");
	printf("\n");
	printf(" 조은진(팀장) : \n");
	printf(" 윤수아 : \n");
	printf(" 이세빈 : \n");
	printf(" 송한이 : \n");
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

			gameStage = 1;
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

			gameStage = -1;
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

			gameStage = -1;
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

			gameStage = -1;
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

			gameStage = -1;
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

			gameStage = -1;
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

			gameStage = -1;
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

			gameStage = -1;
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

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -1;
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
		Text(5, 5, "오늘은 김민지와의 만남이 약속된 날이다.");

		Text(5, 7, "당신은 샤워를 마치고 옷장 앞에 섰다.");

		Text(5, 9, "옷장을 열면 옷들이 다양하게 있다.");

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
				Text(5, 42, "존재하지 않는 옷입니다. 다시 고르세요.");

				Sleep(2000);

				Text(5, 42, "                                               ");

				continue;
			}
			else if (strcmp(top, "셔츠") == 0 &&
				strcmp(bottom, "정장바지") == 0)
			{
				Text(5, 42, "정답입니다.");
				Text(5, 43, "어서 밖으로 나갑니다.");

				Sleep(3000);

				RemoveStoryArea();
				RemoveMenuInside();

				gameStage = 6;

				break;
			}
			else {
				Text(5, 42, "옷 선택 실패...");

				Text(5, 43, "[만남 이벤트 소멸]");
				Text(5, 44, "[잘못된 선택입니다.]");

				Sleep(3000);

				RemoveStoryArea();
				RemoveMenuInside();

				gameStage = -2;
				break;
			}

			Stage5_story_index = 0;
		}
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage6_story_index = 0;

int gameStage_6() {

	if (Stage6_story_index == 0) {
		Text(5, 3, "당신은 밖으로 나왔다.");

		Text(5, 5, "약속 장소로 향하기 위한 수단을 골라라.");

		move_cursor(146, 8);
		printf("이동 수단을 고르세요.");

		move_cursor(139, 12);
		printf("1. 걸어가기");

		move_cursor(139, 17);
		printf("2. 자전거");

		move_cursor(139, 22);
		printf("3. 버스");

		move_cursor(139, 27);
		printf("4. 택시");

		int choice;

		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 4)
				break;

			move_cursor(137, 45);
			printf("1~4 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "\"날씨도 좋은데 걸어갈까?\"");

			Text(5, 5, "30분 후, 주인공은 땀 범벅이 된 채 역 앞에 도착했다.");
			Text(5, 6, "겨드랑이가 흥건하게 젖은 채로 그녀를 마주할 순 없다.");

			Text(5, 8, "-띠링");

			Text(5, 10, "[불쾌지수 상승]");
			Text(5, 11, "[루프를 시작합니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "따릉이를 타고 도로를 질주한다.");
			Text(5, 4, "속도는 빨랐으나 역 앞에 도착했을 때 주인공의 머리는 흡사 폭탄을 맞은 듯 사방으로 뻗쳐 있었다.");

			Text(5, 6, "-띠링");

			Text(5, 8, "[헤어스타일 파괴]");
			Text(5, 9, "[루프를 시작합니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "가장 쾌적하고 안전한 대중교통.");

			Text(5, 5, "에어컨 바람을 쐬며 뽀송뽀송한 상태를 유지한 채 약속 시간 10분 전에 정확히 OO역 앞에 도착했다.");

			Text(5, 7, "멀리서 어제 보았던 민지가 손을 흔들며 걸어온다.");

			Text(5, 9, "\"안녕하세요! 일찍 오셨네요?\"");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 7;
		}
		if (choice == 4) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "\"기사님, 저 늦지 않게 최대한 빠르게 가주세요\"");

			Text(5, 5, "기사는 빠르게 달리다가 교통사고가 난다.");

			Text(5, 7, "[교통사고로 사망]");
			Text(5, 8, "[루프를 시작합니다.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		Stage6_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage7_story_index = 0;

int gameStage_7() {

	if (Stage7_story_index == 0) {
		Text(5, 3, "당신은 민지가 미리 알아봐 둔 유명 맛집 앞으로 향한다.");

		Text(5, 5, "하지만 예상치 못한 난관에 부딪혔다.");
		Text(5, 6, "주말 점심이라 그런지 가게 앞은 인산인해였고,");
		Text(5, 7, "대기판을 보니 웨이팅이 무려 1시간이다.");

		Text(5, 9, "민지가 안절부절못하며 말한다.");

		Text(5, 11, "\"엇... 여기 맛있다고 해서 왔는데, 웨이팅이 너무 기네요... 어쩌죠?\"");

		move_cursor(146, 8);
		printf("행동을 선택하세요.");

		move_cursor(139, 12);
		printf("1. 한 시간 동안 기다린다");

		move_cursor(139, 17);
		printf("2. 근처 분식집이나 들어간다");

		move_cursor(139, 22);
		printf("3. 근처 양식집으로 안내한다");

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

			Text(5, 3, "\"괜찮아요. 맛집이라는데 한 시간 정도야 기다리죠!\"");

			Text(5, 5, "떵떵거렸으나, 30분이 지나자 두 사람 사이에 급격한 침묵이 흐른다.");
			Text(5, 6, "할 말은 고갈되었고 다리는 아파 온다.");

			Text(5, 8, "-띠링");

			Text(5, 10, "[지루함 한도 초과]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "\"저기 분식집 맛있어보이는데 가볼까요?\"");

			Text(5, 5, "좁은 가게 안,");

			Text(5, 7, "이미 초등학생들이 테이블을 점령하고 있어 산만한 분위기,");

			Text(5, 9, "너무 초라한 식사.");

			Text(5, 11, "그런 분위기에 대화에 집중하지 못하고 배도 못 채우고…");
			Text(5, 12, "데이트의 분위기를 느끼지 못한다.");

			Text(5, 14, "[불편함만 남은 식사]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "주인공은 빠르게 스마트폰을 켜서 근처를 스캔했다.");

			Text(5, 5, "\"아, 민지 씨. 이 근처에 분위기 깔끔하고 평점 좋은 양식집이 있는데, 그리로 갈까요?\"");

			Text(5, 7, "민지의 눈이 반짝였다.");

			Text(5, 9, "\"앗, 정말요? 좋아요! 다행이다...\"");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 8;
		}

		Stage7_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage8_story_index = 0;

int gameStage_8() {

	if (Stage8_story_index == 0) {
		Text(5, 3, "깔끔한 인테리어의 양식집에 자리를 잡은 두 사람.");

		Text(5, 5, "메뉴판을 보며 민지가 고민에 빠졌다.");

		Text(5, 7, "\"다 맛있어 보여서 뭘 골라야 할지 모르겠어요.\"");

		Text(5, 9, "당신이 자신 있게 나선다.");

		Text(5, 11, "\"제가 골라드릴게요.\"");

		move_cursor(144, 8);
		printf("민지의 메뉴를 골라주세요.");

		move_cursor(139, 12);
		printf("1. 파스타");

		move_cursor(139, 17);
		printf("2. 샐러드");

		move_cursor(139, 22);
		printf("3. 피자");

		move_cursor(139, 27);
		printf("4. 스테이크");

		int choice;

		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 4)
				break;

			move_cursor(137, 45);
			printf("1~4 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "맛있어보이는 해물파스타를 시켰다.");

			Text(5, 5, "포크를 집어 면을 덜어주는 찰나,");
			Text(5, 6, "음식에 이상한게 있다.");

			Text(5, 8, "\"이게 뭐야.. 달팽이...?\"");

			Text(5, 10, "-띠링");

			Text(5, 12, "[위생 문제로 망쳐버린 식사]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "\"우리 가볍게 입가심할 수 있는 샐러드 하나랑 메인 메뉴 몇 개 시킬까요?\"");

			Text(5, 5, "첫 만남의 어색함과 긴장을 풀어주기에 가장 부담 없는 선택이다.");
			Text(5, 6, "민지도 활짝 웃으며 고개를 끄덕였다.");

			Text(5, 8, "\"좋아요! 딱 좋네요.\"");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 9;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "양이 많고 맛있어 보이는 피자 한 판이 나왔다.");

			Text(5, 5, "그런데 민지는 어째서인지 제대로 먹지 못한다.");

			Text(5, 7, "\"왜 그러시죠?\"");

			Text(5, 9, "\"그게 제가 다이어트 중이라서요..\"");

			Text(5, 11, "-띠링");

			Text(5, 13, "[부담스러운 메뉴 선정]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 4) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "거하게 칼질을 하려니 민지의 표정이 묘하게 차가워졌다.");

			Text(5, 5, "그녀는 칼질하는 그의 손을,");
			Text(5, 6, "그리고 핏물이 뚝뚝 떨어지는 스테이크를");
			Text(5, 7, "혐오스러운 표정으로 바라보았다.");

			Text(5, 9, "-띠링");

			Text(5, 11, "[동물애호가의 실망감 폭발]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}

		Stage8_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage9_story_index = 0;

int gameStage_9() {

	if (Stage9_story_index == 0) {
		Text(5, 3, "잠시 후");

		Text(5, 5, "싱싱한 채소와 커다란 닭가슴살이 통째로 올라간");
		Text(5, 6, "하우스 샐러드가 서빙되었다.");

		Text(5, 8, "그릇이 생각보다 커서 한 입에 먹기 불편한 상황.");

		move_cursor(146, 8);
		printf("행동을 선택하세요.");

		move_cursor(139, 12);
		printf("1. 그녀의 샐러드를 접시에 덜어준다");

		move_cursor(139, 17);
		printf("2. 그녀의 샐러드를 먹기 좋게 썰어준다");

		move_cursor(139, 22);
		printf("3. 그녀의 샐러드에 소스를 마구 뿌린다");

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

			Text(5, 3, "통째로 나온 커다란 채소와 덩어리 과일을 그대로 덜어주었다.");

			Text(5, 5, "민지는 입을 크게 벌려 먹어야 하는 상황에 직면했고,");
			Text(5, 6, "결국 포크를 대지 못했다.");

			Text(5, 8, "-띠링");

			Text(5, 10, "[배려 부족 판정]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "주인공은 나이프와 포크를 들고");
			Text(5, 4, "큰 채소와 과일을 한 입 크기로 정성스럽게 썰어주었다.");

			Text(5, 6, "\"크기가 좀 커서요. 편하게 드세요.\"");

			Text(5, 8, "민지가 감동한 눈빛으로 바라본다.");

			Text(5, 10, "\"와... 진짜 다정하시네요. 감사합니다ㅎㅎ\"");

			Text(5, 12, "식사는 매우 화기애애하게 진행되었다.");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 10;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "함께 나온 요거트 드레싱을 그녀의 샐러드에 듬뿍 뿌린다.");

			Text(5, 5, "\"아앗.. 저 과일 드레싱만 먹는데..\"");

			Text(5, 7, "-띠링");

			Text(5, 9, "[취향 무배려 판정]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}

		Stage9_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage10_story_index = 0;

int gameStage_10() {

	if (Stage10_story_index == 0) {
		Text(5, 3, "식사가 끝나갈 무렵, 민지가 조심스럽게 자리에서 일어났다.");

		Text(5, 5, "\"큭....! 저 잠시 화장실 좀 다녀올게요.\"");

		Text(5, 7, "혼자 남겨진 주인공. 시스템 창이 번쩍인다.");

		move_cursor(146, 8);
		printf("행동을 선택하세요.");

		move_cursor(139, 12);
		printf("1. 남은 음식을 마저 처먹는다");

		move_cursor(139, 17);
		printf("2. 나도 화장실을 간다");

		move_cursor(139, 22);
		printf("3. 카운터로 가서 계산대로 간다");

		move_cursor(139, 27);
		printf("4. 그녀의 두고 간 휴대폰을 훔쳐본다");

		int choice;

		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 4)
				break;

			move_cursor(137, 45);
			printf("1~4 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "접시를 싹싹 비우며 우물거리고 있을 때 민지가 돌아왔다.");

			Text(5, 5, "그리고 그녀가 자연스럽게 계산을 해버렸다.");

			Text(5, 7, "오늘 만남의 명분은 배상이었지만, 너무 개걸스럽게 먹기만 하는 그림이 되었다.");

			Text(5, 9, "-띠링");

			Text(5, 11, "[매력도 하락]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "그녀가 일어나자마자 나도 일어나 화장실로 향한다.");
			Text(5, 4, "그러자 빈 테이블을 보고 직원이 손님이 나간줄 알고 테이블을 치워버린다.");

			Text(5, 6, "메뉴를 다시 주문하느라 그녀는 돈이 2배로 깨졌다");

			Text(5, 8, "-띠링");

			Text(5, 10, "[의도치 않은 민폐로 인한 호감도 하락]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "잠금을 안해두고 간 그녀.");

			Text(5, 5, "그런데 그녀의 폰에 왠 남자의 이름으로 카톡이 온다.");
			Text(5, 6, "\"민지야 오늘 집에 언제 와? 갖다줄게 있어서. 너희 집으로 갈게.\"");

			Text(5, 8, "주인공은 민지가 다른 남자와 양다리를 걸친 줄 알고 분노한다.");
			Text(5, 9, "마침 민지가 온다.");

			Text(5, 11, "\"이 사람 뭐에요? 설마 양다리 걸친거에요?\"");

			Text(5, 13, "주인공은 화가 나서 민지의 폰을 들이밀며 따진다.");

			Text(5, 15, "\"이 사람 우리 아빠인데요? 그런데 지금 제 폰 훔쳐보신거에요?");
			Text(5, 16, "애초에 저희가 무슨 사이도 아니었고. 하, 이만 가볼게요\"");

			Text(5, 18, "-띠링");

			Text(5, 20, "[신뢰도 하락]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 4) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "주인공은 민지가 화장실에 간 사이 슬쩍 일어나 카운터에서 계산을 마쳤다.");

			Text(5, 5, "잠시 후 돌아온 민지가 지갑을 꺼내려 하자, 주인공이 미소를 지으며 영수증을 보여주었다.");

			Text(5, 9, "민지의 얼굴이 살짝 붉어지며 감동한 기색이 역력했다.");

			Text(5, 11, "\"아니... 제가 대접하려고 한 건데... 너무 감동이에요.\"");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 11;
		}

		Stage10_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage11_story_index = 0;

int gameStage_11() {

	if (Stage11_story_index == 0) {
		Text(5, 3, "만족스러운 식사를 마치고 나온 두 사람.");

		Text(5, 5, "배도 부르겠다, 이제 무엇을 해야 할까?");

		move_cursor(146, 8);
		printf("행동을 선택하세요.");

		move_cursor(139, 12);
		printf("1. 산책");

		move_cursor(139, 17);
		printf("2. 영화 관람");

		move_cursor(139, 22);
		printf("3. 카페 가기");

		move_cursor(139, 27);
		printf("4. 서점 구경");

		int choice;

		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 4)
				break;

			move_cursor(137, 45);
			printf("1~4 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "\"날씨도 좋은데 배도 부르니 근처 공원 좀 걸을까요?\"");

			Text(5, 5, "민지가 환하게 웃었다.");

			Text(5, 7, "\"좋아요! 소화도 시킬 겸 딱이네요.\"");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 12;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "\"우리 영화보러 갈까요?\"");

			Text(5, 5, "영화관에 들어섰다.");

			Text(5, 7, "민지는 공포영화가 보고싶다고 했다.");

			Text(5, 9, "그런데 무서운 장면이 나오자, 주인공은 너무 무서워서 계속 눈을 감고 벌벌 떤다.");
			Text(5, 10, "민지는 그런 에겐같은 모습에 실망한다.");

			Text(5, 12, "-띠링");

			Text(5, 14, "[에겐남으로 낙인]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "\"우리 카페나 갈까요?\"");

			Text(5, 5, "방금 전까지 음료를 마시고 나온 상태다.");
			Text(5, 6, "민지가 배를 만지며 난감해한다.");

			Text(5, 8, "\"아... 아직 배가 너무 불러서 음료는 더 안 들어갈 것 같아요.\"");

			Text(5, 10, "-띠링");

			Text(5, 12, "[센스 부족]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 4) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "\"책 읽으러 갈까요? 근처에 자.주.가.는. 서점이 있거든요\"");

			Text(5, 5, "서점으로 향하고 각자 책을 고른다.");

			Text(5, 7, "\"이 책 읽어보실래요? 제가 재밌게 봤던건ㄷ...\"");

			Text(5, 9, "직원이 갑자기 다가온다");
			Text(5, 10, "\"여기서 대화하시면 안됩니다\"");

			Text(5, 12, "대화할 수 없었기에 각자 어색한 상태로 책을 읽다가");
			Text(5, 13, "시간이 다 가버리고 호감도를 쌓지 못한다.");

			Text(5, 15, "-띠링");

			Text(5, 17, "[코스 선택 미스]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}

		Stage11_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage12_story_index = 0;

int gameStage_12() {

	if (Stage12_story_index == 0) {
		Text(5, 3, "푸르른 공원 산책로를 걷기 시작한 두 사람.");

		Text(5, 5, "사람들이 제법 지나다니는 길목에서 주인공은 어디에 서서 걸어야 할까?");

		move_cursor(146, 8);
		printf("위치 선택");

		move_cursor(139, 12);
		printf("1. 그녀의 오른쪽에 선다");

		move_cursor(139, 17);
		printf("2. 그녀의 왼쪽에 선다");

		move_cursor(139, 22);
		printf("3. 그녀의 뒤에 선다");

		move_cursor(139, 27);
		printf("4. 그녀의 앞에 선다");

		int choice;

		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 4)
				break;

			move_cursor(137, 45);
			printf("1~4 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "산책로 왼쪽에서 가끔 자전거나 킥보드가 지나간다.");
			Text(5, 4, "주인공은 자연스럽게 위협이 오는 쪽을 차단하고, 그녀를 안전한 오른쪽 안쪽에 세워 걸었다.");

			Text(5, 6, "민지는 대화 도중 주인공의 듬직한 매너를 은연중에 느끼며 호감을 키워갔다.");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 13;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "그녀의 왼쪽에는 차도가 있었고,");
			Text(5, 4, "그녀는 자신이 안전한 곳으로 걷는 주인공의 이기적인 모습에 실망한다.");

			Text(5, 6, "-띠링");

			Text(5, 8, "[매너 부족]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "미행하는 괴한도 아니고 졸졸 뒤를 따라 걷는다.");
			Text(5, 4, "민지가 힐끔거리며 무서워한다.");

			Text(5, 6, "-띠링");

			Text(5, 8, "[스토커 오인 판정]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}
		if (choice == 4) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "민지를 앞장서서 걷는다.");

			Text(5, 5, "민지는 뒤통수만 보여주는 주인공의 무심한 모습에");
			Text(5, 6, "자신을 보고싶지 않은줄 알고 실망한다.");

			Text(5, 8, "-띠링");

			Text(5, 10, "[오해 상황]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -2;
		}

		Stage12_story_index = 0;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage13_story_index = 0;

int gameStage_13() {

	if (Stage13_story_index == 0) {
		Text(5, 3, "어느덧 해가 뉘엿뉘엿 지고 있었다.");
		Text(5, 4, "즐거웠던 첫 데이트를 마무리할 시간.");

		Text(5, 6, "\"오늘 정말 즐거웠어요.\"");

		Text(5, 8, "민지가 아쉬운 듯 말했다.");

		Text(5, 10, "\"같은 방향 까지 같이 가실래요…? \"");

		Text(5, 12, "\"...! 네, 좋아요. \"");


		Sleep(3000);

		RemoveStoryArea();
		RemoveMenuInside();

		Stage13_story_index = 1;

	}

	if (Stage13_story_index == 1) {

		Text(5, 3, "동네 역에 도착해 출구로 나온 두 사람.");

		Text(5, 5, "어색하면서도 몽글몽글한 분위기 속에 걸어가는데, 방향이 계속 일치한다.");
		Text(5, 6, "같은 아파트 단지, 같은 동, 심지어 같은 층 엘리베이터 버튼까지 같이 눌렀다.");

		Text(5, 8, "딩동- 7층입니다.");

		Text(5, 10, "민지가 눈을 동그랗게 떴다.");

		Text(5, 12, "\"어...? 혹시 702호 사세요?\"");

		Text(5, 14, "\"네? 저 701호인데...\"");

		Text(5, 16, "[히로인이 알고 보니 바로 옆집 이웃이었다!]");

		Text(5, 18, "-띠링");

		Text(5, 20, "[★ 세이브 포인트가 생성되었습니다 ★]");

		Sleep(3000);

		RemoveStoryArea();
		RemoveMenuInside();

		Stage13_story_index = 2;

	}

	if (Stage13_story_index == 2) {

		Text(5, 22, "민지가 부끄러운 듯 웃으며 말했다.");

		Text(5, 24, "\"세상에... 진짜 바로 옆집이었네요.");
		Text(5, 25, "…이렇게 된 김에... 저녁도 같이 하실래요?\"");


		move_cursor(146, 8);
		printf("장소 선택");

		move_cursor(139, 12);
		printf("1. 민지네");

		move_cursor(139, 17);
		printf("2. 당신집");


		int choice;

		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 2)
				break;

			move_cursor(137, 45);
			printf("1~2 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "주인공은 잠시 머리를 굴린 뒤 정중하게 말했다.");

			Text(5, 5, "\"제 집은 남정네 혼자 사는 곳이라 좀 어수선해서요.");
			Text(5, 6, "실례가 안 된다면 민지 씨네 집으로 가도 될까요?\"");

			Text(5, 8, "민지는 흔쾌히 문을 열어주었다.");

			Text(5, 10, "\"좋아요, 들어오세요!\"");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 14;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "\"그럼 저희 집으로 가시죠!\"");

			Text(5, 5, "주인공의 방은 일주일 동안 치우지 않은 옷가지와 배달 용기로 아수라장이었다.");
			Text(5, 6, "문을 열자마자 민지의 표정이 썩어 들어간다.");

			Text(5, 8, "-띠링");

			Text(5, 10, "[위생 실격]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -3;
		}

		Stage13_story_index = 2;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage14_story_index = 0;

int gameStage_14() {

	if (Stage14_story_index == 0) {
		Text(5, 3, "아기자기하고 깔끔하게 꾸며진 민지의 자취방.");

		Text(5, 5, "\"저녁은 배달시켜 먹을까요? 뭐가 좋으세요?\"");

		move_cursor(146, 8);
		printf("음식을 고르세요.");

		move_cursor(139, 12);
		printf("1. 치킨");

		move_cursor(139, 17);
		printf("2. 중식");

		move_cursor(139, 22);
		printf("3. 분식");

		move_cursor(139, 27);
		printf("4. 라면");

		int choice;

		while (1)
		{
			choice = GetStageChoice_num();

			if (choice >= 1 && choice <= 4)
				break;

			move_cursor(137, 45);
			printf("1~4 사이를 입력하세요");
		}


		if (choice == 1) {
			RemoveStoryArea();

			Text(5, 3, "\"첫 이웃 신고식인데 호불호 없는 치킨에 맥주 한잔 어때요?\"");

			Text(5, 5, "가장 안전하고, 분위기를 돋우기에 최고인 메뉴다.");
			Text(5, 6, "민지도 냉장고에서 캔맥주를 꺼내오며 찬성했다.");

			Text(5, 8, "\"와, 치맥 최고죠!\"");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			Stage14_story_index = 1;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "짜장면과 짬뽕을 시킨다.");

			Text(5, 5, "음식을 먹는 순간 갑자기 피를 토한다.");

			Text(5, 7, "국물에 독극물이 들어있었다.");
			Text(5, 8, "건더기와 진한 국물향으로 인해 전혀 눈치채지 못하고 당한다.");

			Text(5, 10, "-띠링");

			Text(5, 12, "[독살로 인한 사망]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -3;
		}
		if (choice == 3) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "떡볶이를 시킨다.");
			Text(5, 4, "떡볶이는 정제 탄수화물(떡)과 정제당(설탕)이 많아 혈당을 급격히 높입니다.");
			Text(5, 5, "이는 인슐린과 피지 분비를 증가시켜 피부에 좋지 않고….(중략)");

			Text(5, 7, "이로 인해 다음날 민지의 피부가 망가진다.");

			Text(5, 9, "-띠링");

			Text(5, 11, "[배려 부족]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			Stage14_story_index = 0;
			gameStage = -3;
		}
		if (choice == 4) {
			RemoveStoryArea();
			RemoveMenuInside();

			Text(5, 3, "첫 만남에 그것도 여자의 집에서 \"라면 먹고 갈래?\"의 역발상으로 라면을 고른 주인공.");

			Text(5, 5, "의도가 너무 불순해 보인다. 분위기가 급격하게 가라앉는다.");

			Text(5, 7, "-띠링");

			Text(5, 9, "[수작 부리기 적발]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			Stage14_story_index = 0;
			gameStage = -3;
		}

	}

	if (Stage14_story_index == 1) {
		Text(5, 3, "바삭한 치킨이 도착하고, 두 사람은 캔맥주를 부딪쳤다.");

		Text(5, 5, "\"오늘 하루 정말 신기하네요.");
		Text(5, 6, "카페에서 우연히 마주친 사람이 옆집 이웃일 확률이 얼마나 되겠어요?\"");

		Text(5, 8, "민지가 맥주를 한 모금 마시며 베시시 웃었다.");

		Text(5, 10, "주인공 또한 낮에 보았던 그녀의 세심한 모습과,");
		Text(5, 11, "지금 내추럴하게 웃고 있는 모습을 보며 가슴이 깊게 뛰는 것을 느꼈다.");

		Text(5, 13, "음악 이야기, 동네 맛집 이야기로 시작된 대화는");
		Text(5, 14, "밤이 깊어가는 줄도 모르게 이어졌다.");

		Text(5, 16, "\"아, 벌써 시간이 이렇게 됐네... 민지 씨 피곤하시겠어요. 전 이만 가볼게요.\"");

		Text(5, 18, "주인공이 깔끔하게 자리를 정리하고 일어섰다.");
		Text(5, 19, "매너 있는 모습에 민지의 눈빛에는 아쉬움이 가득 묻어났다.");

		Text(5, 21, "현관문 앞.");

		Text(5, 23, "\"오늘 정말 고마웠어요.");
		Text(5, 24, "다음엔... 제가 진짜 맛있는 거 해드릴게요. 옆집이니까 자주 봐요 우리.\"");

		Text(5, 26, "민지가 수줍게 인사를 건넸다.");

		Text(5, 28, "-띠링");

		Text(5, 30, "[히로인 '김민지'와의 호감도가 대폭 상승했습니다!]");
		Text(5, 31, "[2일차 미션: 완벽한 데이트 클리어!]");
		Text(5, 33, "[DAY 2 종료]");

		Sleep(3000);

		RemoveStoryArea();
		RemoveMenuInside();

		Stage14_story_index = 0;
		gameStage = 15;
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

int Stage15_story_index = 0;

int gameStage_15() {

	if (Stage15_story_index == 0) {
		Text(5, 3, "눈을 뜨자마자 시야에 들어오는 메시지 창.");

		Text(5, 5, "-띠링");

		Text(5, 7, "[DAY 3 시작]");
		Text(5, 8, "[현재 루프 회차 : 측정 불가]");

		Text(5, 10, "주인공은 한숨을 쉬며 휴대폰을 들었다.");
		Text(5, 11, "어제 분명 바로 옆집인 민지네 자취방에서 단둘이 치맥까지 먹으면서 분위기가 좋았는데");
		Text(5, 12, "왜 아직도 3일차 아침으로 리셋인 건지 의문이 들었다.");

		Text(5, 14, "하지만 생각해보니 당연했다.");
		Text(5, 15, "고백도 안 하고 안 사귀었으니까 루프가 안 끝나고 어제가 반복되는 게 당연했다.");

		Text(5, 17, "결국 오늘 밤이 되기 전 그녀에게 확실하게 고백해서 '연인 관계'를 확정 짓지 못하면");
		Text(5, 18, "이 지옥 같은 무한 루프는 끝나지 않는다. 오늘 무조건 끝장을 낸다.");

		move_cursor(146, 8);
		printf("행동을 고르세요");

		move_cursor(139, 12);
		printf("1. 정식으로 톡을 보내 약속을 잡는다");

		move_cursor(139, 17);
		printf("2. 추리닝 차림으로 옆집 문을 두드린다");

		move_cursor(139, 22);
		printf("3. 쓰레기 버리러 나간다.");

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

			Text(5, 3, "\"아니지, 정신 차려. 확실하게 성공하려면 단 1%의 빈틈도 보이면 안 돼.\"");

			Text(5, 5, "\"깔끔하게 씻고 제대로 옷을 갖춰 입은 뒤 정식으로 데이트 신청을 한다.\"");

			Text(5, 7, "주인공은 깔끔하게 준비를 마친 뒤, 떨리는 손가락으로 민지에게 직진 카톡을 보냈다.");
			Text(5, 8, "어제 치맥의 여운이 가시기 전인 지금이 타이밍이다.");

			Text(5, 10, "\"민지 씨, 어제 치맥 너무 즐거웠어요ㅋㅋ");
			Text(5, 11, "오늘 날씨 되게 좋은데, 오후 2시에 동네 공원에서 잠깐 볼래요?\"");

			Text(5, 13, "\"실은 민지 씨한테 꼭 하고 싶은 말이 있어서요.\"");

			Text(5, 15, "톡을 보내자마자 상단의 숫자 '1'이 광속으로 지워졌다.");
			Text(5, 16, "엄청난 속도의 칼답이었다!");

			Text(5, 18, "\"어? 진짜요?!\"");

			Text(5, 20, "\"저 안 그래도 어제 너무너무 재밌어가지구 오늘도 먼저 연락해 볼까 엄청 고민하고 있었는데 통했네요!\"");
			Text(5, 21, "\"헤헤 당연히 나가야죠! 무슨 할 말이길래 그렇게 진지해요?\"");
			Text(5, 22, "\"궁금하니까 2시까지 공원 앞으로 조심히 와요! 기다릴게요!\"");

			Text(5, 24, "주인공은 주먹을 불끈 쥐었다. 호감도 스택은 이미 가득 차 있었다.");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = 16;
		}
		if (choice == 2) {
			RemoveStoryArea();

			Text(5, 3, "\"어차피 어제 라면 드립에 치맥까지 깠는데 굳이 딱딱하게 카톡을 보낼 필요가 있나?\"");

			Text(5, 5, "\"옆집 사촌의 묘미는 바로 이 기습 방문이지!\"");

			Text(5, 7, "주인공은 무릎 나온 추리닝에 까치집이 지어진 머리를 대충 털며 옆집 702호 문을 똑똑 두드렸다.");

			Text(5, 9, "\"민지 씨~ 좋은 아침! 어제 치맥 진짜 잘 먹었습니다. 혹시 오늘……\"");

			Text(5, 11, "딸칵- 하고 문이 열리는데, 안에서 나온 사람은 호랑이 문신을 한 덩치 큰 험상궂은 아저씨였다.");
			Text(5, 12, "주말을 맞아 딸의 자취방에 기습 방문하신 민지의 아버님이셨다!");

			Text(5, 14, "꾀죄죄한 차림으로 아침부터 딸의 문 앞을 서성거리는 불청객을 본 아버님의 눈이 뒤집혔고,");
			Text(5, 15, "변명 한마디 못 한 채 복도에서 영혼까지 털리게 된다.");

			Text(5, 17, "민지는 뒤에서 안절부절못하며 눈물만 글썽이고 있었고, 분위기는 완전히 파탄 났다.");

			Text(5, 19, "-띠링");

			Text(5, 21, "[히로인 아버님 격노 / 예비 장인어른 기피 대상 1호 지정]");
			Text(5, 22, "[관계 회복 불가능 판정으로 인한 세계선 붕괴.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -3;
		}
		if (choice == 3) {
			RemoveStoryArea();

			Text(5, 3, "\"인위적인 약속은 하수나 하는 짓이지.\"");

			Text(5, 5, "\"이따 분리수거 하러 나가는 척하면서 복도에서 자연스럽게 마주치는 상황을 노린다.\"");

			Text(5, 7, "주인공은 세수도 하지 않고 눈곱만 대충 뗀 채, 찌그러진 페트병들을 들고 현관문을 벌컥 열었다.");
			Text(5, 8, "마침 옆집 문도 동시에 스르륵 열리더니, 화사하게 외출 준비를 마친 민지가 걸어 나왔다.");

			Text(5, 10, "\"어……? 민우 씨……? 아, 안녕하세…… 요?\"");

			Text(5, 12, "동시에 두 사람의 시선이 교차했다.");

			Text(5, 13, "민지의 시선은 주인공의 떡진 머리와 눈가에 잔뜩 낀 눈곱");
			Text(5, 14, "그리고 정체 모를 국물이 뚝뚝 떨어지는 쓰레기봉투로 향했다.");

			Text(5, 16, "어제 치맥을 먹으며 쌓아 올린 훈훈한 이웃 오빠의 환상이 단 1초 만에 박살 났다.");

			Text(5, 18, "민지는 썩어 들어가는 표정으로 도망치듯 엘리베이터를 타고 사라졌고");
			Text(5, 19, "그날 이후 주인공을 벌레 보듯 피하게 되었다.");

			Text(5, 21, "-띠링");

			Text(5, 23, "[남주의 신비감 제로 / 비주얼 쇼크로 인한 호감도 파탄]");
			Text(5, 24, "[대참사로 인한 영구 차단.]");

			Sleep(3000);

			RemoveStoryArea();
			RemoveMenuInside();

			gameStage = -3;
		}

		Stage15_story_index = 0;

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

int Ending_bad_CheckPoint_2() {

	Text(5, 3, "베드엔딩");
	Text(5, 5, "[루프를 시작합니다.]");
	Text(5, 6, "[체크포인트로 이동합니다.]");
	Text(5, 8, "3...");
	Text(5, 9, "2...");
	Text(5, 10, "1...");

	Sleep(1000);

	gameStage = 13;

	return 0;
}