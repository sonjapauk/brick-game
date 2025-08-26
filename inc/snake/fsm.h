#ifndef _SNAKE_FSM_H_
#define _SNAKE_FSM_H_

#include "backend.h"

namespace s21 {
/**
 * @brief Тип состояний КА змейки
 *
 * Используется для определения состояний КА змейки.
 */
enum class SnakeState {
  INIT,
  START,
  SPAWN_APPLE,
  MOVING,
  TURNING,
  COLLISION,
  EAT_APPLE,
  WIN,
  GAMEOVER,
  EXIT
};
}  // namespace s21

#endif