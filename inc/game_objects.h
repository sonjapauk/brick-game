#ifndef _GAME_OBJECTS_H_
#define _GAME_OBJECTS_H_

#include "defines.h"

/** @brief Тип игровых состояний
 *
 * Используется для определения ключевых этапов игрового процесса
 */
typedef enum { PLAYING, WIN, GAMEOVER_GAME, START_GAME, SERVICE } game_status_t;

/** @brief Тип статусов консоли
 *
 * Используется для определения глобальных статусов игровой консоли
 */
typedef enum { MENU, TETRIS, SNAKE, EXIT } brick_game_status_t;

/** @brief Тип статусов меню
 *
 * Используется для определения статусов меню
 */
typedef enum { MENU_TETRIS, MENU_SNAKE, MENU_EXIT } menu_status_t;

/** @brief Тип пользовальских действий
 *
 * Используется для определения действия пользователя
 */
typedef enum {
  START,
  PAUSE,
  TERMINATE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ACTION
} user_action_t;

/** @brief Тип состояния конкретной игры
 *
 * Используется для определения важных метрик, таких как игровая статистика и
 * игровое поле
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} game_info_t;

#endif