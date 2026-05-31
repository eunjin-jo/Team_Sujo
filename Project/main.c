#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>



//202618970 조은진
// 테스트
//이세빈
//송한이
//윤수아
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
 * -3: 게임 시작힐때 로고 / GAMESTATE_LOGO
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
int gameStage = 0;


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

void ClearStoryArea()
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

void ClearMenuInside()
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
}

int game_screen() {
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

}

int RenderGame() {

	game_screen();

	//gameStage -2 : 배드엔딩
	//gameStage 0 : 프롤로그
	//gameStage 1 : 스테이지 1
	//gameStage 2 : 스테이지 2

	switch (gameStage) {
		case -2 : 
			gameEnding_bad();
			break;
		case 0:
			move_cursor(5, 3);
			printf("프롤로그 진행");
			move_cursor(5, 5);
			printf("여기다가 대충");
			move_cursor(5, 7);
			printf("방향키 > 누르면 스테이지 1");
			break;
		case 1 : 
			gameStage_1();
			break;
		case 2:
			gameStage_2();
			break;
	}




	return 0;
}

int RenderHelp() {
	move_cursor(1, 1);

	printf("게임설명 페이지\n");

	return 0;
}

int RenderCredits() {
	move_cursor(1, 1);

	printf("팀 소개 페이지\n");

	return 0;
}


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
	case 77:
		if(gameStage == 0) gameStage = 1; 
		break;

	}

	return 0;
}



