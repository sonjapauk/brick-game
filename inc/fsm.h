#ifndef _FSM_H_
#define _FSM_H_

#include "snake/fsm.h"

extern "C" {
#include "tetris/fsm.h"
}

namespace s21 {
/**
 * @class FSM
 * @brief Базовый абстрактный класс КА
 *
 * Определяет общий миимальный интерфейс КА, отвечающего за смену состояний
 * игры.
 */
class FSM {
 public:
  virtual ~FSM() {}

  /**
   * @brief Реализация логики работы КА: обработка игровых данных в соответствии
   * с ее текущим состоянием игры.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   */
  virtual void fsm(user_action_t user_action) = 0;

  /**
   * @brief Приводит в соответствие состояние КА игровому состоянию.
   * @return Игровое состояние, соответствующее текущему состоянию КА.
   */
  virtual game_status_t getGameStatus() = 0;
};

/**
 * @class TetrisFSM
 * @brief Класс КА тетриса
 */

class TetrisFSM : public FSM {
  tetris_state_t state{INIT};
  game_info_t *current_state{nullptr};

 public:
  TetrisFSM(game_info_t *state) : current_state(state) {}
  virtual ~TetrisFSM() {}

  virtual void fsm(user_action_t user_action) {
    tetris_fsm(user_action, current_state);
    state = get_tetris_state();
  }

  virtual game_status_t getGameStatus() {
    game_status_t current_status;

    switch (state) {
      case START_TETRIS:
        current_status = START_GAME;
        break;
      case GAMEOVER:
        current_status = GAMEOVER_GAME;
        break;
      case INIT:
      case EXIT_TETRIS:
        current_status = SERVICE;
        break;
      default:
        current_status = PLAYING;
        break;
    }

    return current_status;
  }
};

/**
 * @class SnakeFSM
 * @brief Класс КА змейки
 */

class SnakeFSM : public FSM {
  SnakeState state{SnakeState::INIT};

  Field field{nullptr};
  Snake snake{};
  Apple apple{};

  std::stack<user_action_t> actions;

 public:
  SnakeFSM(game_info_t *state) : field(state) {}
  SnakeFSM(Field fld, Snake snk = Snake{}, Apple ppl = Apple{})
      : field(fld), snake(snk), apple(ppl) {}

  virtual ~SnakeFSM() {}

  virtual void fsm(user_action_t user_action);
  virtual game_status_t getGameStatus();

  /**
   * @brief Функция, соответствующая начальному состоянию игровой сессии.
   * Осуществляет начальную инициализацию полей и игровой статистики.
   */
  void onInitState();

  /**
   * @brief Функция, соответствующая стартовому состоянию текущей игры.
   * Запускает игровой таймер, заполняет статистику,
   * устанавливает начальную конфигурацию змейки на поле.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   */
  void onStartState(user_action_t user_action);

  /**
   * @brief Функция, соответствующая состоянию спавна яблока.
   * Определяет новые координаты яблока, выводит его на поле.
   */
  void onSpawnAppleState();

  /**
   * @brief Функция, соответствующая состоянию инициированного пользователем
   * движения змейки. В зависимости от пользовательского действия поворачивает
   * ее вправо/влево/вверх/вниз или ускоряет.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   */
  void onTurningState(user_action_t user_action);

  /**
   * @brief Функция, соответствующая состоянию самопроизвольного движения
   * змейки. По истечении таймера сдвигает ее на один "пиксель" в направлении
   * движения, пока это возможно (нет коллизии).
   */
  void onMovingState();

  /**
   * @brief Функция, соответствующая состоянию коллизии змейки
   * с каким-либо объектом на поле (стеной, яблоком, самой собой).
   * Определяет новое состояние КА в зависимости от типа объекта, с которым
   * столкнулась змейка.
   */
  void onCollisionState();

  /**
   * @brief Функция, соответствующая поеданию змейкой яблока.
   * Подсчитывает очки, обновляет игровую статистику, определяет следующее
   * состояние в зависимости от количества очков.
   */
  void onEatAppleState();

  /**
   * @brief Функция, соответствующая состоянию геймовера.
   * Останавливает игру.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   */
  void onGameoverState(user_action_t user_action);

  /**
   * @brief Функция, соответствующая состоянию победы игрока.
   * Останавливает игру.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   */
  void onWinState(user_action_t user_action);

  /**
   * @brief Функция, соответствующая конечному состоянию игровой сессии.
   * Очищает выделенную для сессии память, обнуляет статистику.
   */
  void onExitState();

  /**
   * @brief Функция тестирования. Устанавливает новое состояние КА змейки
   * @param state Новое состояние КА змейки
   */
  void setSnakeState(SnakeState state);

  /**
   * @brief Функция тестирования. Возвращает текущее состояние КА змейки
   * @return Текущее состояние КА змейки
   */
  SnakeState getSnakeState();

 private:
  user_action_t getActionFromStack();
  void cleanActionStack();
};
}  // namespace s21

#endif