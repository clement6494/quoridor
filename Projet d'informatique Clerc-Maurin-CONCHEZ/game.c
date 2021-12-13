#include "game.h"

int main(int argc, char* argv[]) {
    menu();
    return 0;
}

/**
 * Lancement du menu principal
 */
void menu() {
    // Affichage du menu
    display_menu();

    // Récupération du choix de l'utilisateur
    int user_choice = get_choice(1, 3);

    printf("\n");

    switch (user_choice) {
        case 1:
            start_new_game();
            break;
        case 2:
            display_help();
            break;
        case 3:
            display_scores();
            break;
        case 4:
        printf("Merci d'avoir joué à Quoridor. A une prochaine fois !\n");
            exit(1);
    }

    // Retour au menu
    menu();
}

/**
 * Lancement d'une nouvelle partie
 * @param players Liste des joueurs de la partie
 */
void start_new_game() {
    // Initialisation du jeu
    Game* ptr_game = initialize_new_game();

    // Premier tour
    first_round(ptr_game);
    display_grid(ptr_game->grid);

    // Tour à tour
    int current_player_index = ptr_game->player_count - 1;
    while (!is_game_finished(ptr_game)) {
        // Mise à jour de l'indice du prochain joueur
        current_player_index = (current_player_index + 1)%ptr_game->player_count;

        // Affichage des informations du joueur
        display_player_information(ptr_game, current_player_index);

        // Tour du prochain joueur
        next_round(ptr_game, current_player_index);

        // Affichage de la grille
        display_grid(ptr_game->grid);
    }
    // Indication du gagnant
    printf("Le joueur %s a gagné la partie !\n\n", ptr_game->players[current_player_index].name);

    // Libération du pointeur
    free(ptr_game);
}

/**
 * Premier tour
 * @param ptr_game Pointeur sur la structure Game
 */
void first_round(Game* ptr_game) {
    StartingPosition starting_positions[ptr_game->player_count];

    if (ptr_game->player_count == 2) {
        starting_positions[0] = FIRST_ROW;
        starting_positions[1] = LAST_ROW;
    } else {
        starting_positions[0] = FIRST_ROW;
        starting_positions[1] = LAST_COLUMN;
        starting_positions[2] = LAST_ROW;
        starting_positions[3] = FIRST_COLUMN;
    }

    for (int i = 0; i < ptr_game->player_count; i++) {
        printf("C'est au tour de %s de choisir sa position de départ.\n", ptr_game->players[i].name);
        ptr_game->players[i].coordinate = get_starting_coordinate(starting_positions[i]);
        ptr_game->players[i].starting_position = starting_positions[i];
        ptr_game->grid[2*ptr_game->players[i].coordinate.row][2*ptr_game->players[i].coordinate.column] = ptr_game->players[i].token;
        printf("\n");
    }
}

/**
 * Prochain tour
 * @param ptr_game Pointeur sur la structure Game
 * @param current_player_index Indice du joueur
 */
void next_round(Game* ptr_game, int current_player_index) {
    // Affichage du menu
    printf("C'est à %s (%c) de jouer :\n", ptr_game->players[current_player_index].name, ptr_game->players[current_player_index].token);
    display_player_menu();

    // Récupération du choix
    int user_choice = get_choice(1, 3);

    printf("\n");

    switch (user_choice) {
        case 1:
            move(ptr_game, current_player_index);
            break;
        case 2:
            // Vérification du nombre de barrières du joueur
            if (ptr_game->players[current_player_index].remaining_barrier > 0) {
                place_barrier(ptr_game, current_player_index);
            } else {
                printf("Vous n'avez pas assez de barrières. Vous passez votre tour.\n");
            }
            break;
        case 3:
            miss_turn(ptr_game, current_player_index);
            break;
    }
}

/**
 * Action de déplacer un pion
 * @param ptr_game Pointeur sur la structure Game
 * @param current_player_index Indice du joueur
 */
void move(Game* ptr_game, int current_player_index) {
    // Affichage du menu des mouvements
    printf("Choisissez votre déplacement :\n");
    display_move_menu();
    int user_choice = get_choice(1, 4);
    while (!is_move_valid(ptr_game, current_player_index, user_choice)) {
        printf("\nLe mouvement choisi n'est pas valide. Veuillez en réessayer :\n");
        display_move_menu();
        user_choice = get_choice(1, 4);
    }
    printf("\n");

    // Suppression du pion du joueur sur l'ancienne position
    ptr_game->grid[2*ptr_game->players[current_player_index].coordinate.row][2*ptr_game->players[current_player_index].coordinate.column] = ' ';

    // Mouvement
    Coordinate offset = get_direction_offset(user_choice);

    // Calcul du nouveau couple ligne / colonne
    int new_row = ptr_game->players[current_player_index].coordinate.row + offset.row;
    int new_column = ptr_game->players[current_player_index].coordinate.column + offset.column;

    // Ajustement si un joueur se situe sur la trajectoire
    if (ptr_game->grid[2*new_row][2*new_column] != ' ') {
        new_row += offset.row;
        new_column += offset.column;
    }

    // Mise à jour du couple ligne / colonne
    ptr_game->players[current_player_index].coordinate.row = new_row;
    ptr_game->players[current_player_index].coordinate.column = new_column;

    // Ajout du pion sur la nouvelle position
    ptr_game->grid[2*new_row][2*new_column] = ptr_game->players[current_player_index].token;
}

/**
 *
 * @param ptr_game Pointeur sur la structure Game
 * @param current_player_index Indice du joueur
 */
void place_barrier(Game* ptr_game, int current_player_index) {
    Coordinate first_cell, second_cell;
    Direction direction;
    do {
        printf("Choix d'une première case :\n");
        first_cell =  get_coordinate();
        printf("\nChoix d'une deuxième case :\n");
        second_cell =  get_coordinate();
        printf("\nChoisissez votre déplacement :\n");
        display_move_menu();
        direction = get_choice(1, 4);
        printf("\n");
    } while (!is_barrier_valid(ptr_game, first_cell, second_cell, direction));

    // Placement de la barrière
    Coordinate offset = get_direction_offset(direction);
    Coordinate first_barrier_cell = {2*first_cell.row + offset.row, 2*first_cell.column + offset.column};
    Coordinate second_barrier_cell = {2*second_cell.row + offset.row, 2*second_cell.column + offset.column};
    ptr_game->grid[first_barrier_cell.row][first_barrier_cell.column] = 'B';
    ptr_game->grid[second_barrier_cell.row][second_barrier_cell.column] = 'B';

    // Mise à jour du nombre de barrières du joueur
    ptr_game->players[current_player_index].remaining_barrier --;
}

/**
 * Action de passer son tour
 * @param ptr_game Pointeur sur la structure Game
 * @param current_player_index Indice du joueur
 */
void miss_turn(Game* ptr_game, int current_player_index) {
    printf("%s a décidé de passer son tour.\n\n", ptr_game->players[current_player_index].name);
}