int main()
{
	gameState = GAMESTATE_START;
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

int stage_initialized = 0;

int gameStage_1() {

	int stage1_choice = 0;

	if (!stage_initialized) {
		ClearStoryArea();
		ClearMenuInside();
		stage_initialized = 1;
	}

	move_cursor(5, 3);
	printf("      \n");
	printf("                               어딘가 위험해 보이는 그녀   \n");
	printf("                                          ,..                                                                         \n");
	printf("                                       .==*+==:,.                                                                         \n");
	printf("                                      ;#$$!$####$-                                                                         \n");
	printf("                                     =##$;'=$#@@##:                                                                           \n");
	printf("                                     ~#@=   ;-=;##-                                                                         \n");
	printf("                                     !@@-,    . ##!                    옆집 소녀                                                    \n");
	printf("                                     @#@!,    -!##$-                                                                    \n");
	printf("                                     $*@# -   ;@@@=,                     :;;--                                              \n");
	printf("                                     ,;$@@*=-~####!                   ~=*==*!-.                                            \n");
	printf("                                     ,:=@@@@$,.;#@#*.                 .*$**!*!::                                              \n");
	printf("                                     ,~=@@@@@..;@$#~                  -$$=*:::!:                    청순한 그녀                \n");
	printf("                                     .!#@@@@@~,,-#$::                 ;$!!   =$;.                                        \n");
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
	printf("                        :=:.$#=!;. :;!;$=;~-......,=@@*  ~   :::!*!!!!*===#==::,, -;*,#    .!;;;!*===*~.-*@#$$=$!-          \n");
	printf("                        :=$=##*~~- ..-.,,.-,. . .,;##$!.        .,,~*::::~~-~-:..  ~*,$    *,.- ~*~!:~, ,*$##$==;.          \n");
	printf("                        #$#!##=;::.      ~~-- ,,-:!@:*:!.          ,*-,,,.    .. . :$,!    !.    :..:-~...~=##$$$!.         \n");
	printf("                        #$#=$$==$=$=;;#@@$-~,..::~:=#.             ,*-,.      ,...,~$:-,   :.  ,  ---:.  .!*###$*~-         \n");
	printf("                       *!*~--~::**====@@#!!;-~~~~,;!*             ,*-,  ...  ,.,.~:==-,   ;.    . .,-.  ,::=##$=:.         \n");
	printf("                        .,:;;;;===***!*#@@###!~~~-,:-,            .,*-,...-!==*...;$$#. -!::..  .  .,.    ,-;##!:.          \n");
	printf("                        ;:;:#$$$==!!!*=@@###@~,,--,.              .,*:,.;=$#$==~--###,!*$$#=,.   ,  ..     ::$##:           \n");
	printf("                        ;$$===*;==*!!!!#@@##@--.,-,,              .,**..~$*$*!!.,*$#$;*;,,,!. . .-  .,,,-,.-*$$$$=,         \n");
	printf("                        =!!;~:;;*=*!!*!#@@##@,,,~,.,             ,.~=:.. =.=,     :=#$,*===*, , ,.-  .    ,,~*$$=!.         \n");
	printf("                        :::~~:;;*=*!;*;#@@##@,.,;,.             ,. -=-.,.=,;       *$$ $===*-.. ..,      . ~-!$$=!,         \n");
	printf("                        ::::~:;;===*!=*#@@##@..,;,.             ..~-$,,;~=!-       ~#$ $====!, ..-,~        :!$$$~.         \n");
	printf("                        ~:::~:;:*==*##@@@###@,.,!..            ... -$,,;-=!.       -## @#$$*-,. .:,.   ......,;=      .,,.  \n");
	printf("                        ~:~:~:;;===*@@@@@@@@@!.,: . .         ,-,. -;.,*,=         ,=$ =#$$$!-,..,,.,,,,,,,,-~:,.,---~:!!;~-\n");
	printf("                        ~::::;;;===#@@@@@@@@@$.,-.. ~        ,-,-. -~.-*.=          !#,~#$$$;~,....,-,-,----~;~::;;;;;;;;;;;\n");
	printf("                        ~~:::;;!===#@@@@@@@#@$.-~., -       --.,,: --..! =          :##,###$;~,..:,,--~---~~:;;;;;;;;;;;;;;;\n");
	printf("                        ~::::;!;===#@@@@@@@##$.~~..       .--.,,,. ,,..; =          ;#=-@###*~-...*.,-~-~~~~;:!;;;;;;;;;;;;;\n");
	printf("                        ~~~:::;;===#@@@@@@@@@$.~~.        ,,,,,,---~-,.; =          ;=#:$###*~--~,=.,-~~~~~:!-:;;;;;;;;:;;;;\n");
	printf("                        ~~~:::;!===##@@=@@@@@#,~~...       ~!:   ;~-..*=-=          ;~#*!$#$;~-,:,~. .--~::!*:;;;;;!!!~-:;;;\n");

	game_screen();

	move_cursor(5, 5);
	printf("근처 카페");

	Sleep(2000);


	move_cursor(145, 6);
	printf("공략상대선택");


	move_cursor(139, 13);
	printf("1. 어딘가 위험해 보이는 그녀");

	move_cursor(139, 18);
	printf("2. 옆집 소녀"); //정답

	move_cursor(139, 23);
	printf("3. 청순한 그녀");

	move_cursor(139, 28);
	printf("4. 사람4");

	int choice = GetStageChoice_num();

	if (choice >= 1 && choice <= 4)
	{
		stage1_choice = choice;
	}

	move_cursor(5, 7);
	printf("게임스테이지1 선택 : %d", choice);

	if(choice == 2) {
		move_cursor(5, 9);
		printf("정답입니다!");
		move_cursor(5, 10);
		printf("다음 스테이지로 이동합니다");
		Sleep(2000);
		gameStage = 2;
	}
	else {
		move_cursor(5, 9);
		printf("틀렸습니다.");
		gameStage = -2;
	}

	Sleep(2000);

	stage_initialized = 0;
	return 0;
}

int gameStage_2() {


	if (!stage_initialized) {
		ClearStoryArea();
		ClearMenuInside();
		stage_initialized = 1;
	}

	move_cursor(5, 3);
	printf("여기다가");
	move_cursor(5, 5);
	printf("게임스테이지2");


	return 0;
}

int gameEnding_bad() {
	if (!stage_initialized) {
		ClearStoryArea();
		ClearMenuInside();
		stage_initialized = 1;
	}

	move_cursor(5, 3);
	printf("베드엔딩");

	return 0;
}