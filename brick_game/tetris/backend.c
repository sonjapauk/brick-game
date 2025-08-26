#include "../../inc/tetris/backend.h"

void fill_square(int figure[FIGURE_ROWS][FIGURE_COLUMNS]) {
  figure[0][1] = figure[0][2] = figure[1][1] = figure[1][2] = 1;
}

void fill_line(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position) {
  switch (position) {
    case 0:
    case 2:
      figure[1][1] = figure[1][2] = figure[1][3] = figure[1][0] = 1;
      break;
    case 1:
      figure[0][1] = figure[1][1] = figure[2][1] = figure[3][1] = 1;
      break;
    case 3:
      figure[0][2] = figure[1][2] = figure[2][2] = figure[3][2] = 1;
      break;
  }
}

void fill_snail_right(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position) {
  switch (position) {
    case 0:
    case 2:
      figure[0][0] = figure[0][1] = figure[1][1] = figure[1][2] = 1;
      break;
    case 1:
    case 3:
      figure[0][2] = figure[1][1] = figure[1][2] = figure[2][1] = 1;
      break;
  }
}

void fill_snail_left(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position) {
  switch (position) {
    case 0:
    case 2:
      figure[0][1] = figure[0][2] = figure[1][0] = figure[1][1] = 1;
      break;
    case 1:
    case 3:
      figure[0][1] = figure[1][1] = figure[1][2] = figure[2][2] = 1;
      break;
  }
}

void fill_poker_left(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position) {
  switch (position) {
    case 0:
      figure[0][0] = figure[1][0] = figure[1][1] = figure[1][2] = 1;
      break;
    case 1:
      figure[0][1] = figure[0][2] = figure[1][1] = figure[2][1] = 1;
      break;
    case 2:
      figure[1][0] = figure[1][1] = figure[1][2] = figure[2][2] = 1;
      break;
    case 3:
      figure[0][1] = figure[1][1] = figure[2][0] = figure[2][1] = 1;
      break;
  }
}

void fill_poker_right(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position) {
  switch (position) {
    case 0:
      figure[0][2] = figure[1][0] = figure[1][1] = figure[1][2] = 1;
      break;
    case 1:
      figure[0][1] = figure[1][1] = figure[2][1] = figure[2][2] = 1;
      break;
    case 2:
      figure[1][0] = figure[1][1] = figure[1][2] = figure[2][0] = 1;
      break;
    case 3:
      figure[0][0] = figure[0][1] = figure[1][1] = figure[2][1] = 1;
      break;
  }
}

void fill_ufo(int figure[FIGURE_ROWS][FIGURE_COLUMNS], int position) {
  switch (position) {
    case 0:
      figure[0][1] = figure[1][0] = figure[1][1] = figure[1][2] = 1;
      break;
    case 1:
      figure[0][1] = figure[1][1] = figure[1][2] = figure[2][1] = 1;
      break;
    case 2:
      figure[1][0] = figure[1][1] = figure[1][2] = figure[2][1] = 1;
      break;
    case 3:
      figure[0][1] = figure[1][0] = figure[1][1] = figure[2][1] = 1;
      break;
  }
}

void add_figure_to_field(int **field, figure_t figure) {
  for (int i = 0; i < FIGURE_ROWS; i++) {
    for (int j = 0; j < FIGURE_COLUMNS; j++) {
      if (figure.figure[i][j] == 1) {
        field[i + figure.y][j + figure.x] = 1;
      }
    }
  }
}

void clean_figure_current_position(figure_t figure, int **field) {
  for (int i = 0; i < FIGURE_ROWS; i++) {
    for (int j = 0; j < FIGURE_COLUMNS; j++) {
      if (figure.figure[i][j] == 1) {
        field[i + figure.y][j + figure.x] = 0;
      }
    }
  }
}

void clean_figure(int figure[FIGURE_ROWS][FIGURE_COLUMNS]) {
  for (int i = 0; i < FIGURE_ROWS; i++) {
    for (int j = 0; j < FIGURE_COLUMNS; j++) {
      figure[i][j] = 0;
    }
  }
}

void fill_figure(int figure[FIGURE_ROWS][FIGURE_COLUMNS],
                 figure_type_t figure_type, int position) {
  switch (figure_type) {
    case SQUARE:
      fill_square(figure);
      break;
    case LINE:
      fill_line(figure, position);
      break;
    case SNAIL_RIGHT:
      fill_snail_right(figure, position);
      break;
    case SNAIL_LEFT:
      fill_snail_left(figure, position);
      break;
    case POKER_LEFT:
      fill_poker_left(figure, position);
      break;
    case POKER_RIGHT:
      fill_poker_right(figure, position);
      break;
    case UFO:
      fill_ufo(figure, position);
      break;
    default:
      break;
  }
}

void set_figure(figure_t *figure, figure_type_t figure_type, int x, int y,
                int position) {
  clean_figure(figure->figure);

  fill_figure(figure->figure, figure_type, position);

  figure->position = position;
  figure->x = x;
  figure->y = y;
  figure->figure_type = figure_type;
}

int read_high_score_from_file(const char *file_path) {
  int high_score_from_file = 0;

  FILE *file = fopen(file_path, "r");

  if (file) {
    fscanf(file, "%d", &high_score_from_file);
    fclose(file);
  }

  return high_score_from_file;
}

