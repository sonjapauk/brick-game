#include <gtest/gtest.h>

#include "../inc/brick_game.h"

TEST(FieldTest, StatsInit) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  EXPECT_NE(state.field, nullptr);

  for (int i = 0; i < FIELD_LENGTH; i++) {
    EXPECT_NE(state.field[i], nullptr);
  }

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
        EXPECT_EQ(state.field[i][j], 1);
      } else {
        EXPECT_EQ(state.field[i][j], 0);
      }
    }
  }

  EXPECT_EQ(state.score, 0);
  EXPECT_EQ(state.level, 1);
  EXPECT_EQ(state.speed, 1);
  EXPECT_EQ(state.pause, false);
  EXPECT_EQ(state.high_score, 0);

  field.statsDelete();
}

TEST(FieldTest, StatsDelete) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();
  field.statsDelete();

  EXPECT_EQ(state.field, nullptr);

  EXPECT_EQ(state.score, 0);
  EXPECT_EQ(state.level, 0);
  EXPECT_EQ(state.speed, 0);
  EXPECT_EQ(state.pause, false);
}

TEST(FieldTest, StatsUpdate) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  field.statsUpdate();

  EXPECT_EQ(state.score, POINTS_PER_APPLE);

  state.score = POINTS_PER_LEVEL - 1;

  field.statsUpdate();

  EXPECT_EQ(state.score, POINTS_PER_LEVEL);
  EXPECT_EQ(state.level, 2);
  EXPECT_EQ(state.speed, 1);
  EXPECT_EQ(state.pause, false);

  field.statsDelete();
}

TEST(FieldTest, SetPointValid) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  int x = 5;
  int y = 5;

  field.setPoint(x, y);

  EXPECT_EQ(state.field[y][x], 1);

  field.statsDelete();
}

TEST(FieldTest, SetPointNonValidX) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  int x = 0;
  int y = 5;

  field.setPoint(x, y);

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
        EXPECT_EQ(state.field[i][j], 1);
      } else {
        EXPECT_EQ(state.field[i][j], 0);
      }
    }
  }

  x = FIELD_WIDTH - 1;

  field.setPoint(x, y);

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
        EXPECT_EQ(state.field[i][j], 1);
      } else {
        EXPECT_EQ(state.field[i][j], 0);
      }
    }
  }

  field.statsDelete();
}

TEST(FieldTest, SetPointNonValidY) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  int x = 5;
  int y = 0;

  field.setPoint(x, y);

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
        EXPECT_EQ(state.field[i][j], 1);
      } else {
        EXPECT_EQ(state.field[i][j], 0);
      }
    }
  }

  y = FIELD_LENGTH - 1;

  field.setPoint(x, y);

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
        EXPECT_EQ(state.field[i][j], 1);
      } else {
        EXPECT_EQ(state.field[i][j], 0);
      }
    }
  }

  field.statsDelete();
}

TEST(FieldTest, RemovePoint) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  int x = 5;
  int y = 5;

  field.setPoint(x, y);

  EXPECT_EQ(state.field[y][x], 1);

  field.removePoint(x, y);

  EXPECT_EQ(state.field[y][x], 0);

  field.statsDelete();
}

TEST(FieldTest, Clean) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  for (int i = 0; i < FIELD_LENGTH; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      field.setPoint(j, i);
    }
  }

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      EXPECT_EQ(state.field[i][j], 1);
    }
  }

  field.clean();

  for (int i = 0; i < FIELD_LENGTH; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 || j == FIELD_WIDTH - 1) {
        EXPECT_EQ(state.field[i][j], 1);
      } else {
        EXPECT_EQ(state.field[i][j], 0);
      }
    }
  }

  field.statsDelete();
}

TEST(FieldTest, IsCollide) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  int x = 5;
  int y = 5;

  field.setPoint(x, y);

  EXPECT_TRUE(field.isCollide(x, y));

  field.removePoint(x, y);

  EXPECT_FALSE(field.isCollide(x, y));

  field.statsDelete();
}

TEST(FieldTest, InitSnake) {
  game_info_t state{};

  s21::Field field(&state);

  field.statsInit();

  int x = 5;
  int y = 10;

  field.initSnake(BODY_LENGTH, x, y);

  for (int i = y; i < y + BODY_LENGTH; i++) {
    EXPECT_EQ(state.field[i][x], 1);
  }

  field.statsDelete();
}

TEST(FieldTest, GameTimer) {
  game_info_t state{};
  s21::Field field(&state);

  state.level = 1;
  double time1 = field.gameTimer();

  state.level = 10;
  double time10 = field.gameTimer();

  EXPECT_TRUE(time10 > 0);
  EXPECT_TRUE(time1 > time10);
}

