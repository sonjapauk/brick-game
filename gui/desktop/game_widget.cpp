#include "game_widget.h"

void s21::GameWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  drawShot(painter);
}

void s21::GameWidget::drawShot(QPainter &painter) {
  drawOverlay(painter);

  if (status == MENU) {
    drawMenu(painter);
  } else if (status != EXIT) {
    drawGameOverlay(painter);

    if (status == TETRIS) {
      drawTetrisOverlay(painter);
    }

    drawCurrentState(painter);
  }
}

void s21::GameWidget::drawOverlay(QPainter &painter) {
  painter.drawRect(BOARD_LEFT - 1, BOARD_TOP - 1, FIELD_WIDTH_PX + 2,
                   FIELD_HEIGHT_PX + 2);
  painter.drawRect(HUD_LEFT - 1, BOARD_TOP - 1, 180, FIELD_HEIGHT_PX + 2);
}

void s21::GameWidget::drawMenu(QPainter &painter) {
  int base_x = (HUD_WIDTH + 2) * 20 + CELL_SIZE;
  int y1 = 60, y2 = 110, y3 = 160;

  painter.drawText(base_x, y1,
                   menu_status == MENU_TETRIS ? "> TETRIS" : "  TETRIS");
  painter.drawText(base_x, y2,
                   menu_status == MENU_SNAKE ? "> SNAKE" : "  SNAKE");
  painter.drawText(base_x, y3, menu_status == MENU_EXIT ? "> EXIT" : "  EXIT");
}

void s21::GameWidget::drawGameOverlay(QPainter &painter) {
  painter.drawRect(HUD_LEFT + CELL_SIZE, 2 * CELL_SIZE,
                   (HUD_WIDTH - 3) * CELL_SIZE, 2 * CELL_SIZE);
  painter.drawRect(HUD_LEFT + CELL_SIZE, 5 * CELL_SIZE,
                   (HUD_WIDTH - 3) * CELL_SIZE, 2 * CELL_SIZE);
  painter.drawRect(HUD_LEFT + CELL_SIZE, 8 * CELL_SIZE,
                   (HUD_WIDTH - 3) * CELL_SIZE, 2 * CELL_SIZE);
  painter.drawRect(HUD_LEFT + CELL_SIZE, 11 * CELL_SIZE,
                   (HUD_WIDTH - 3) * CELL_SIZE, 2 * CELL_SIZE);

  const QColor backgroundColor = palette().window().color();

  painter.fillRect(HUD_LEFT + 1.5 * CELL_SIZE, 1.5 * CELL_SIZE, 2.5 * 20,
                   2 * 20, backgroundColor);
  painter.fillRect(HUD_LEFT + 1.5 * CELL_SIZE, 4.5 * CELL_SIZE, 2.5 * 20,
                   2 * 20, backgroundColor);
  painter.fillRect(HUD_LEFT + 1.5 * CELL_SIZE, 7.5 * CELL_SIZE, 5 * 20, 2 * 20,
                   backgroundColor);
  painter.fillRect(HUD_LEFT + 1.5 * CELL_SIZE, 10.5 * CELL_SIZE, 2.5 * 20,
                   2 * 20, backgroundColor);

  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, 1.5 * CELL_SIZE + 15, "LEVEL");
  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, 4.5 * CELL_SIZE + 15, "SCORE");
  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, 7.5 * CELL_SIZE + 15,
                   "HIGH-SCORE");
  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, 10.5 * CELL_SIZE + 15, "PAUSE");
}

void s21::GameWidget::drawStat(QPainter &painter) {
  painter.setBackgroundMode(Qt::OpaqueMode);
  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, BOARD_TOP + 1.5 * LINE_HEIGHT,
                   QString::number(current_state.level));
  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, BOARD_TOP + 3.5 * LINE_HEIGHT,
                   QString::number(current_state.score));
  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, BOARD_TOP + 5.5 * LINE_HEIGHT,
                   QString::number(current_state.high_score));
  painter.drawText(HUD_LEFT + 1.5 * CELL_SIZE, BOARD_TOP + 7.5 * LINE_HEIGHT,
                   current_state.pause ? "ON" : "OFF");
}

void s21::GameWidget::drawTetrisOverlay(QPainter &painter) {
  painter.drawRect(HUD_LEFT + CELL_SIZE, 14 * CELL_SIZE,
                   (HUD_WIDTH - 3) * CELL_SIZE, 4.5 * CELL_SIZE);

  int base_x = HUD_LEFT + (HUD_WIDTH - 3) * CELL_SIZE + 5;
  int base_y = 15 * CELL_SIZE;

  painter.drawText(base_x, base_y, "N");
  painter.drawText(base_x, base_y + 20, "E");
  painter.drawText(base_x, base_y + 40, "X");
  painter.drawText(base_x, base_y + 60, "T");
}

