#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/brick_game.h"

#ifdef USE_CLI
#include "../gui/cli/view.h"
#else
#include "../gui/desktop/view.h"
#endif

namespace s21 {
class Controller {
  GameModel &model;
  View &view;

 public:
  Controller(GameModel &g_model, View &g_view) : model(g_model), view(g_view) {}

  void gameLoop();
  user_action_t getAction(int user_input);
  void initGame();
  void endGame();
};
}  // namespace s21

#endif