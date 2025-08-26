#ifndef _GAME_DATA_
#define _GAME_DATA_

#include "game_objects.h"

namespace s21 {
/**
 * @class GameData
 * @brief Хранит игровую информацию
 *
 * Совокупность данных, содержащихся в классе,
 * является исчерпывающей информацией о полном состоянии
 * игровой консоли
 */

class GameData {
  game_info_t current_state{};
  menu_status_t menu_status{MENU_TETRIS};
  brick_game_status_t status{MENU};
  game_status_t game_status{START_GAME};

 public:
  /**
   * @brief Возвращает ссылку на состояние конкретной игры
   * @return game_info_t Текущее состояние конкретной игры
   */
  game_info_t &getCurrentState() { return current_state; }

  /**
   * @brief Возвращает ссылку на состояние меню
   * @return menu_status_t Текущее состояние меню
   */
  menu_status_t &getMenuStatus() { return menu_status; }

  /**
   * @brief Возвращает ссылку на состояние консоли
   * @return brick_game_status_t Текущее состояние консоли
   */
  brick_game_status_t &getStatus() { return status; }

  /**
   * @brief Возвращает ссылку на игровой статус
   * @return game_status_t Текущий игровой статус
   */
  game_status_t &getGameStatus() { return game_status; }
};
}  // namespace s21

#endif