#include "controller.h"

user_action_t s21::Controller::getAction(int user_input) {
  user_action_t user_action;

  switch (user_input) {
    case ENTER_KEY:
      user_action = START;
      break;
    case PAUSE_KEY:
      user_action = PAUSE;
      break;
    case KEY_LEFT:
      user_action = LEFT;
      break;
    case KEY_RIGHT:
      user_action = RIGHT;
      break;
    case KEY_DOWN:
      user_action = DOWN;
      break;
    case KEY_UP:
      user_action = UP;
      break;
    case SPACE_KEY:
      user_action = ACTION;
      break;
    case ESCAPE_KEY:
      user_action = TERMINATE;
      break;
    default:
      user_action = (user_action_t)NO_ACTION;
      break;
  }

  return user_action;
}

void s21::Controller::gameLoop() {
  initGame();

  GameData state{};

  while (state.getStatus() != EXIT) {
    user_action_t user_action = getAction(view.getUiKey());

    model.userInput(user_action, false);
    state = model.updateCurrentState();

    view.printGame(state);
  }

  endGame();
}

void s21::Controller::initGame() { view.initWindow(); }

void s21::Controller::endGame() { view.closeWindow(); }
