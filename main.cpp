#include "controller/controller.h"

int main() {
  s21::GameModel model;

#ifdef USE_CLI
  s21::CLIView view;
#else
  s21::GUIView view;
#endif

  s21::Controller controller(model, view);
  controller.gameLoop();

  return 0;
}
