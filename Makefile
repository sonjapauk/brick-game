CC = gcc
CXX = g++-14
UI =

CXXFLAGS = $(UI) -Werror -Wall -Wextra -std=c++17
CFLAGS = $(UI) -Wall -Werror -Wextra -std=c11
GTEST_FLAGS = -lgtest -lgmock -pthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LCOV_TOOL = 
#make gcov_report CXX=g++-14 LCOV_TOOL="--gcov-tool=$(which gcov-14)" 

BUILD_DIR = out
LIBRARY_DIR = $(BUILD_DIR)/library
CONTROLLER_DIR = $(BUILD_DIR)/controller
FRONTEND_DIR = $(BUILD_DIR)/frontend
TESTS_DIR = $(BUILD_DIR)/tests
INSTALL_DIR = game
DOCS_DIR = docs

PROGRAM_NAME = brick_game
TEST_REPORT = test_report.txt

QT_FLAGS = $(shell pkg-config --cflags --libs Qt6Widgets)

HEADERS = $(wildcard inc/*.h)
SOURCES_TETRIS_LIBRARY = $(wildcard brick_game/tetris/*.c)
SOURCES_SNAKE_LIBRARY = $(wildcard brick_game/snake/*.cpp)
SOURCES_BRICK_GAME = $(wildcard brick_game/brick_game.cpp)
SOURCES_CONTROLLER = $(wildcard controller/controller.cpp)
SOURCES_TESTS = $(wildcard tests/*.cpp)

OBJ_TETRIS_LIBRARY := $(patsubst %.c, $(LIBRARY_DIR)/%.o, $(SOURCES_TETRIS_LIBRARY))
OBJ_SNAKE_LIBRARY := $(patsubst %.cpp, $(LIBRARY_DIR)/%.o, $(SOURCES_SNAKE_LIBRARY))
OBJ_BRICK_GAME := $(patsubst %.cpp, $(LIBRARY_DIR)/%.o, $(SOURCES_BRICK_GAME))
OBJ_CONTROLLER := $(patsubst %.cpp, $(CONTROLLER_DIR)/%.o, $(SOURCES_CONTROLLER))
OBJ_TESTS := $(patsubst %.cpp, $(TESTS_DIR)/%.o, $(SOURCES_TESTS))

ifeq ($(findstring -DUSE_CLI,$(UI)), -DUSE_CLI)
	SOURCES_FRONTEND = $(wildcard gui/cli/*.c)
	OBJ_FRONTEND := $(patsubst %.c, $(FRONTEND_DIR)/%.o, $(SOURCES_FRONTEND))
	UI_FLAG = -lncurses
else
	CXXFLAGS += -Wno-unknown-pragmas
	SOURCES_FRONTEND = $(wildcard gui/desktop/*.cpp)
	OBJ_FRONTEND := $(patsubst %.cpp, $(FRONTEND_DIR)/%.o, $(SOURCES_FRONTEND))
	UI_FLAG = $(QT_FLAGS)
endif

ifeq ($(shell uname),Linux)
	FLAGSCH += -lsubunit
endif

$(LIBRARY_DIR)/%.o: %.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(FRONTEND_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(FRONTEND_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< $(UI_FLAG) -o $@ 

$(CONTROLLER_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< $(UI_FLAG) -o $@

$(TESTS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(PROGRAM_NAME)

s21_brick_game.a: $(OBJ_TETRIS_LIBRARY) $(OBJ_SNAKE_LIBRARY) $(OBJ_BRICK_GAME) $(HEADERS)
	ar rcs s21_brick_game.a $(OBJ_TETRIS_LIBRARY) $(OBJ_SNAKE_LIBRARY) $(OBJ_BRICK_GAME) 
	ranlib s21_brick_game.a

$(PROGRAM_NAME): s21_brick_game.a  $(OBJ_CONTROLLER) $(OBJ_FRONTEND)
	$(CXX) $(CXXFLAGS) main.cpp $(OBJ_CONTROLLER) s21_brick_game.a $(OBJ_FRONTEND) -o $(PROGRAM_NAME).out $(UI_FLAG)

test: s21_brick_game.a $(OBJ_TESTS)
	$(CXX) $(CXXFLAGS) test_main.cpp s21_brick_game.a $(OBJ_TESTS) -o test.out $(GTEST_FLAGS)
	./test.out
	> $(TEST_REPORT)

install: $(PROGRAM_NAME)
	@mkdir -p $(INSTALL_DIR)
	mv brick_game.out $(INSTALL_DIR)/$(PROGRAM_NAME).out

uninstall: 
	rm -f $(INSTALL_DIR)/$(PROGRAM_NAME).out

dist:
	tar -czf $(PROGRAM_NAME).tar.gz $(HEADERS) $(SOURCES_TETRIS_LIBRARY) $(SOURCES_FRONTEND) main.c Makefile

dvi:
	@mkdir -p $(DOCS_DIR)
	doxygen Doxyfile
	open ./docs/html/index.html

gcov_report: $(OBJ_TESTS) $(OBJ_TETRIS_LIBRARY) test_main.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) test_main.cpp $(OBJ_TESTS) $(SOURCES_SNAKE_LIBRARY) $(OBJ_TETRIS_LIBRARY) $(SOURCES_BRICK_GAME) -o report.out $(GTEST_FLAGS)
	./report.out > $(TEST_REPORT)
	lcov $(LCOV_TOOL) -t "gcov_report" -o coverage_report.info -c -d . --ignore-errors inconsistent --no-external
	lcov --remove coverage_report.info 'main.cpp' 'inc/*' -o filtered_coverage_report.info
	genhtml -o ./report filtered_coverage_report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov	
	open ./report/index-sort-f.html

linter: 
	@echo "---\nBasedOnStyle: Google" > .clang-format
	clang-format -n $(shell find . -name "*.cpp" -or -name "*.h")

format:
	@echo "---\nBasedOnStyle: Google" > .clang-format
	clang-format -i $(shell find . -name "*.cpp" -or -name "*.h")

clean:
	-rm -f $(BUILD_DIR)/*.o *.a *.gcno *.gcda *.info *.out *.gcov
	-rm -rf ./report $(BUILD_DIR)
	-rm -rf $(INSTALL_DIR)
	-rm -f $(PROGRAM_NAME).tar.gz
	-rm -f $(TEST_REPORT)
	-rm -f test.txt high_score_tetris.txt high_score_snake.txt .clang-format
	-rm -rf $(DOCS_DIR)

.PHONY: all test install uninstall gcov_report clean dist dvi $(PROGRAM_NAME) linter format