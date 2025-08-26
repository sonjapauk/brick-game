
#ifndef _TETRIS_BACKEND_H_
#define _TETRIS_BACKEND_H_

#include <math.h>
#include <stdlib.h>

#include "../game_objects.h"
#include "defines.h"

typedef enum {
  SQUARE,
  LINE,
  SNAIL_RIGHT,
  SNAIL_LEFT,
  POKER_LEFT,
  POKER_RIGHT,
  UFO,
  NOT_DEFINED
} figure_type_t;

typedef struct {
  int figure[FIGURE_ROWS][FIGURE_COLUMNS];
  int position;
  int x;
  int y;
  figure_type_t figure_type;
} figure_t;

void fill_square(int figure[FIGURE_ROWS][FIGURE_COLUMNS]);
void fill_line(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position);
void fill_poker_left(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position);
void fill_poker_right(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position);
void fill_snail_left(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position);
void fill_snail_right(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position);
void fill_ufo(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position);
void fill_figure(int figure[FIGURE_ROWS][FIGURE_COLUMNS],
                 figure_type_t figure_type, int position);
void clean_figure(int figure[FIGURE_ROWS][FIGURE_COLUMNS]);
void clean_figure_current_position(figure_t figure, int **field);
void add_figure_to_field(int **field, figure_t figure);
void set_figure(figure_t *figure, figure_type_t figure_type, int x, int y,
                int position);
void horizontal_move(user_action_t user_action, game_info_t *current_state,
                     figure_t *current_figure);
void rotate_figure(game_info_t *current_state, figure_t *current_figure);
void drop_figure(game_info_t *current_state, figure_t *current_figure);
bool is_collide(int **field, figure_t *current_figure);
void remove_line(int **field, int line_to_remove);
void process_lines(game_info_t *current_state, figure_t *current_figure);
bool is_gameover(game_info_t *current_state);
void clean_field(int **field);
int read_high_score_from_file(const char *file_path);
void write_high_score_to_file(const char *file_path, int new_high_score);
void stats_init(game_info_t *current_state);
void stats_delete(game_info_t *current_state);
bool shift_figure(figure_t *current_figure, game_info_t *current_state);

#endif