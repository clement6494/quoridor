#ifndef H_TOOL
#define H_TOOL
    #include <stdbool.h>
    #include <math.h>

    #include "game.h"

    Game* initialize_new_game();
    bool is_wall(char grid[GRID_SIZE][GRID_SIZE], int row, int column);
    bool is_valid_starting_position(StartingPosition starting_position, Coordinate coordinate);
    bool is_valid_coordinate(char user_input[MAX_LEN]);
    bool is_game_finished(Game* ptr_game);
    bool is_move_valid(Game* ptr_game, int current_player_index, Direction direction);
    Coordinate get_direction_offset(Direction direction);
    bool is_coordinate_in_grid(Coordinate coordinate);
    bool is_barrier_valid(Game* ptr_game, Coordinate first_cell, Coordinate second_cell, Direction direction);
    int get_score(char name[]);
#endif // H_TOOL
