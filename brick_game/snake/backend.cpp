#include "../../inc/snake/backend.h"

void s21::Field::statsInit() {
  current_state->field = new int *[FIELD_LENGTH]();

  for (int i = 0; i < FIELD_LENGTH; i++) {
    current_state->field[i] = new int[FIELD_WIDTH]();
  }

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
        current_state->field[i][j] = 1;
      }
    }
  }

  current_state->next = nullptr;
  current_state->score = 0;
  current_state->level = 1;
  current_state->speed = 1;
  current_state->pause = false;
  current_state->high_score = 0;
}

void s21::Field::statsDelete() {
  for (int i = 0; i < FIELD_LENGTH; i++) {
    delete[] current_state->field[i];
    current_state->field[i] = nullptr;
  }

  delete[] current_state->field;
  current_state->field = nullptr;

  current_state->score = 0;
  current_state->high_score = 0;
  current_state->level = 0;
  current_state->speed = 0;
  current_state->pause = false;
}

void s21::Snake::move() {
  Direction head_direction = direction.back();
  movePoint(x_head, y_head, head_direction);

  direction.push(head_direction);

  if (!eat_apple) {
    Direction tail_direction = direction.front();
    movePoint(x_tail, y_tail, tail_direction);

    direction.pop();
  } else {
    eat_apple = false;
  }
}

bool s21::Snake::turn(user_action_t user_action, bool &speed_up) {
  bool was_turned = false;
  speed_up = false;

  switch (user_action) {
    case LEFT:
      if (direction.back() != Direction::RIGHT) {
        if (direction.back() == Direction::LEFT) {
          speed_up = true;
        } else {
          direction.back() = Direction::LEFT;
          was_turned = true;
        }
      }
      break;
    case RIGHT:
      if (direction.back() != Direction::LEFT) {
        if (direction.back() == Direction::RIGHT) {
          speed_up = true;
        } else {
          direction.back() = Direction::RIGHT;
          was_turned = true;
        }
      }
      break;
    case UP:
      if (direction.back() != Direction::DOWN) {
        if (direction.back() == Direction::UP) {
          speed_up = true;
        } else {
          direction.back() = Direction::UP;
          was_turned = true;
        }
      }

      break;
    case DOWN:
      if (direction.back() != Direction::UP) {
        if (direction.back() == Direction::DOWN) {
          speed_up = true;
        } else {
          direction.back() = Direction::DOWN;
          was_turned = true;
        }
      }
      break;
    case ACTION:
      speed_up = true;
    default:
      break;
  }

  return was_turned;
}

int s21::Snake::getXHead() { return x_head; }
int s21::Snake::getYHead() { return y_head; }
int s21::Snake::getXTail() { return x_tail; }
int s21::Snake::getYTail() { return y_tail; }

int s21::Apple::getX() { return x; }
int s21::Apple::getY() { return y; }

void s21::Field::setPoint(int x, int y) {
  if (x > 0 && x < FIELD_WIDTH - 1 && y > 0 && y < FIELD_LENGTH - 1) {
    current_state->field[y][x] = 1;
  }
}

void s21::Field::removePoint(int x, int y) {
  if (x > 0 && x < FIELD_WIDTH - 1 && y > 0 && y < FIELD_LENGTH - 1) {
    current_state->field[y][x] = 0;
  }
}

double s21::Field::gameTimer() {
  return 1 / (1 + (current_state->level - 1) * (SPEED_SNAKE_COEFFICIENT));
}

void s21::Snake::movePoint(int &x, int &y, Direction point_direction) {
  switch (point_direction) {
    case Direction::UP:
      --y;
      break;
    case Direction::DOWN:
      ++y;
      break;
    case Direction::LEFT:
      --x;
      break;
    case Direction::RIGHT:
      ++x;
      break;
  }
}

void s21::Field::initSnake(int body_length, int start_x, int start_y) {
  for (int i = 0; i < body_length; ++i) {
    setPoint(start_x, start_y + i);
  }
}

bool s21::Field::isCollide(int x, int y) { return current_state->field[y][x]; }

void s21::Field::clean() {
  for (int i = 1; i < FIELD_LENGTH - 1; i++) {
    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      current_state->field[i][j] = 0;
    }
  }

  current_state->level = 1;
  current_state->score = 0;
}

void s21::Snake::reset() {
  x_head = START_X_HEAD;
  y_head = START_Y_HEAD;
  x_tail = START_X_TAIL;
  y_tail = START_Y_TAIL;

  eat_apple = false;

  while (!direction.empty()) {
    direction.pop();
  }

  for (int i = 0; i < BODY_LENGTH; ++i) {
    direction.push(Direction::UP);
  }
}

void s21::Apple::spawn() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<int> x_dist(1, FIELD_WIDTH - 2);
  static std::uniform_int_distribution<int> y_dist(1, FIELD_LENGTH - 2);

  x = x_dist(gen);
  y = y_dist(gen);
}

void s21::Snake::foundApple() { eat_apple = true; }

void s21::Field::statsUpdate() {
  current_state->score += POINTS_PER_APPLE;

  if (current_state->score % POINTS_PER_SNAKE_LEVEL == 0 &&
      current_state->level < MAX_LEVEL) {
    current_state->level++;
  }

  if (current_state->score > current_state->high_score) {
    current_state->high_score = current_state->score;
    writeHighScoreToFile(HIGH_SCORE_SNAKE_FILE_PATH);
  }
}

void s21::Field::readHighScoreFromFile(const char *file_path) {
  int high_score_from_file = 0;

  std::ifstream in;
  in.open(file_path);

  if (in.is_open()) {
    in >> high_score_from_file;
    in.close();
  }

  current_state->high_score = high_score_from_file;
}

void s21::Field::writeHighScoreToFile(const char *file_path) {
  std::ofstream out;
  out.open(file_path);

  if (out.is_open()) {
    out << current_state->high_score;
    out.close();
  }
}

int s21::Snake::length() { return direction.size() + (eat_apple ? 1 : 0); }

bool s21::Snake::isHungry() { return !eat_apple; }

void s21::Apple::setX(int x) {
  if (x >= 0) {
    this->x = x;
  }
}

void s21::Apple::setY(int y) {
  if (y >= 0) {
    this->y = y;
  }
}

void s21::Snake::setXHead(int x_head) {
  if (x_head >= 0) {
    this->x_head = x_head;
  }
}

void s21::Snake::setYHead(int y_head) {
  if (y_head >= 0) {
    this->y_head = y_head;
  }
}

void s21::Snake::setXTail(int x_tail) {
  if (x_tail >= 0) {
    this->x_tail = x_tail;
  }
}

void s21::Snake::setYTail(int y_tail) {
  if (y_tail >= 0) {
    this->y_tail = y_tail;
  }
}

s21::Direction s21::Snake::getHeadDirection() { return direction.back(); }
s21::Direction s21::Snake::getTailDirection() { return direction.front(); }

void s21::Snake::setHeadDirection(Direction head_direction) {
  direction.back() = head_direction;
}

void s21::Snake::setTailDirection(Direction tail_direction) {
  direction.front() = tail_direction;
}