TEST(FieldTest, ScoreKeeper) {
  game_info_t state{};
  s21::Field field(&state);

  state.high_score = 777;
  field.writeHighScoreToFile("test.txt");

  state.high_score = 0;

  EXPECT_EQ(state.high_score, 0);

  field.readHighScoreFromFile("test.txt");
  EXPECT_EQ(state.high_score, 777);
}

TEST(FieldTest, NotExist) {
  game_info_t state{};
  s21::Field field(&state);

  EXPECT_EQ(state.high_score, 0);

  field.readHighScoreFromFile("not_exist.txt");
  EXPECT_EQ(state.high_score, 0);
}

TEST(SnakeTest, GetterHead) {
  s21::Snake snake;
  snake.setXHead(3);
  snake.setYHead(7);

  EXPECT_EQ(snake.getXHead(), 3);
  EXPECT_EQ(snake.getYHead(), 7);
}

TEST(SnakeTest, GetterTail) {
  s21::Snake snake;
  snake.setXTail(1);
  snake.setYTail(2);

  EXPECT_EQ(snake.getXTail(), 1);
  EXPECT_EQ(snake.getYTail(), 2);
}

TEST(SnakeTest, Length) {
  s21::Snake snake;

  EXPECT_EQ(snake.length(), BODY_LENGTH);
}

TEST(SnakeTest, IsHungry) {
  s21::Snake snake;

  EXPECT_TRUE(snake.isHungry());
}

TEST(SnakeTest, IsNotHungry) {
  s21::Snake snake;

  snake.foundApple();

  EXPECT_FALSE(snake.isHungry());
}

TEST(SnakeTest, LengthEaten) {
  s21::Snake snake;

  snake.foundApple();

  EXPECT_EQ(snake.length(), BODY_LENGTH + 1);
}

TEST(SnakeTest, SetterHead) {
  s21::Snake snake;
  snake.setXHead(3);
  snake.setYHead(7);

  snake.setXHead(-2);
  snake.setYHead(8);

  EXPECT_EQ(snake.getXHead(), 3);
  EXPECT_EQ(snake.getYHead(), 8);
}

TEST(SnakeTest, SetterTail) {
  s21::Snake snake;
  snake.setXTail(1);
  snake.setYTail(2);

  snake.setXTail(6);
  snake.setYTail(-12);

  EXPECT_EQ(snake.getXTail(), 6);
  EXPECT_EQ(snake.getYTail(), 2);
}

TEST(SnakeTest, SetAndGetHeadDirection) {
  s21::Snake snake;
  snake.setHeadDirection(s21::Direction::RIGHT);

  EXPECT_EQ(snake.getHeadDirection(), s21::Direction::RIGHT);
}

TEST(SnakeTest, SetAndGetTailDirection) {
  s21::Snake snake;
  snake.setTailDirection(s21::Direction::LEFT);

  EXPECT_EQ(snake.getTailDirection(), s21::Direction::LEFT);
}

TEST(SnakeTest, HeadAndTailIndependent) {
  s21::Snake snake;
  snake.setHeadDirection(s21::Direction::UP);
  snake.setTailDirection(s21::Direction::DOWN);

  EXPECT_EQ(snake.getHeadDirection(), s21::Direction::UP);
  EXPECT_EQ(snake.getTailDirection(), s21::Direction::DOWN);
}

TEST(SnakeTest, MoveIsHungryUp) {
  s21::Snake snake;

  int x_head_init = snake.getXHead();
  int y_head_init = snake.getYHead();

  int x_tail_init = snake.getXTail();
  int y_tail_init = snake.getYTail();

  int length_init = snake.length();

  s21::Direction head_init = s21::Direction::UP;
  snake.setHeadDirection(head_init);

  s21::Direction tail_init = s21::Direction::UP;
  snake.setTailDirection(tail_init);

  snake.move();

  int x_head = snake.getXHead();
  int y_head = snake.getYHead();

  int x_tail = snake.getXTail();
  int y_tail = snake.getYTail();

  int length = snake.length();

  s21::Direction head = snake.getHeadDirection();

  EXPECT_EQ(x_head - x_head_init, 0);
  EXPECT_EQ(x_tail - x_tail_init, 0);
  EXPECT_EQ(y_head - y_head_init, -1);
  EXPECT_EQ(y_tail - y_tail_init, -1);

  EXPECT_EQ(length, length_init);
  EXPECT_EQ(head, head_init);
}

