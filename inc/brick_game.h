#ifndef _BRICK_GAME_H_
#define _BRICK_GAME_H_

#include "fsm.h"
#include "game_data.h"

namespace s21 {
/**
 * @class Game
 * @brief Класс для элемента консоли "игра"
 *
 * Содержит данные, необходимые конкретно игровому процессу - игровой статус
 * (game_status_t), структуру game_info_t, пользовательское действие, указатель
 * на КА, формализующий логику.
 */
class Game {
  game_info_t &current_state;
  user_action_t action{};
  bool hold{false};

  game_status_t &game_status;
  FSM *fsm{nullptr};

 public:
  Game(game_info_t &state, game_status_t &status)
      : current_state(state), game_status(status) {}

  ~Game() {
    if (fsm) {
      delete fsm;
    }
  }

  /**
   * @brief Обновляет данные о пользовательском вводе в объекте игры
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   * @param hold Отвечает за зажатие клавиши
   */
  void userInput(user_action_t action, bool hold);

  /**
   * @brief Реализация игрового процесса. На основании текущего состояния и
   * пользовательского ввода обновляет состояние игры.
   * @return game_info_t Информация о текущем состоянии игры
   */
  game_info_t updateCurrentState();

  /**
   * @brief Инициализирует и удаляет КА в соответствии со статусом консоли и
   * игровым этапом
   * @param status Статус Brick-game
   */
  void setFsm(brick_game_status_t status);
};

/**
 * @class Menu
 * @brief Класс для элемента консоли "меню"
 *
 * Содержит статус меню
 */
class Menu {
  menu_status_t &menu_status;

 public:
  Menu(menu_status_t &status) : menu_status(status) {}

  /**
   * @brief Работа меню - смена статусов меню и глобальных статусов консоли.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   */
  brick_game_status_t menu(user_action_t action);
};

/**
 * @class BrickGame
 * @brief Класс, "эмулирующий" игровую консоль
 *
 * Содержит глобальный статус консоли и ее элементы "меню" и "игра"
 */
class BrickGame {
  brick_game_status_t &status;
  Menu menu;
  Game game;

 public:
  BrickGame(GameData &data)
      : status(data.getStatus()),
        menu(data.getMenuStatus()),
        game(data.getCurrentState(), data.getGameStatus()) {}

  /**
   * @brief Инициирует обновление статусов консоли и меню в соответствии с
   * пользовательским действием.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   */
  void updateStatuses(user_action_t action);

  /**
   * @brief Обработка пользовательского действия и игрового(консольного) события
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   * @param hold Отвечает за зажатие клавиши
   */
  void gameEvent(user_action_t action, bool hold);

  /**
   * @brief Определяет, в работе ли консоль (в меню или игре)
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   * @return булево значение: истинно, если консоль в меню или игре, иначе -
   * ложно
   */
  bool inGame(user_action_t action);
};

/**
 * @class GameModel
 * @brief Класс модели
 *
 * Содержит консоль и игровые данные GameData
 */
class GameModel {
  GameData data{};
  BrickGame console;

 public:
  GameModel() : console(data) {}
  GameModel(GameData g_data) : data(g_data), console(data) {}

  /**
   * @brief Инициирует игровое событие в консоли в соответствии с
   * пользовательским вводом
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   * @param hold Отвечает за зажатие клавиши
   */
  void userInput(user_action_t action, bool hold);

  /**
   * @brief Возвращает данные о состоянии игры для внешнего использования
   * (отрисовки в интерфейсе)
   * @return GameData Полные игровые данные
   */
  GameData updateCurrentState();
};
}  // namespace s21

#endif