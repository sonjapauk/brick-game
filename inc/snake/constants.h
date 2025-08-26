#ifndef _SNAKE_DEFINES_H_
#define _SNAKE_DEFINES_H_

#include <cstdio>

constexpr int START_APPLE_X = 3;
constexpr int START_APPLE_Y = 3;

constexpr int START_X_HEAD = 5;
constexpr int START_Y_HEAD = 10;

constexpr int START_X_TAIL = 5;
constexpr int START_Y_TAIL = 13;

constexpr int WIN_SCORE = 200;
constexpr int POINTS_PER_APPLE = 1;
constexpr int POINTS_PER_SNAKE_LEVEL = 5;

constexpr double SPEED_SNAKE_COEFFICIENT = 0.25;

constexpr int BODY_LENGTH = 4;

constexpr const char* HIGH_SCORE_SNAKE_FILE_PATH = "high_score_snake.txt";

#endif