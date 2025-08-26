#ifndef _CLI_VIEW_H_
#define _CLI_VIEW_H_

#include "../view.h"

extern "C" {
#include "frontend.h"
}

namespace s21 {
class CLIView : public View {
 public:
  virtual ~CLIView() {}

  virtual void printGame(GameData &data) {
    cli_print_game(data.getStatus(), data.getMenuStatus(), data.getGameStatus(),
                   &data.getCurrentState());
  }

  virtual int getUiKey() { return get_cli_key(); }

  virtual void closeWindow() { endwin(); }

  virtual void initWindow() { win_init(50); }
};
}  // namespace s21

#endif