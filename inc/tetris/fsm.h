#ifndef TETRIS_FSM_H
#define TETRIS_FSM_H

#include <time.h>

#include "backend.h"

typedef enum {
  INIT,
  START_TETRIS,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  EXIT_TETRIS
} tetris_state_t;

void tetris_fsm(user_action_t user_action, game_info_t *current_state);
void on_init_state(game_info_t *current_state);
void on_start_state(user_action_t user_action, game_info_t *current_state);
void on_spawn_state(game_info_t *current_state);
void on_shifting_state(game_info_t *current_state);
void on_moving_state(user_action_t user_action, game_info_t *current_state);
void on_attaching_state(game_info_t *current_state);
void on_gameover_state(user_action_t user_action, game_info_t *current_state);

tetris_state_t get_tetris_state();

#endif