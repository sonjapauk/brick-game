#ifndef _GUI_FRONTEND_H_
#define _GUI_FRONTEND_H_

#include <QApplication>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../inc/game_objects.h"
#include "constants.h"

namespace s21 {
class GameWidget : public QWidget {
  int last_key{-1};

 public:
  menu_status_t menu_status;
  brick_game_status_t status;
  game_info_t current_state;
  game_status_t game_status;

  GameWidget(QWidget *parent = nullptr) : QWidget(parent) {
    setFont(QFont("Courier New", 16));
    setFocusPolicy(Qt::StrongFocus);
  }

  int getGuiKey();

 protected:
  void paintEvent(QPaintEvent *) override;
  void keyPressEvent(QKeyEvent *event) override;

  void drawOverlay(QPainter &painter);
  void drawMenu(QPainter &painter);
  void drawShot(QPainter &painter);
  void drawGameOverlay(QPainter &painter);
  void drawTetrisOverlay(QPainter &painter);

  void drawCurrentState(QPainter &painter);
  void drawStat(QPainter &painter);
  void drawMessage(QPainter &painter);
  void drawField(QPainter &painter);
  void drawNextFigure(QPainter &painter);
  void drawInstruction(QPainter &painter);
};
}  //     namespace s21

#endif