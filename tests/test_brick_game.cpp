#include <gtest/gtest.h>

#include "../inc/brick_game.h"

TEST(MenuTest, MenuTetrisUp) {
  menu_status_t menu_status = MENU_TETRIS;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(UP);

  EXPECT_EQ(menu_status, MENU_TETRIS);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuSnakeUp) {
  menu_status_t menu_status = MENU_SNAKE;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(UP);

  EXPECT_EQ(menu_status, MENU_TETRIS);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuExitUp) {
  menu_status_t menu_status = MENU_EXIT;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(UP);

  EXPECT_EQ(menu_status, MENU_SNAKE);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuTetrisDown) {
  menu_status_t menu_status = MENU_TETRIS;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(DOWN);

  EXPECT_EQ(menu_status, MENU_SNAKE);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuSnakeDown) {
  menu_status_t menu_status = MENU_SNAKE;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(DOWN);

  EXPECT_EQ(menu_status, MENU_EXIT);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuExitDown) {
  menu_status_t menu_status = MENU_EXIT;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(DOWN);

  EXPECT_EQ(menu_status, MENU_EXIT);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuStartTetris) {
  menu_status_t menu_status = MENU_TETRIS;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(START);

  EXPECT_EQ(bg_status, TETRIS);
}

TEST(MenuTest, MenuStartSnake) {
  menu_status_t menu_status = MENU_SNAKE;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(START);

  EXPECT_EQ(bg_status, SNAKE);
}

TEST(MenuTest, MenuStartExit) {
  menu_status_t menu_status = MENU_EXIT;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(START);

  EXPECT_EQ(bg_status, EXIT);
}

TEST(MenuTest, MenuTerminateFromTetris) {
  menu_status_t menu_status = MENU_TETRIS;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(TERMINATE);

  EXPECT_EQ(bg_status, EXIT);
}

TEST(MenuTest, MenuTerminateFromSnake) {
  menu_status_t menu_status = MENU_SNAKE;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(TERMINATE);

  EXPECT_EQ(bg_status, EXIT);
}

TEST(MenuTest, MenuTerminateFromExit) {
  menu_status_t menu_status = MENU_EXIT;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(TERMINATE);

  EXPECT_EQ(bg_status, EXIT);
}

TEST(MenuTest, MenuLeftActionDoesNothing) {
  menu_status_t menu_status = MENU_SNAKE;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(LEFT);

  EXPECT_EQ(menu_status, MENU_SNAKE);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuRightActionDoesNothing) {
  menu_status_t menu_status = MENU_TETRIS;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu(RIGHT);

  EXPECT_EQ(menu_status, MENU_TETRIS);
  EXPECT_EQ(bg_status, MENU);
}

TEST(MenuTest, MenuNoneActionDoesNothing) {
  menu_status_t menu_status = MENU_EXIT;
  s21::Menu menu(menu_status);

  brick_game_status_t bg_status = menu.menu((user_action_t)NO_ACTION);

  EXPECT_EQ(menu_status, MENU_EXIT);
  EXPECT_EQ(bg_status, MENU);
}

TEST(BrickGameTest, UpdateStatuses) {
  s21::GameData data;
  menu_status_t &menu_status = data.getMenuStatus();
  brick_game_status_t &bg_status = data.getStatus();

  menu_status = MENU_TETRIS;
  bg_status = MENU;

  s21::BrickGame bg(data);

  bg.updateStatuses(DOWN);

  EXPECT_EQ(menu_status, MENU_SNAKE);
  EXPECT_EQ(bg_status, MENU);
}

TEST(BrickGameTest, UpdateStatusesTerminate) {
  s21::GameData data;
  menu_status_t &menu_status = data.getMenuStatus();
  brick_game_status_t &bg_status = data.getStatus();

  menu_status = MENU_SNAKE;
  bg_status = SNAKE;

  s21::BrickGame bg(data);

  bg.updateStatuses(TERMINATE);

  EXPECT_EQ(menu_status, MENU_SNAKE);
  EXPECT_EQ(bg_status, MENU);
}

TEST(BrickGameTest, UpdateStatusesExit) {
  s21::GameData data;
  menu_status_t &menu_status = data.getMenuStatus();
  brick_game_status_t &bg_status = data.getStatus();

  menu_status = MENU_SNAKE;
  bg_status = EXIT;

  s21::BrickGame bg(data);

  bg.updateStatuses(START);

  EXPECT_EQ(menu_status, MENU_SNAKE);
  EXPECT_EQ(bg_status, EXIT);
}

TEST(GameTest, Pause) {
  game_info_t state{};
  game_status_t game_status = PLAYING;

  s21::Game game(state, game_status);

  game.userInput(PAUSE, false);
  game.updateCurrentState();

  EXPECT_TRUE(state.pause);
}

TEST(GameTest, PauseAndTerminate) {
  game_info_t state{};
  game_status_t game_status = PLAYING;

  s21::Game game(state, game_status);

  game.setFsm(SNAKE);

  game.userInput(START, false);
  game.updateCurrentState();

  game.userInput(PAUSE, false);
  game.updateCurrentState();

  game.userInput(TERMINATE, false);
  game.updateCurrentState();

  EXPECT_EQ(game_status, SERVICE);
}

TEST(GameTest, NoFSM) {
  game_info_t state{};
  game_status_t game_status = WIN;

  s21::Game game(state, game_status);

  game.userInput(START, false);
  game.updateCurrentState();

  EXPECT_EQ(game_status, WIN);
}

TEST(GameTest, HasFSM) {
  game_info_t state{};
  game_status_t game_status = WIN;

  s21::Game game(state, game_status);

  game.setFsm(TETRIS);

  game.userInput(START, false);
  game.updateCurrentState();

  EXPECT_EQ(game_status, START_GAME);

  game.userInput(TERMINATE, false);
  game.updateCurrentState();

  game.setFsm(TETRIS);
}

TEST(GameModelTest, InGameTetris) {
  s21::GameData data;
  brick_game_status_t &status = data.getStatus();
  game_info_t &state = data.getCurrentState();

  EXPECT_FALSE(state.pause);

  status = TETRIS;
  s21::GameModel model(data);

  model.userInput(PAUSE, false);
  data = model.updateCurrentState();

  EXPECT_TRUE(state.pause);
}

TEST(GameModelTest, InGameSnake) {
  s21::GameData data;
  brick_game_status_t &status = data.getStatus();
  game_info_t &state = data.getCurrentState();

  EXPECT_FALSE(state.pause);

  status = SNAKE;
  s21::GameModel model(data);

  model.userInput(PAUSE, false);
  data = model.updateCurrentState();

  EXPECT_TRUE(state.pause);
}

TEST(GameModelTest, InGameTerminate) {
  s21::GameData data;
  brick_game_status_t &status = data.getStatus();
  game_info_t &state = data.getCurrentState();

  EXPECT_FALSE(state.pause);

  status = TETRIS;
  s21::GameModel model(data);

  model.userInput(TERMINATE, false);
  data = model.updateCurrentState();

  EXPECT_EQ(status, MENU);
}