TEST(SnakeTest, MoveEatAppleUp) {
  s21::Snake snake;

  int length_init = snake.length();

  snake.foundApple();
  EXPECT_FALSE(snake.isHungry());

  int x_head_init = snake.getXHead();
  int y_head_init = snake.getYHead();

  int x_tail_init = snake.getXTail();
  int y_tail_init = snake.getYTail();

  s21::Direction head_init = s21::Direction::UP;
  snake.setHeadDirection(head_init);

  s21::Direction tail_init = s21::Direction::UP;
  snake.setTailDirection(tail_init);

  snake.move();

  int x_head = snake.getXHead();
  int y_head = snake.getYHead();

  int x_tail = snake.getXTail();
  int y_tail = snake.getYTail();

  int length = snake.length();

  s21::Direction head = snake.getHeadDirection();
  s21::Direction tail = snake.getTailDirection();

  EXPECT_EQ(x_head - x_head_init, 0);
  EXPECT_EQ(x_tail - x_tail_init, 0);
  EXPECT_EQ(y_head - y_head_init, -1);
  EXPECT_EQ(y_tail - y_tail_init, 0);

  EXPECT_EQ(length, length_init + 1);
  EXPECT_EQ(head, head_init);
  EXPECT_EQ(tail, tail_init);
}

TEST(SnakeTest, MoveLeft) {
  s21::Snake snake;

  int x_head_init = snake.getXHead();
  int y_head_init = snake.getYHead();

  s21::Direction head_init = s21::Direction::LEFT;
  snake.setHeadDirection(head_init);

  snake.move();

  int x_head = snake.getXHead();
  int y_head = snake.getYHead();

  s21::Direction head = snake.getHeadDirection();

  EXPECT_EQ(x_head - x_head_init, -1);
  EXPECT_EQ(y_head - y_head_init, 0);

  EXPECT_EQ(head, head_init);
}

TEST(SnakeTest, MoveRight) {
  s21::Snake snake;

  int x_head_init = snake.getXHead();
  int y_head_init = snake.getYHead();

  s21::Direction head_init = s21::Direction::RIGHT;
  snake.setHeadDirection(head_init);

  snake.move();

  int x_head = snake.getXHead();
  int y_head = snake.getYHead();

  s21::Direction head = snake.getHeadDirection();

  EXPECT_EQ(x_head - x_head_init, 1);
  EXPECT_EQ(y_head - y_head_init, 0);

  EXPECT_EQ(head, head_init);
}

TEST(SnakeTest, MoveDown) {
  s21::Snake snake;

  int x_head_init = snake.getXHead();
  int y_head_init = snake.getYHead();

  s21::Direction head_init = s21::Direction::DOWN;
  snake.setHeadDirection(head_init);

  snake.move();

  int x_head = snake.getXHead();
  int y_head = snake.getYHead();

  s21::Direction head = snake.getHeadDirection();

  EXPECT_EQ(x_head - x_head_init, 0);
  EXPECT_EQ(y_head - y_head_init, 1);

  EXPECT_EQ(head, head_init);
}

TEST(SnakeTest, TurnLeft) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::UP;
  snake.setHeadDirection(head_init);

  EXPECT_TRUE(snake.turn(LEFT, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);

  EXPECT_FALSE(snake.turn(LEFT, speed_up));

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);

  EXPECT_FALSE(snake.turn(RIGHT, speed_up));
  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);
}

TEST(SnakeTest, TurnRight) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::DOWN;
  snake.setHeadDirection(head_init);

  EXPECT_TRUE(snake.turn(RIGHT, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);

  EXPECT_FALSE(snake.turn(RIGHT, speed_up));

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);

  EXPECT_FALSE(snake.turn(LEFT, speed_up));
  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);
}

TEST(SnakeTest, TurnUp) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::LEFT;
  snake.setHeadDirection(head_init);

  EXPECT_TRUE(snake.turn(UP, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);

  EXPECT_FALSE(snake.turn(UP, speed_up));

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);

  EXPECT_FALSE(snake.turn(DOWN, speed_up));
  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);
}

TEST(SnakeTest, TurnDown) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::RIGHT;
  snake.setHeadDirection(head_init);

  EXPECT_TRUE(snake.turn(DOWN, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);

  EXPECT_FALSE(snake.turn(DOWN, speed_up));

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);

  EXPECT_FALSE(snake.turn(UP, speed_up));
  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);
}

TEST(SnakeTest, ActionFromRight) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::RIGHT;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn(ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);
}

TEST(SnakeTest, ActionFromLeft) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::LEFT;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn(ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);
}

TEST(SnakeTest, ActionFromUp) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::UP;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn(ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);
}

TEST(SnakeTest, ActionFromDown) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::DOWN;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn(ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_TRUE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);
}