void s21::GameWidget::drawCurrentState(QPainter &painter) {
  drawStat(painter);
  drawField(painter);

  if (status == TETRIS) {
    drawNextFigure(painter);
  }

  drawMessage(painter);
  drawInstruction(painter);
}

void s21::GameWidget::drawField(QPainter &painter) {
  for (int i = 1; i < FIELD_LENGTH - 1; ++i) {
    for (int j = 1; j < FIELD_WIDTH - 1; ++j) {
      if (current_state.field[i][j] == 1) {
        int x = BOARD_LEFT + (j - 1) * CELL_SIZE;
        int y = BOARD_TOP + (i - 1) * CELL_SIZE;

        QRect cellRect(x, y, CELL_SIZE, CELL_SIZE);
        QRect innerWhiteRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
        QRect fillRect(x + 2, y + 2, CELL_SIZE - 4, CELL_SIZE - 4);

        painter.setPen(QPen(Qt::white, 1));
        painter.drawRect(innerWhiteRect);
        painter.fillRect(fillRect, Qt::darkCyan);
        painter.setPen(QPen(Qt::black, 1));
        painter.drawRect(cellRect);
      }
    }
  }
}

void s21::GameWidget::drawNextFigure(QPainter &painter) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (current_state.next[i][j] == 1) {
        int x = HUD_LEFT + (j + 2) * CELL_SIZE;
        int y = BOARD_TOP + (i + 14) * CELL_SIZE;

        QRect cellRect(x, y, CELL_SIZE, CELL_SIZE);
        QRect innerWhiteRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
        QRect fillRect(x + 2, y + 2, CELL_SIZE - 4, CELL_SIZE - 4);

        painter.setPen(QPen(Qt::white, 1));
        painter.drawRect(innerWhiteRect);
        painter.fillRect(fillRect, Qt::darkCyan);
        painter.setPen(QPen(Qt::black, 1));
        painter.drawRect(cellRect);
      }
    }
  }
}

void s21::GameWidget::drawMessage(QPainter &painter) {
  painter.setBackgroundMode(Qt::OpaqueMode);

  if (game_status == START_GAME) {
    painter.drawText(
        BOARD_LEFT + (FIELD_WIDTH_PX / 2 - INTRO_MESSAGE_LEN_F) / 2,
        BOARD_TOP + FIELD_HEIGHT_PX / 2 - 20, INTRO_MESSAGE_F);
    painter.drawText(
        BOARD_LEFT + (FIELD_WIDTH_PX / 2 - INTRO_MESSAGE_LEN_S) / 2 + 10,
        BOARD_TOP + FIELD_HEIGHT_PX / 2 + 0, INTRO_MESSAGE_S);
  } else if (game_status == GAMEOVER_GAME) {
    painter.drawText(BOARD_LEFT + (FIELD_WIDTH_PX / 2 - GAMEOVER_LEN) / 2 + 10,
                     BOARD_TOP + FIELD_HEIGHT_PX / 2 - 20, GAMEOVER_WORD);
    painter.drawText(
        BOARD_LEFT + (FIELD_WIDTH_PX / 2 - INTRO_MESSAGE_LEN_S) / 2,
        BOARD_TOP + FIELD_HEIGHT_PX / 2 + 0, INTRO_MESSAGE_F);
  } else if (game_status == WIN) {
    painter.drawText(BOARD_LEFT + (FIELD_WIDTH_PX / 2 - WIN_LEN) / 2 + 17,
                     BOARD_TOP + FIELD_HEIGHT_PX / 2 - 20, WIN_WORD);
    painter.drawText(
        BOARD_LEFT + (FIELD_WIDTH_PX / 2 - INTRO_MESSAGE_LEN_S) / 2,
        BOARD_TOP + FIELD_HEIGHT_PX / 2 + 0, INTRO_MESSAGE_F);
  }

  painter.setBackgroundMode(Qt::TransparentMode);
}

void s21::GameWidget::drawInstruction(QPainter &painter) {
  painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 2,
                   "INSTRUCTION:");
  painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 3,
                   "Key \"p\" - pause");
  painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 4,
                   "ESC - exit to menu");

  if (status == TETRIS) {
    painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 5,
                     "SPACE - rotate figure");
    painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 6,
                     "LEFT/RIGHT arrow - move figure");
    painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 7,
                     "DOWN arrow - drop figure");
  } else if (status == SNAKE) {
    painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 5,
                     "SPACE - speed up snake");
    painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 6,
                     "LEFT/RIGHT/UP/DOWN arrow - controle snake");
    painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 7,
                     "You can also use the arrows in direction");
    painter.drawText(FIELD_WIDTH_PX * 2 + CELL_SIZE * 2, CELL_SIZE * 8,
                     "of moving to speed up ;)");
  }
}

void s21::GameWidget::keyPressEvent(QKeyEvent *event) {
  last_key = event->key();
}

int s21::GameWidget::getGuiKey() {
  int key = last_key;
  last_key = -1;
  return key;
}