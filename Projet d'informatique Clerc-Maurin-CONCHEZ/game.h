#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "display.h"
#include "input.h"
#include "tool.h"

#ifndef GRID_SIZE
#define GRID_SIZE 17
#endif // GRID_SIZE

#ifndef MAX_LEN
#define MAX_LEN 80
#endif // MAX_LEN

#ifndef INITIAL_BARRIER_COUNT
#define INITIAL_BARRIER_COUNT 20
#endif // INITIAL_BARRIER_COUNT

#ifndef H_GAME
#define H_GAME
    typedef enum StartingPosition StartingPosition;
    enum StartingPosition {
        FIRST_ROW,
        FIRST_COLUMN,
        LAST_ROW,
        LAST_COLUMN
    };

    typedef enum Direction Direction;
    enum Direction {
        UP = 1,
        RIGHT = 2,
        DOWN = 3,
        LEFT = 4
    };

    typedef struct Coordinate Coordinate;
    struct Coordinate {
        int row;
        int column;
    };

    typedef struct Player Player;
    struct Player {
        char name[MAX_LEN];
        StartingPosition starting_position;
        Coordinate coordinate;
        int score;
        char token;
        int remaining_barrier;
    };

    typedef struct Game Game;
    struct Game {
        int player_count;
        Player* players;
        char grid[17][17];
    };
#endif // H_GAME

void menu();
void start_new_game();
void first_round(Game* ptr_game);
void next_round(Game* ptr_game, int current_player_index);
void move(Game* ptr_game, int current_player_index);
void place_barrier(Game* ptr_game, int current_player_index);
void miss_turn(Game* ptr_game, int current_player_index);
