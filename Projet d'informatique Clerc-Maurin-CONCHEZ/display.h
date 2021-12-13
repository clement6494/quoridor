#ifndef H_DISPLAY
#define H_DISPLAY
    #include <stdio.h>

    #include "game.h"

    void display_player_menu();
    void display_menu();
    void display_move_menu();
    void display_player_information(Game* ptr_game, int current_player_index);
    void display_grid(char grid[GRID_SIZE][GRID_SIZE]);
    void display_intermediary_line(char grid[GRID_SIZE][GRID_SIZE], int i);
    void display_starting_position(StartingPosition starting_position);
    void display_help();
    int display_scores();
#endif //H_DISPLAY
