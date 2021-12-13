#include "tool.h"

/**
 * Initialisation d'une nouvelle partie
 * @return Partie
 */
Game* initialize_new_game() {
    // Création du jeu
    Game* ptr_game = (Game*)malloc(sizeof(Game));

    // Initialisation de la grille
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            ptr_game->grid[i][j] = ' ';
        }
    }

    // Obtention du nombre de joueurs
    ptr_game->player_count = get_player_count();

    // Enregistrement des joueurs
    ptr_game->players = (Player*)calloc(ptr_game->player_count, sizeof(Player));
    register_players(ptr_game->players, ptr_game->player_count);

    return ptr_game;
}

/**
 * Indique si l'élément est un mur
 * @return Indication sur la nature de l'élément
 */
bool is_barrier(char grid[GRID_SIZE][GRID_SIZE], int row, int column) {
    return grid[row][column] == 'B';
}

/**
 * Indique si les coordonnées rentrées par l'utilisateur sont valides (exemple : A1, B4, I9...)
 * @return Validité des coordonnées
 */
bool is_valid_coordinate(char user_input[MAX_LEN]) {
    return 'A' <= user_input[0] && user_input[0] <= 'I' && '1' <= user_input[1] && user_input[1] <= '9' ;
}

/**
 * Indique si les coordonnées sont valide pour la position de départ
 * @return Indication sur la validité des coordonnées
 */
bool is_valid_starting_position(StartingPosition starting_position, Coordinate coordinate) {
    switch(starting_position) {
        case FIRST_ROW:
            return coordinate.row == 0;
        case LAST_ROW:
            return coordinate.row == 8;
        case FIRST_COLUMN:
            return coordinate.column == 0;
        case LAST_COLUMN:
            return coordinate.column == 8;
        default:
            return false;
    }
}

/**
 * Vérification de l'état de la partie
 * @param ptr_game Pointeur sur la structure Game
 */
bool is_game_finished(Game* ptr_game) {
    for (int i = 0; i < ptr_game->player_count; i++) {
        switch (ptr_game->players[i].starting_position) {
            case FIRST_ROW:
                if (ptr_game->players[i].coordinate.row == 8)
                    return true;
                break;
            case LAST_ROW:
                if (ptr_game->players[i].coordinate.row == 0)
                    return true;
                break;
            case FIRST_COLUMN:
                if (ptr_game->players[i].coordinate.column == 8)
                    return true;
                break;
            case LAST_COLUMN:
                if (ptr_game->players[i].coordinate.column == 0)
                    return true;
                break;
        }
    }
    return false;
}

/**
 * Vérification de la validité du déplacement
 * @param ptr_game Pointeur sur la structure Game
 * @param current_player_index Indice du joueur
 * @param to Position d'arrivée
 */
bool is_move_valid(Game* ptr_game, int current_player_index, Direction direction) {
    // Obtention des coordonnées de déplacement
    Coordinate offset = get_direction_offset(direction);

    // Obtention des deux prochaines cases de la trajectoire
    Coordinate first_cell = {ptr_game->players[current_player_index].coordinate.row + offset.row,
                             ptr_game->players[current_player_index].coordinate.column + offset.column};
    Coordinate second_cell = {ptr_game->players[current_player_index].coordinate.row + 2*offset.row,
                              ptr_game->players[current_player_index].coordinate.column + 2*offset.column};

    // Obtention des statuts des barrières
    bool is_barrier_before_first_cell = !is_coordinate_in_grid(first_cell)
            || is_barrier(ptr_game->grid, 2*first_cell.row - offset.row, 2*first_cell.column - offset.column);
    bool is_barrier_before_second_cell = !is_coordinate_in_grid(second_cell)
            || is_barrier_before_first_cell || is_barrier(ptr_game->grid, 2*second_cell.row - offset.row, 2*second_cell.column - offset.column);

    // Vérification si un joueur se trouve sur la trajectoire
    bool is_player_in_first_cell = ptr_game->grid[first_cell.row][first_cell.column] != ' ';
    bool is_player_in_second_cell = ptr_game->grid[second_cell.row][second_cell.column] != ' ';

    // Vérification qu'il n'y a pas de barrière sur la trajectoire
    return (!is_player_in_first_cell && !is_barrier_before_first_cell) ||
        (is_player_in_first_cell && !is_player_in_second_cell && !is_barrier_before_second_cell);
}

/**
 * Obtention des coordonnées de déplacement en fonction de la direction
 * @param direction Direction
 */
Coordinate get_direction_offset(Direction direction) {
    Coordinate coordinate = {0, 0};
    switch (direction) {
        case UP:
            coordinate.row = -1;
            break;
        case RIGHT:
            coordinate.column = 1;
            break;
        case DOWN:
            coordinate.row = 1;
            break;
        case LEFT:
            coordinate.column = -1;
            break;
    }
    return coordinate;
}

/**
 * Vérification qu'une coordonnée se situe dans la grille
 * @param coordinate Coordonnée
 */
bool is_coordinate_in_grid(Coordinate coordinate) {
    return 0 <= coordinate.row && coordinate.row <= 8 &&
           0 <= coordinate.column && coordinate.column <= 8;
}

/**
 * Vérification de la validité d'un positionnement de barrière
 * @param ptr_game Pointeur sur la structure Game
 * @param first_cell Première case
 * @param second_cell Deuxième case
 * @param direction Direction
 */
bool is_barrier_valid(Game* ptr_game, Coordinate first_cell, Coordinate second_cell, Direction direction) {
    // Vérifie que les cases sont côte à côte
    if (abs(first_cell.row - second_cell.row) + abs(first_cell.column - second_cell.column) != 1) {
        printf("Les cases ne sont pas côtes à côtes. Veuillez recommencer :\n");
        return false;
    }

    // Vérifie que la direction est valide pour les cases
    if ((first_cell.row == second_cell.row && (direction == RIGHT || direction == LEFT))
        || (first_cell.row != second_cell.row && (direction == UP || direction == DOWN))) {
        printf("La direction choisie n'est pas compatible avec le positionnement des cases. Veuillez réessayer :\n");
        return false;
    }

    // Vérifie qu'aucune barrière ne se trouve sur les cases considérées
    Coordinate offset = get_direction_offset(direction);
    Coordinate first_barrier_cell = {2*first_cell.row + offset.row, 2*first_cell.column + offset.column};
    Coordinate second_barrier_cell = {2*second_cell.row + offset.row, 2*second_cell.column + offset.column};
    if (ptr_game->grid[first_barrier_cell.row][first_barrier_cell.column] != ' ' ||
        ptr_game->grid[second_barrier_cell.row][second_barrier_cell.column] != ' ') {
        printf("Il y a collision avec une barrière existante. Veuillez réessayer :\n");
        return false;
    }

    return true;
}

/**
 * Accesseur du score d'un personnage
 * @param name Nom
 */
int get_score(char name[]) {
    FILE* file;
    file = fopen("../src/scores.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, file))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        char* token = strtok(buffer, " ");

        // Vérification de la correspondance
        if (strcmp(name, token) == 0) {
            token = strtok(NULL, " ");
            return atoi(token);
        }
    }

    fclose(file);
    return 0;
}
