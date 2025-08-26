#include <gtest/gtest.h>

#include "../inc/brick_game.h"

TEST(FSMTest, FromInitToStart) {
  game_info_t state{};

  s21::SnakeFSM fsm = s21::SnakeFSM(&state);
  user_action_t action = (user_action_t)NO_ACTION;

  s21::SnakeState init_state = s21::SnakeState::INIT;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::START;

  EXPECT_EQ(current_state, expected_state);

  fsm.setSnakeState(s21::SnakeState::EXIT);
  fsm.fsm(action);
}

TEST(FSMTest, FromExitToInit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::EXIT;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromStartToStart) {
  game_info_t state{};
  s21::SnakeFSM fsm = s21::SnakeFSM(&state);
  user_action_t action = (user_action_t)NO_ACTION;

  s21::SnakeState init_state = s21::SnakeState::START;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::START;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromStartToSpawnApple) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = START;
  s21::SnakeState init_state = s21::SnakeState::START;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::SPAWN_APPLE;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromStartToExit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = TERMINATE;
  s21::SnakeState init_state = s21::SnakeState::START;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromSpawnAppleToTurning) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::SPAWN_APPLE;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::TURNING;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromTurningToMoving) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::TURNING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);
  sleep(1);
  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::MOVING;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromTurningToMovingSpeedUp) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = ACTION;
  s21::SnakeState init_state = s21::SnakeState::TURNING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::MOVING;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromTurningToMovingTurned) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = LEFT;
  s21::SnakeState init_state = s21::SnakeState::TURNING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::MOVING;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromTurningToTurning) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::TURNING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::TURNING;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromTurningToExit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = TERMINATE;
  s21::SnakeState init_state = s21::SnakeState::TURNING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromMovingToCollisionWall) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = ACTION;
  s21::SnakeState init_state = s21::SnakeState::MOVING;
  fsm.setSnakeState(init_state);

  for (int i = 0; i < (FIELD_LENGTH - START_Y_HEAD - 2) * 2 - 1; i++) {
    fsm.fsm(action);
  }

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::COLLISION;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromMovingToCollisionApple) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::Snake snake{};

  field.setPoint(snake.getXHead(), snake.getYHead());
  field.setPoint(snake.getXHead(), snake.getYHead() - 1);

  s21::SnakeFSM fsm(field, snake);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::MOVING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::COLLISION;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromMovingToTurning) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::MOVING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::TURNING;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromMovingToExit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = TERMINATE;
  s21::SnakeState init_state = s21::SnakeState::MOVING;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromCollisionToGameover) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = ACTION;
  s21::SnakeState init_state = s21::SnakeState::MOVING;
  fsm.setSnakeState(init_state);

  for (int i = 0; i < (FIELD_LENGTH - START_Y_HEAD - 2) * 2; i++) {
    fsm.fsm(action);
  }

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::GAMEOVER;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromCollisionToEatApple) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::Snake snake{};
  s21::Apple apple{};
  apple.setX(snake.getXHead());
  apple.setY(snake.getYHead());

  s21::SnakeFSM fsm(field, snake, apple);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::COLLISION;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::EAT_APPLE;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromCollisionToExit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = TERMINATE;
  s21::SnakeState init_state = s21::SnakeState::COLLISION;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromEatAppleToSpawnApple) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::EAT_APPLE;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::SPAWN_APPLE;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromEatAppleToWin) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::Snake snake{};

  for (int i = 0; i < WIN_SCORE - BODY_LENGTH - 1; ++i) {
    snake.foundApple();
    snake.move();
  }

  s21::SnakeFSM fsm(field, snake);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::EAT_APPLE;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::WIN;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromEatAppleToExit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = TERMINATE;
  s21::SnakeState init_state = s21::SnakeState::EAT_APPLE;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromWinToStart) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::SnakeFSM fsm(field);

  user_action_t action = START;
  s21::SnakeState init_state = s21::SnakeState::WIN;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::START;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromWinToWin) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::WIN;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::WIN;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromWinToExit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = TERMINATE;
  s21::SnakeState init_state = s21::SnakeState::WIN;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(FSMTest, FromGameoverToStart) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::SnakeFSM fsm(field);

  user_action_t action = START;
  s21::SnakeState init_state = s21::SnakeState::GAMEOVER;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::START;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromGameoverToGameover) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();

  s21::SnakeFSM fsm(field);

  user_action_t action = (user_action_t)NO_ACTION;
  s21::SnakeState init_state = s21::SnakeState::GAMEOVER;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::GAMEOVER;

  EXPECT_EQ(current_state, expected_state);

  field.statsDelete();
}

TEST(FSMTest, FromGameoverToExit) {
  game_info_t state{};
  s21::Field field(&state);
  field.statsInit();
  s21::SnakeFSM fsm(field);

  user_action_t action = TERMINATE;
  s21::SnakeState init_state = s21::SnakeState::GAMEOVER;
  fsm.setSnakeState(init_state);

  fsm.fsm(action);

  s21::SnakeState current_state = fsm.getSnakeState();
  s21::SnakeState expected_state = s21::SnakeState::INIT;

  EXPECT_EQ(current_state, expected_state);
}

TEST(GameStatusTest, StartStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState init_state = s21::SnakeState::START;
  fsm.setSnakeState(init_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = START_GAME;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, GameoverStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState gameover_state = s21::SnakeState::GAMEOVER;
  fsm.setSnakeState(gameover_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = GAMEOVER_GAME;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, InitStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState init_state = s21::SnakeState::INIT;
  fsm.setSnakeState(init_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = SERVICE;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, ExitStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState exit_state = s21::SnakeState::EXIT;
  fsm.setSnakeState(exit_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = SERVICE;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, WinStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState win_state = s21::SnakeState::WIN;
  fsm.setSnakeState(win_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = WIN;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, SpawnStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState playing_state = s21::SnakeState::SPAWN_APPLE;
  fsm.setSnakeState(playing_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = PLAYING;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, TurningStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState playing_state = s21::SnakeState::TURNING;
  fsm.setSnakeState(playing_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = PLAYING;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, MovingStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState playing_state = s21::SnakeState::MOVING;
  fsm.setSnakeState(playing_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = PLAYING;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, CollisionStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState playing_state = s21::SnakeState::COLLISION;
  fsm.setSnakeState(playing_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = PLAYING;

  EXPECT_EQ(current_status, expected_status);
}

TEST(GameStatusTest, EatAppleStatus) {
  game_info_t state{};
  s21::SnakeFSM fsm(&state);

  s21::SnakeState playing_state = s21::SnakeState::EAT_APPLE;
  fsm.setSnakeState(playing_state);

  game_status_t current_status = fsm.getGameStatus();
  game_status_t expected_status = PLAYING;

  EXPECT_EQ(current_status, expected_status);
}