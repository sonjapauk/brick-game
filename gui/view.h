#ifndef _VIEW_H_
#define _VIEW_H_

#include "../inc/game_data.h"

namespace s21 {
class View {
 public:
  virtual ~View() = default;
  virtual void printGame(GameData &data) = 0;
  virtual int getUiKey() = 0;
  virtual void closeWindow() = 0;
  virtual void initWindow() = 0;
};
}  // namespace s21

#endif
