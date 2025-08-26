#ifndef _CLI_FRONTEND_H_
#define _CLI_FRONTEND_H_

#include <ncurses.h>
#undef scroll

#include <locale.h>
#include <time.h>

#include "../../inc/game_objects.h"

#define ENTER_KEY 10
#define ESCAPE_KEY 27
#define SPACE_KEY 32
#define PAUSE_KEY 112

#define BOARD_N ROWS_MAP
#define BOARD_M 20
#define HUD_WIDTH 14
#define MAP_PADDING 1
#define ROWS_MAP 20

#define INTRO_MESSAGE_LEN_F 11
#define INTRO_MESSAGE_F "Press ENTER"
#define INTRO_MESSAGE_LEN_S 9
#define INTRO_MESSAGE_S "to start!"

#define GAMEOVER_LEN 9
#define GAMEOVER_WORD "GAMEOVER!"

#define WIN_LEN 8
#define WIN_WORD "YOU WON!"

void win_init(int time);
void print_overlay();
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_menu(menu_status_t menu_status);
void print_game_overlay();
void print_tetris_overlay();
void print_stat(game_info_t *current_state);
void print_field(game_info_t *current_state);
void print_next_figure(game_info_t *current_state);
void print_current_state(brick_game_status_t status, game_status_t game_status,
                         game_info_t *current_state);
void print_message(game_status_t game_status);
void print_shot(brick_game_status_t status, menu_status_t menu_status,
                game_status_t game_status, game_info_t *current_state);
void print_instruction(brick_game_status_t status);
void cli_print_game(brick_game_status_t status, menu_status_t menu_status,
                    game_status_t game_status, game_info_t *current_state);
int get_cli_key();

#endif
