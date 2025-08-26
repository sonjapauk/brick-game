#include "../inc/brick_game.h"

game_info_t s21::Game::updateCurrentState() {
  if (action == PAUSE) {
    current_state.pause = current_state.pause ? false : true;
  }

  if ((!current_state.pause || action == TERMINATE) && fsm) {
    fsm->fsm(action);
    game_status = fsm->getGameStatus();
  }

  return current_state;
}

void s21::Game::userInput(user_action_t action, bool hold) {
  this->action = action;
  this->hold = hold;
}

void s21::BrickGame::updateStatuses(user_action_t action) {
  if (status == MENU) {
    status = menu.menu(action);
    game.setFsm(status);
  }

  if (action == TERMINATE && status != EXIT) {
    status = MENU;
  }
}

brick_game_status_t s21::Menu::menu(user_action_t action) {
  brick_game_status_t status = MENU;

  switch (action) {
    case UP:
      if (menu_status == MENU_EXIT) {
        menu_status = MENU_SNAKE;
      } else if (menu_status == MENU_SNAKE) {
        menu_status = MENU_TETRIS;
      }

      break;
    case DOWN:
      if (menu_status == MENU_TETRIS) {
        menu_status = MENU_SNAKE;
      } else if (menu_status == MENU_SNAKE) {
        menu_status = MENU_EXIT;
      }

      break;
    case START:
      if (menu_status == MENU_TETRIS) {
        status = TETRIS;
      } else if (menu_status == MENU_SNAKE) {
        status = SNAKE;
      } else {
        status = EXIT;
      }

      break;
    case TERMINATE:
      status = EXIT;
      break;
    default:
      break;
  }

  return status;
}

void s21::BrickGame::gameEvent(user_action_t action, bool hold) {
  game.userInput(action, hold);
  game.updateCurrentState();
}

void s21::Game::setFsm(brick_game_status_t status) {
  if (fsm) {
    delete fsm;
    fsm = nullptr;
  }

  if (status == TETRIS) {
    fsm = new TetrisFSM(&current_state);
  } else if (status == SNAKE) {
    fsm = new SnakeFSM(&current_state);
  }
}

bool s21::BrickGame::inGame(user_action_t action) {
  return ((status == TETRIS || status == SNAKE) ||
          (action == TERMINATE && status != EXIT));
}

void s21::GameModel::userInput(user_action_t action, bool hold) {
  console.updateStatuses(action);

  if (console.inGame(action)) {
    console.gameEvent(action, hold);
  }
}

s21::GameData s21::GameModel::updateCurrentState() { return data; }
