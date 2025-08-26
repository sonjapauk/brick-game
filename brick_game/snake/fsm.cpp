#include "../../inc/fsm.h"

static struct timespec start_time {};
static struct timespec current_time {};

void s21::SnakeFSM::fsm(user_action_t user_action) {
  if (user_action == TERMINATE && state != SnakeState::INIT) {
    state = SnakeState::EXIT;
  }

  actions.push(user_action);

  switch (state) {
    case SnakeState::INIT:
      onInitState();
      break;
    case SnakeState::START:
      onStartState(user_action);
      break;
    case SnakeState::SPAWN_APPLE:
      onSpawnAppleState();
      break;
    case SnakeState::TURNING:
      onTurningState(user_action);
      break;
    case SnakeState::MOVING:
      onMovingState();
      break;
    case SnakeState::COLLISION:
      onCollisionState();
      break;
    case SnakeState::EAT_APPLE:
      onEatAppleState();
      break;
    case SnakeState::GAMEOVER:
      onGameoverState(user_action);
      break;
    case SnakeState::WIN:
      onWinState(user_action);
      break;
    case SnakeState::EXIT:
      onExitState();
      break;
  }
}

void s21::SnakeFSM::onInitState() {
  field.statsInit();
  state = SnakeState::START;
}

void s21::SnakeFSM::onStartState(user_action_t user_action) {
  field.readHighScoreFromFile(HIGH_SCORE_SNAKE_FILE_PATH);

  if (user_action == START) {
    clock_gettime(CLOCK_REALTIME, &start_time);

    field.initSnake(BODY_LENGTH, snake.getXHead(), snake.getYHead());

    state = SnakeState::SPAWN_APPLE;
  }
}

void s21::SnakeFSM::onSpawnAppleState() {
  do {
    apple.spawn();
  } while (field.isCollide(apple.getX(), apple.getY()));

  field.setPoint(apple.getX(), apple.getY());

  state = SnakeState::TURNING;
}

void s21::SnakeFSM::onTurningState(user_action_t user_action) {
  if (user_action == (user_action_t)NO_ACTION) {
    user_action = getActionFromStack();
  }

  bool speed_up = false;
  bool was_turned = snake.turn(user_action, speed_up);

  cleanActionStack();

  clock_gettime(CLOCK_REALTIME, &current_time);

  double time_diff = current_time.tv_sec - start_time.tv_sec +
                     (current_time.tv_nsec - start_time.tv_nsec) * 1e-9;

  if (time_diff >= field.gameTimer() || speed_up || was_turned) {
    start_time = current_time;
    state = SnakeState::MOVING;
  }
}

void s21::SnakeFSM::onMovingState() {
  if (snake.isHungry()) {
    field.removePoint(snake.getXTail(), snake.getYTail());
  }

  snake.move();

  if (field.isCollide(snake.getXHead(), snake.getYHead())) {
    state = SnakeState::COLLISION;
  } else {
    state = SnakeState::TURNING;
  }

  field.setPoint(snake.getXHead(), snake.getYHead());
}

void s21::SnakeFSM::onCollisionState() {
  if (snake.getXHead() == apple.getX() && snake.getYHead() == apple.getY()) {
    state = SnakeState::EAT_APPLE;
  } else {
    state = SnakeState::GAMEOVER;
  }
}

void s21::SnakeFSM::onEatAppleState() {
  snake.foundApple();
  field.statsUpdate();

  if (snake.length() == WIN_SCORE) {
    state = SnakeState::WIN;
  } else {
    state = SnakeState::SPAWN_APPLE;
  }
}

void s21::SnakeFSM::onWinState(user_action_t user_action) {
  if (user_action == START) {
    field.clean();
    snake.reset();

    state = SnakeState::START;
  }
}

void s21::SnakeFSM::onGameoverState(user_action_t user_action) {
  if (user_action == START) {
    field.clean();
    snake.reset();

    state = SnakeState::START;
  }
}

void s21::SnakeFSM::onExitState() {
  field.statsDelete();
  state = SnakeState::INIT;
}

user_action_t s21::SnakeFSM::getActionFromStack() {
  user_action_t user_action = (user_action_t)NO_ACTION;

  while (user_action == (user_action_t)NO_ACTION && !actions.empty()) {
    user_action = actions.top();
    actions.pop();
  }

  return user_action;
}

void s21::SnakeFSM::cleanActionStack() {
  while (!actions.empty()) {
    actions.pop();
  }
}

void s21::SnakeFSM::setSnakeState(SnakeState state) { this->state = state; }

s21::SnakeState s21::SnakeFSM::getSnakeState() { return state; }

game_status_t s21::SnakeFSM::getGameStatus() {
  game_status_t current_status;

  switch (state) {
    case SnakeState::START:
      current_status = START_GAME;
      break;
    case SnakeState::GAMEOVER:
      current_status = GAMEOVER_GAME;
      break;
    case SnakeState::INIT:
    case SnakeState::EXIT:
      current_status = SERVICE;
      break;
    case SnakeState::WIN:
      current_status = WIN;
      break;
    default:
      current_status = PLAYING;
      break;
  }

  return current_status;
}
