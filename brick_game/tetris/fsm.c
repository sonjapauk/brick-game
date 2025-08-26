#include "../../inc/tetris/fsm.h"

static tetris_state_t tetris_state = INIT;
static figure_t current_figure = {{{0}}, 0, 0, 0, NOT_DEFINED};
static figure_t next_figure = {{{0}}, 0, 0, 0, NOT_DEFINED};
static struct timespec start_time;
static struct timespec current_time;

tetris_state_t get_tetris_state() { return tetris_state; }

void set_tetris_state(tetris_state_t new_tetris_state) {
  tetris_state = new_tetris_state;
}

void on_init_state(game_info_t *current_state) {
  stats_init(current_state);
  tetris_state = START_TETRIS;
}

void on_start_state(user_action_t user_action, game_info_t *current_state) {
  current_state->high_score =
      read_high_score_from_file(HIGH_SCORE_TETRIS_FILE_PATH);

  if (user_action == START) {
    clock_gettime(CLOCK_REALTIME, &start_time);
    tetris_state = SPAWN;
  }
}

void on_spawn_state(game_info_t *current_state) {
  if (next_figure.figure_type == NOT_DEFINED) {
    set_figure(&next_figure, (figure_type_t)(rand() % 7), 0, 0, 0);
  }

  figure_type_t current_figure_type = next_figure.figure_type;
  figure_type_t next_figure_type = (figure_type_t)(rand() % 7);

  clean_figure_current_position(next_figure, current_state->next);

  set_figure(&current_figure, current_figure_type, START_X, START_Y, 0);
  set_figure(&next_figure, next_figure_type, 0, 0, 0);

  add_figure_to_field(current_state->field, current_figure);
  add_figure_to_field(current_state->next, next_figure);

  tetris_state = MOVING;
}

void on_moving_state(user_action_t user_action, game_info_t *current_state) {
  if (user_action != (user_action_t)NO_ACTION) {
    clean_figure_current_position(current_figure, current_state->field);

    switch (user_action) {
      case LEFT:
      case RIGHT:
        horizontal_move(user_action, current_state, &current_figure);
        break;
      case ACTION:
        rotate_figure(current_state, &current_figure);
        break;
      case DOWN:
        drop_figure(current_state, &current_figure);
        tetris_state = ATTACHING;
        break;
      default:
        break;
    }

    add_figure_to_field(current_state->field, current_figure);
  }

  clock_gettime(CLOCK_REALTIME, &current_time);

  double time_diff = current_time.tv_sec - start_time.tv_sec +
                     (current_time.tv_nsec - start_time.tv_nsec) * 1e-9;

  if (time_diff >= 1 / (1 + (current_state->level - 1) * SPEED_COEFFICIENT)) {
    start_time = current_time;
    tetris_state = SHIFTING;
  }
}

void on_shifting_state(game_info_t *current_state) {
  clean_figure_current_position(current_figure, current_state->field);

  tetris_state =
      shift_figure(&current_figure, current_state) ? MOVING : ATTACHING;

  add_figure_to_field(current_state->field, current_figure);
}

void on_attaching_state(game_info_t *current_state) {
  process_lines(current_state, &current_figure);

  tetris_state = is_gameover(current_state) ? GAMEOVER : SPAWN;
}

void on_gameover_state(user_action_t user_action, game_info_t *current_state) {
  clean_figure_current_position(next_figure, current_state->next);

  if (user_action == START) {
    clean_field(current_state->field);
    current_state->level = 1;
    current_state->score = 0;

    tetris_state = START_TETRIS;
  }
}

void on_exit_state(game_info_t *current_state) {
  stats_delete(current_state);
  tetris_state = INIT;
}

void tetris_fsm(user_action_t user_action, game_info_t *current_state) {
  if (user_action == TERMINATE) {
    tetris_state = EXIT_TETRIS;
  }

  switch (tetris_state) {
    case INIT:
      on_init_state(current_state);
      break;
    case START_TETRIS:
      on_start_state(user_action, current_state);
      break;
    case SPAWN:
      on_spawn_state(current_state);
      break;
    case MOVING:
      on_moving_state(user_action, current_state);
      break;
    case SHIFTING:
      on_shifting_state(current_state);
      break;
    case ATTACHING:
      on_attaching_state(current_state);
      break;
    case GAMEOVER:
      on_gameover_state(user_action, current_state);
      break;
    case EXIT_TETRIS:
      on_exit_state(current_state);
      break;
    default:
      break;
  }
}