TEST(SnakeTest, NoActionFromUp) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::UP;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn((user_action_t)NO_ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);

  EXPECT_FALSE(snake.turn(START, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);

  EXPECT_FALSE(snake.turn(TERMINATE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);

  EXPECT_FALSE(snake.turn(PAUSE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::UP);
}

TEST(SnakeTest, NoActionFromDown) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::DOWN;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn((user_action_t)NO_ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);

  EXPECT_FALSE(snake.turn(START, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);

  EXPECT_FALSE(snake.turn(TERMINATE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);

  EXPECT_FALSE(snake.turn(PAUSE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::DOWN);
}

TEST(SnakeTest, NoActionFromLeft) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::LEFT;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn((user_action_t)NO_ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);

  EXPECT_FALSE(snake.turn(START, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);

  EXPECT_FALSE(snake.turn(TERMINATE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);

  EXPECT_FALSE(snake.turn(PAUSE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::LEFT);
}

TEST(SnakeTest, NoActionFromRight) {
  s21::Snake snake;
  bool speed_up;

  s21::Direction head_init = s21::Direction::RIGHT;
  snake.setHeadDirection(head_init);

  EXPECT_FALSE(snake.turn((user_action_t)NO_ACTION, speed_up));

  s21::Direction head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);

  EXPECT_FALSE(snake.turn(START, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);

  EXPECT_FALSE(snake.turn(TERMINATE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);

  EXPECT_FALSE(snake.turn(PAUSE, speed_up));

  head = snake.getHeadDirection();

  EXPECT_FALSE(speed_up);
  EXPECT_EQ(head, s21::Direction::RIGHT);
}

TEST(SnakeTest, Reset) {
  s21::Snake snake;

  s21::Direction head_init = s21::Direction::LEFT;
  snake.setHeadDirection(head_init);

  snake.move();

  head_init = s21::Direction::DOWN;
  snake.setHeadDirection(head_init);

  s21::Direction tail_init = s21::Direction::RIGHT;
  snake.setTailDirection(tail_init);

  snake.move();

  snake.foundApple();

  tail_init = s21::Direction::RIGHT;
  snake.setTailDirection(tail_init);

  int x_head = snake.getXHead();
  int y_head = snake.getYHead();

  int x_tail = snake.getXTail();
  int y_tail = snake.getYTail();

  int length = snake.length();

  s21::Direction head = snake.getHeadDirection();
  s21::Direction tail = snake.getTailDirection();

  EXPECT_NE(x_head, START_X_HEAD);
  EXPECT_NE(y_head, START_Y_HEAD);
  EXPECT_NE(x_tail, START_X_TAIL);
  EXPECT_NE(y_tail, START_Y_TAIL);
  EXPECT_NE(length, BODY_LENGTH);
  EXPECT_NE(head, s21::Direction::UP);
  EXPECT_NE(tail, s21::Direction::UP);
  EXPECT_FALSE(snake.isHungry());

  snake.reset();

  x_head = snake.getXHead();
  y_head = snake.getYHead();

  x_tail = snake.getXTail();
  y_tail = snake.getYTail();

  length = snake.length();

  head = snake.getHeadDirection();
  tail = snake.getTailDirection();

  EXPECT_EQ(x_head, START_X_HEAD);
  EXPECT_EQ(y_head, START_Y_HEAD);
  EXPECT_EQ(x_tail, START_X_TAIL);
  EXPECT_EQ(y_tail, START_Y_TAIL);
  EXPECT_EQ(length, BODY_LENGTH);
  EXPECT_EQ(head, s21::Direction::UP);
  EXPECT_EQ(tail, s21::Direction::UP);
  EXPECT_TRUE(snake.isHungry());
}

TEST(AppleTest, Setter) {
  s21::Apple apple;
  apple.setX(4);
  apple.setY(9);

  apple.setX(-7);
  apple.setY(-9);

  EXPECT_EQ(apple.getX(), 4);
  EXPECT_EQ(apple.getY(), 9);
}

TEST(AppleTest, Getter) {
  s21::Apple apple;
  apple.setX(4);
  apple.setY(9);

  EXPECT_EQ(apple.getX(), 4);
  EXPECT_EQ(apple.getY(), 9);
}

TEST(AppleTest, Spawn) {
  s21::Apple apple;
  apple.setX(400);
  apple.setY(900);

  apple.spawn();

  int new_x = apple.getX();
  int new_y = apple.getY();

  EXPECT_TRUE(new_x >= 1 && new_x < FIELD_WIDTH - 1);
  EXPECT_TRUE(new_y >= 1 && new_x < FIELD_WIDTH - 1);
}