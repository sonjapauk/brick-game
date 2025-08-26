#include "frontend.h"

void win_init(int time) {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(time);
}

void print_overlay() {
  print_rectangle(0, BOARD_N + 1, 1, BOARD_M + 3);
  print_rectangle(0, BOARD_N + 1, BOARD_M + 4, BOARD_M + HUD_WIDTH + 5);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) {
    mvaddch(top_y, i, ACS_HLINE);
  }

  mvaddch(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);

  i = left_x + 1;

  for (; i < right_x; i++) {
    mvaddch(bottom_y, i, ACS_HLINE);
  }

  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void print_menu(menu_status_t menu_status) {
  if (menu_status == MENU_TETRIS) {
    mvprintw(2, BOARD_M + 7, "> TETRIS");
    mvprintw(5, BOARD_M + 7, "  SNAKE");
    mvprintw(8, BOARD_M + 7, "  EXIT");
  } else if (menu_status == MENU_SNAKE) {
    mvprintw(2, BOARD_M + 7, "  TETRIS");
    mvprintw(5, BOARD_M + 7, "> SNAKE");
    mvprintw(8, BOARD_M + 7, "  EXIT");
  } else {
    mvprintw(2, BOARD_M + 7, "  TETRIS");
    mvprintw(5, BOARD_M + 7, "  SNAKE");
    mvprintw(8, BOARD_M + 7, "> EXIT");
  }
}

void print_game_overlay() {
  print_rectangle(1, 3, BOARD_M + 5, BOARD_M + HUD_WIDTH + 4);
  print_rectangle(4, 6, BOARD_M + 5, BOARD_M + HUD_WIDTH + 4);
  print_rectangle(7, 9, BOARD_M + 5, BOARD_M + HUD_WIDTH + 4);
  print_rectangle(10, 12, BOARD_M + 5, BOARD_M + HUD_WIDTH + 4);

  mvprintw(1, BOARD_M + 7, "LEVEL");
  mvprintw(4, BOARD_M + 7, "SCORE");
  mvprintw(7, BOARD_M + 7, "HIGH SCORE");
  mvprintw(10, BOARD_M + 7, "PAUSE");
}

void print_tetris_overlay() {
  print_rectangle(16, 20, BOARD_M + 6, BOARD_M + HUD_WIDTH + 3);

  mvaddch(17, BOARD_M + HUD_WIDTH + 3, 'N');
  mvaddch(18, BOARD_M + HUD_WIDTH + 3, 'E');
  mvaddch(19, BOARD_M + HUD_WIDTH + 3, 'X');
  mvaddch(20, BOARD_M + HUD_WIDTH + 3, 'T');
}

void print_field(game_info_t *current_state) {
  for (int i = 1; i < FIELD_LENGTH - 1; i++) {
    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      if (current_state->field[i][j] == 1) {
        mvprintw(i, 2 * j + 1, "▢");
      } else {
        mvprintw(i, 2 * j + 1, " ");
      }
    }
  }
}

void print_stat(game_info_t *current_state) {
  mvprintw(2, BOARD_M + 7, "%d", current_state->level);
  mvprintw(5, BOARD_M + 7, "%d", current_state->score);
  mvprintw(8, BOARD_M + 7, "%d", current_state->high_score);

  const char *pause_state = current_state->pause ? "ON" : "OFF";

  mvprintw(11, BOARD_M + 7, "%s", pause_state);
}

void print_next_figure(game_info_t *current_state) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_state->next[i][j] == 1) {
        mvprintw(16 + (i + 1), BOARD_M + (2 * j + 1) + 7, "▢");
      } else {
        mvprintw(16 + (i + 1), BOARD_M + (2 * j + 1) + 7, " ");
      }
    }
  }
}

void print_message(game_status_t game_status) {
  if (game_status == START_GAME) {
    mvprintw(BOARD_N / 2 - 1, (BOARD_M - INTRO_MESSAGE_LEN_F) / 2 + 3,
             INTRO_MESSAGE_F);
    mvprintw(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN_S) / 2 + 3,
             INTRO_MESSAGE_S);
  } else if (game_status == GAMEOVER_GAME) {
    mvprintw(BOARD_N / 2 - 2, (BOARD_M - GAMEOVER_LEN) / 2 + 3, GAMEOVER_WORD);
    mvprintw(BOARD_N / 2 - 1, (BOARD_M - INTRO_MESSAGE_LEN_F) / 2 + 3,
             INTRO_MESSAGE_F);
  } else if (game_status == WIN) {
    mvprintw(BOARD_N / 2 - 2, (BOARD_M - WIN_LEN) / 2 + 3, WIN_WORD);
    mvprintw(BOARD_N / 2 - 1, (BOARD_M - INTRO_MESSAGE_LEN_F) / 2 + 3,
             INTRO_MESSAGE_F);
  }
}

void print_current_state(brick_game_status_t status, game_status_t game_status,
                         game_info_t *current_state) {
  print_stat(current_state);

  print_field(current_state);

  if (status == TETRIS) {
    print_next_figure(current_state);
  }

  print_message(game_status);
}

void print_shot(brick_game_status_t status, menu_status_t menu_status,
                game_status_t game_status, game_info_t *current_state) {
  clear();
  print_overlay();

  if (status == MENU) {
    print_menu(menu_status);
  } else if (status != EXIT) {
    print_game_overlay();

    if (status == TETRIS) {
      print_tetris_overlay();
    }

    print_instruction(status);

    print_current_state(status, game_status, current_state);
  }
}

void print_instruction(brick_game_status_t status) {
  mvprintw(2, 43, "INSTRUCTION:");
  mvprintw(4, 43, "Key \"p\" - pause");
  mvprintw(6, 43, "ESC - exit to menu");

  if (status == TETRIS) {
    mvprintw(8, 43, "SPACE - rotate figure");
    mvprintw(10, 43, "LEFT/RIGHT arrow - move figure");
    mvprintw(12, 43, "DOWN arrow - drop figure");
  } else if (status == SNAKE) {
    mvprintw(8, 43, "SPACE - speed up snake");
    mvprintw(10, 43, "LEFT/RIGHT/UP/DOWN arrow - controle snake");
    mvprintw(
        12, 43,
        "You can also use the arrows in direction of moving to speed up ;)");
  }
}

void cli_print_game(brick_game_status_t status, menu_status_t menu_status,
                    game_status_t game_status, game_info_t *current_state) {
  static struct timespec start_shot_time = {(__darwin_time_t)0, 0};

  static struct timespec end_shot_time;
  clock_gettime(CLOCK_REALTIME, &end_shot_time);

  double time_diff = end_shot_time.tv_sec - start_shot_time.tv_sec +
                     (end_shot_time.tv_nsec - start_shot_time.tv_nsec) * 1e-9;

  if (time_diff >= 1. / FPS) {
    print_shot(status, menu_status, game_status, current_state);
    clock_gettime(CLOCK_REALTIME, &start_shot_time);
  }
}

int get_cli_key() { return getch(); }