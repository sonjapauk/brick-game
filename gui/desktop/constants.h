#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <Qt>
#include <string_view>

constexpr auto ENTER_KEY = Qt::Key_Return;
constexpr auto ESCAPE_KEY = Qt::Key_Escape;
constexpr auto SPACE_KEY = Qt::Key_Space;
constexpr auto PAUSE_KEY = Qt::Key_P;

constexpr auto KEY_LEFT = Qt::Key_Left;
constexpr auto KEY_RIGHT = Qt::Key_Right;
constexpr auto KEY_DOWN = Qt::Key_Down;
constexpr auto KEY_UP = Qt::Key_Up;

const QString INTRO_MESSAGE_F = "Press ENTER";
constexpr int INTRO_MESSAGE_LEN_F = 11;

const QString INTRO_MESSAGE_S = "to start!";
constexpr int INTRO_MESSAGE_LEN_S = 9;

const QString GAMEOVER_WORD = "GAMEOVER!";
constexpr int GAMEOVER_LEN = 9;

const QString WIN_WORD = "YOU WON!";
constexpr int WIN_LEN = 8;

constexpr int CELL_SIZE = 20;
constexpr int BOARD_LEFT = 20;
constexpr int BOARD_TOP = 20;

constexpr int FIELD_WIDTH_PX = (FIELD_WIDTH - 2) * CELL_SIZE;
constexpr int FIELD_HEIGHT_PX = (FIELD_LENGTH - 2) * CELL_SIZE;

constexpr int HUD_PADDING = 20;
constexpr int HUD_LEFT = BOARD_LEFT + FIELD_WIDTH_PX + HUD_PADDING;
constexpr int HUD_WIDTH = 10;
constexpr int LINE_HEIGHT = 30;

#endif