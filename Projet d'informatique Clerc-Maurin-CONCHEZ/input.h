#ifndef H_INPUT
#define H_INPUT
    #include <time.h>

    #include "game.h"

    int get_choice(int min, int max);
    int get_player_count();
    void register_players(Player players[], int player_count);
    char random_token(char available_tokens[], size_t number_of_tokens);
    Coordinate get_coordinate();
    Coordinate get_starting_coordinate(StartingPosition starting_position);
#endif // H_INPUT
