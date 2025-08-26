#ifndef _GUI_VIEW_H_
#define _GUI_VIEW_H_

#include "../view.h"
#include "game_widget.h"

namespace s21 {
class GUIView : public s21::View {
  int argc{};
  char **argv{};
  QApplication *app;
  QMainWindow *window;
  s21::GameWidget *game_widget;

 public:
  GUIView() {
    app = new QApplication(argc, argv);
    window = new QMainWindow();
    game_widget = new GameWidget();

    window->setWindowTitle("Snake Game");
    window->resize(850, 440);
    window->setCentralWidget(game_widget);
    window->show();

    game_widget->setParent(window);
  }

  virtual ~GUIView() {
    delete window;
    delete app;
  }

  virtual void printGame(GameData &data) {
    game_widget->menu_status = data.getMenuStatus();
    game_widget->status = data.getStatus();
    game_widget->game_status = data.getGameStatus();
    game_widget->current_state = data.getCurrentState();

    game_widget->update();
  }

  virtual int getUiKey() {
    QApplication::processEvents();
    return game_widget->getGuiKey();
  };

  virtual void closeWindow() { game_widget->close(); }

  virtual void initWindow() {}
};
}  // namespace s21

#endif