#ifndef _SNAKE_BACKEND_H_
#define _SNAKE_BACKEND_H_

#include <cstdlib>
#include <fstream>
#include <queue>
#include <random>
#include <stack>

#include "../game_objects.h"
#include "constants.h"

namespace s21 {
/**
 * @brief Тип направлений
 *
 * Используется для определения направлений движения частей змейки.
 */
enum class Direction { LEFT, RIGHT, UP, DOWN };

/**
 * @class Snake
 * @brief Класс игрового элемента "змейка"
 */
class Snake {
  int x_head{START_X_HEAD};
  int y_head{START_Y_HEAD};
  int x_tail{START_X_TAIL};
  int y_tail{START_Y_TAIL};

  bool eat_apple{false};

  std::queue<Direction> direction;

 public:
  Snake() {
    for (int i = 0; i < BODY_LENGTH; ++i) {
      direction.push(Direction::UP);
    }
  }

  /**
   * @brief Сдвигает змейку на один "пиксель" в направлении движения
   */
  void move();

  /**
   * @brief Функция поворота (инициированного пользователем движения змейки).
   * В зависимости от пользовательского действия поворачивает
   * ее вправо/влево/вверх/вниз или ускоряет.
   * @param user_action Аргумент типа user_action_t, содержащий информацию о
   * пользовательском действии
   * @param speed_up Аргумент типа bool, содержащий информацию о том, привело ли
   * пользовательское действие к ускорению
   * @return булево значение, указывающую на то, привело ли пользовательское
   * действие к повороту
   */
  bool turn(user_action_t user_action, bool &speed_up);

  /**
   * @brief Приводит объект в состояние, соответствующее поеданию яблока.
   * Вызывается после столкновения с яблоком на поле.
   */
  void foundApple();

  /**
   * @brief Сбрасывает состояние объекта к начальному
   */
  void reset();

  /**
   * @brief Возвращает текущую игровую длину змейки
   * @return int длина змейки
   */
  int length();

  /**
   * @brief Возвращает информацию о том, "поела" ли змейка
   * @return булево значение: истинно, если змейка голодна, и ложно, если она
   * съела яблоко.
   */
  bool isHungry();

  /**
   * @brief Возвращает x-координату головы змейки
   * @return int x-координата головы
   */
  int getXHead();

  /**
   * @brief Возвращает y-координату головы змейки
   * @return int y-координата головы
   */
  int getYHead();

  /**
   * @brief Возвращает x-координату хвоста змейки
   * @return int x-координата хвоста
   */
  int getXTail();

  /**
   * @brief Возвращает y-координату хвоста змейки
   * @return int y-координата хвоста
   */
  int getYTail();

  /**
   * @brief Устанавливает x-координату головы змейки
   * @param x_head x-координата головы
   */
  void setXHead(int x_head);

  /**
   * @brief Устанавливает y-координату головы змейки
   * @param y_head y-координата головы
   */
  void setYHead(int y_head);

  /**
   * @brief Устанавливает x-координату хвоста змейки
   * @param x_tail x-координата хвоста
   */
  void setXTail(int x_tail);

  /**
   * @brief Устанавливает y-координату хвоста змейки
   * @param y_tail y-координата хвоста
   */
  void setYTail(int y_tail);

  /**
   * @brief Возвращает направление головы змейки
   * @return Direction направление головы
   */
  Direction getHeadDirection();

  /**
   * @brief Возвращает направление хвоста змейки
   * @return Direction направление хвоста
   */
  Direction getTailDirection();

  /**
   * @brief Устанавливает направление головы змейки
   * @param head_direction направление головы
   */
  void setHeadDirection(Direction head_direction);

  /**
   * @brief Устанавливает направление хвоста змейки
   * @param tail_direction направление хвоста
   */
  void setTailDirection(Direction tail_direction);

 private:
  void movePoint(int &x, int &y, Direction point_direction);
};

/**
 * @class Apple
 * @brief Класс игрового элемента "яблоко"
 */

class Apple {
  int x{START_APPLE_X};
  int y{START_APPLE_Y};

 public:
  /**
   * @brief определяет координаты яблока в пределах поля средствами рандомизации
   */
  void spawn();

  /**
   * @brief Возвращает x-координату яблока
   * @return int x-координата
   */
  int getX();

  /**
   * @brief Возвращает y-координату яблока
   * @return int y-координата
   */
  int getY();

  /**
   * @brief Устанавливает x-координату яблока
   * @param x x-координата
   */
  void setX(int x);

  /**
   * @brief Устанавливает y-координату яблока
   * @param y y-координата
   */
  void setY(int y);
};

/**
 * @class Field
 * @brief Класс игрового элемента "поле"
 *
 * Содержит структуру game_info_t, которая хранит в себе игровое поле и игровую
 * статистику
 */

class Field {
  game_info_t *current_state;

 public:
  Field(game_info_t *state) : current_state(state) {}

  /**
   * @brief Инициализирует поле класса - структуру game_info_t, содержащую
   * информацию о текущем состоянии игры. Память для полей выделяется
   * динамически, поэтому необходимо вызывать функцию stats_delete для избежания
   * утечек памяти
   */
  void statsInit();

  /**
   * @brief Освобождает память, ранее выделенную для полей, обнуляет игровую
   * статистику
   */
  void statsDelete();

  /**
   * @brief Обновляет игровую статистику: очки, уровень, рекорд.
   */
  void statsUpdate();

  /**
   * @brief Считывает из указанного файла игровой рекорд в поле класса
   * -структуру game_info_t. Если файла не существует, считывается 0.
   * @param file_path Путь к файлу
   */
  void readHighScoreFromFile(const char *file_path);

  /**
   * @brief Записывает указанный рекорд в файл. Если файла не существует,
   * создает его
   * @param file_path Путь к файлу
   */
  void writeHighScoreToFile(const char *file_path);

  /**
   * @brief Устанавливает на игровое поле точку по переданным координатам. В
   * функцию включена проверка границ
   * @param x x-координата
   * @param y y-координата
   */
  void setPoint(int x, int y);

  /**
   * @brief Удаляет на игровом поле точку по переданным координатам. В
   * функцию включена проверка границ
   * @param x x-координата
   * @param y y-координата
   */
  void removePoint(int x, int y);

  /**
   * @brief Помещает змейку на поле в ее стартовой конфигурации
   * @param body_length начальная длина змейки
   * @param start_x стартовая x-координата змейки
   * @param start_y стартовая y-координата змейки
   */
  void initSnake(int body_length, int start_x, int start_y);

  /**
   * @brief Проверяет коллизию с игровым полем точки с переданными координатами
   * @param x x-координата
   * @param y y-координата
   * @return булево значение: истинно, если есть коллизия (наложение), ложно -
   * если нет
   */
  bool isCollide(int x, int y);

  /**
   * @brief Очищает игровое поле
   */
  void clean();

  /**
   * @brief Игровой таймер
   * @return double "Тик" игры в скеундах
   */
  double gameTimer();
};
}  // namespace s21

#endif