void write_high_score_to_file(const char *file_path, int new_high_score) {
  FILE *file = fopen(file_path, "w");

  if (file) {
    fprintf(file, "%d", new_high_score);
    fclose(file);
  }
}

void horizontal_move(user_action_t user_action, game_info_t *current_state,
                     figure_t *current_figure) {
  int tmp_x = current_figure->x;

  if (user_action == LEFT) {
    current_figure->x--;
  } else {
    current_figure->x++;
  }

  if (is_collide(current_state->field, current_figure)) {
    current_figure->x = tmp_x;
  }
}

void rotate_figure(game_info_t *current_state, figure_t *current_figure) {
  int tmp_position = current_figure->position;
  int new_position = (current_figure->position + 1) % 4;

  set_figure(current_figure, current_figure->figure_type, current_figure->x,
             current_figure->y, new_position);

  if (is_collide(current_state->field, current_figure)) {
    set_figure(current_figure, current_figure->figure_type, current_figure->x,
               current_figure->y, tmp_position);
  }
}

void drop_figure(game_info_t *current_state, figure_t *current_figure) {
  do {
    current_figure->y++;
  } while (!is_collide(current_state->field, current_figure));

  current_figure->y--;
}

bool shift_figure(figure_t *current_figure, game_info_t *current_state) {
  current_figure->y++;
  bool was_shifted = TRUE;

  if (is_collide(current_state->field, current_figure)) {
    current_figure->y--;
    was_shifted = FALSE;
  }

  return was_shifted;
}

bool is_collide(int **field, figure_t *current_figure) {
  bool is_collide = FALSE;

  for (int i = 0; i < FIGURE_ROWS && !is_collide; i++) {
    for (int j = 0; j < FIGURE_COLUMNS; j++) {
      if (current_figure->figure[i][j] == 1) {
        if (field[i + current_figure->y][j + current_figure->x] == 1) {
          is_collide = TRUE;
          break;
        }
      }
    }
  }

  return is_collide;
}

void remove_line(int **field, int line_to_remove) {
  for (int i = line_to_remove; i > 0; i--) {
    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      field[i][j] = field[i - 1][j];
    }
  }
}

void process_lines(game_info_t *current_state, figure_t *current_figure) {
  int removed_lines_count = 0;

  for (int i = current_figure->y + FIGURE_ROWS; i >= current_figure->y; i--) {
    if (i > FIELD_LENGTH - 2) {
      continue;
    }

    bool is_full = TRUE;

    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      if (current_state->field[i][j] == 0) {
        is_full = FALSE;
        break;
      }
    }

    if (is_full) {
      remove_line(current_state->field, i);
      removed_lines_count++;
      current_state->score += 100 * pow(2, removed_lines_count - 1);
      i++;
    }
  }

  if (removed_lines_count) {
    current_state->level = (current_state->score < MAX_LEVEL_SCORE)
                               ? 1 + (current_state->score / POINTS_PER_LEVEL)
                               : MAX_LEVEL;

    if (current_state->score > current_state->high_score) {
      current_state->high_score = current_state->score;
      write_high_score_to_file(HIGH_SCORE_TETRIS_FILE_PATH,
                               current_state->high_score);
    }
  }
}

bool is_gameover(game_info_t *current_state) {
  bool is_gameover = FALSE;

  for (int j = 1; j < FIELD_WIDTH - 1; j++) {
    if (current_state->field[HIGHEST_GAME_LINE][j] == 1) {
      is_gameover = TRUE;
    }
  }

  return is_gameover;
}

void clean_field(int **field) {
  for (int i = 0; i < FIELD_LENGTH - 1; i++) {
    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      field[i][j] = 0;
    }
  }
}

void stats_init(game_info_t *current_state) {
  current_state->field = (int **)calloc(FIELD_LENGTH, sizeof(int *));

  if (current_state->field) {
    for (int i = 0; i < FIELD_LENGTH; i++) {
      current_state->field[i] = (int *)calloc(FIELD_WIDTH, sizeof(int));
    }

    for (int i = 0; i < FIELD_LENGTH; i++) {
      for (int j = 0; j < FIELD_WIDTH && current_state->field[i]; j++) {
        if (i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
          current_state->field[i][j] = 1;
        }
      }
    }
  }

  current_state->next = (int **)calloc(4, sizeof(int *));

  if (current_state->next) {
    for (int i = 0; i < FIGURE_ROWS; i++) {
      current_state->next[i] = (int *)calloc(4, sizeof(int));
    }
  }

  current_state->score = 0;
  current_state->level = 1;
  current_state->speed = 1;
  current_state->pause = FALSE;
  current_state->high_score = 0;
}

void stats_delete(game_info_t *current_state) {
  for (int i = 0; i < FIELD_LENGTH && current_state->field[i]; i++) {
    free(current_state->field[i]);
    current_state->field[i] = NULL;
  }

  if (current_state->field) {
    free(current_state->field);
    current_state->field = NULL;
  }

  for (int i = 0; i < FIGURE_ROWS && current_state->next[i]; i++) {
    free(current_state->next[i]);
    current_state->next[i] = NULL;
  }

  if (current_state->next) {
    free(current_state->next);
    current_state->next = NULL;
  }

  current_state->score = 0;
  current_state->high_score = 0;
  current_state->level = 0;
  current_state->speed = 0;
  current_state->pause = FALSE;
}
