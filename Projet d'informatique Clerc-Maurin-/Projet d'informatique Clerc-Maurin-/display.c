#include "display.h"
#include "tool.h"
#include "game.h"
#include "input.h"

/**
 * Affiche le menu principal du jeu Quoridor
 */
void display_menu() {
    printf("Quoridor :\n");
    printf("1 - Lancer une nouvelle partie\n");
    printf("2 - Afficher l aide\n");
    printf("3 - Afficher les scores\n");
    printf("4 - Quitter le jeu\n");
}

/**
 * Affiche les actions disponibles
 */
void display_player_menu() {
    printf("1 - Deplacer son pion\n");
    printf("2 - Poser une barriere\n");
    printf("3 - Passer son tour\n");
}

/**
 * Affichage du menu des mouvements
 */
void display_move_menu() {
    printf("1 - Haut\n");
    printf("2 - Droite\n");
    printf("3 - Bas\n");
    printf("4 - Gauche\n");
}

/**
 * Affichage d'informations sur la partie
 * @param ptr_game Pointeur sur la structure Game
 * @param current_player_index Indice du joueur
 */
void display_player_information(Game* ptr_game, int current_player_index) {
    printf("Nombre de joueurs : %d\n", ptr_game->player_count);
    printf("Joueur : %s\n", ptr_game->players[current_player_index].name);
    printf("Score partie : %d\n", ptr_game->players[current_player_index].score);
    printf("Jeton : %c\n", ptr_game->players[current_player_index].token);
    printf("Barrieres restante : %d\n\n", ptr_game->players[current_player_index].remaining_barrier);
}

/**
 * Affichage de la grille
 * @param grid Grille
 */
void display_grid(char grid[GRID_SIZE][GRID_SIZE]) {
    printf("   | A | | B | | C | | D | | E | | F | | G | | H | | I |\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("--------------------------------------------------------\n");
        display_intermediary_line(grid, i);

        printf(" %c |", i%2 == 0 ? 49 + i/2 : ' ');
        for (int j = 0; j < GRID_SIZE; j++) {
            if (j%2 == 1) {
                printf("%c|", grid[i][j]);
            } else {
                if (i%2 == 0) {
                    printf(" %c |", grid[i][j]);
                } else {
                    printf("%c%c%c|", grid[i][j], grid[i][j], grid[i][j]);
                }
            }
        }
        printf("\n");

        display_intermediary_line(grid, i);
    }
    printf("--------------------------------------------------------\n\n");
}

/**
 * Affichage d'une ligne intermédiaire
 * @param i Ligne
 */
void display_intermediary_line(char grid[GRID_SIZE][GRID_SIZE], int i) {
    if (i%2 == 0) {
        printf("   |");
        for (int j = 0; j < GRID_SIZE; j++) {
            if (j%2 == 1) {
                printf("%c|", grid[i][j]);
            } else {
                printf("   |");
            }
        }
        printf("\n");
    }
}

/**
 * Affichage de la position de départ
 * @param starting_position Position de départ
 */
void display_starting_position(StartingPosition starting_position) {
    printf("Choisissez une case sur la ");
    switch(starting_position) {
        case FIRST_ROW:
            printf("premiere ligne (ligne 1) :\n");
            break;
        case LAST_ROW:
            printf("derniere ligne (ligne 9) :\n");
            break;
        case FIRST_COLUMN:
            printf("premiere colonne (colonne A) :\n");
            break;
        case LAST_COLUMN:
            printf("derniere colonne (colonne I) :\n");
            break;
    }
}

/**
 * Affichage de l'aide
 */
void display_help() {
    printf("AIDE :\n\n");
    printf("PRINCIPE DU JEU : \n\n");
    printf("Le 1er joueur qui commencera la partie sera tire au hasard.\n");
    printf("Il placera son pion sur une case de la 1ere ligne du plateau situe devant lui.\n");
    printf("Ce sera au joueur suivant de placer son pion et ainsi de suite.");

    printf("\n\nACTIONS :\n\n");
    printf("Chaque joueur choisit, a tour de role, de :\n");
    printf("- Deplacer son pion d'une case, verticalement ou horizontalement, en avant ou en arriere\n");
    printf("- Poser une de ses barrieres entre deux blocs de cases : verticalement ou horizontalement\n");
    printf("- Passer son tour;\n");

    printf("\n\nREGLES :");

    printf("\n\nSE DEPLACER :\n\n");
    printf("Un deplacement ne se fera entre deux cases que si aucune barriere n est presente entre elles.\n");
    printf("Si le deplacement est possible alors le pion change de case, sinon, le joueur rejoue.\n");
    printf("Si deux pions sont l un en face de l autre et leur case n est pas separee par une barriere. ");
    printf("du joueur passe au-dessus de son adversaire et prend la prochaine case vide. Cette derniere ");
    printf("est situee dans la meme direction si aucune barriere n est placee apres le pion survole sinon ");
    printf("le joueur pourra bifurquer a gauche ou a droite selon son choix et selon les eventuelles barrieres presentent");
    printf("\nDans le cas ou la partie se fait avec 4 joueurs, il n est pas possible de sauter plus d un pion a la fois.");
    printf("\nEn cas de blocage de la partie : Il n y aucun gagnant.");

    printf("\n\nPOSER UNE BARRIERE :\n\n");
    printf("Ceci est possible tant que le joueur a encore des barrieres dans sa zone de reserve.");
    printf("\nLe but de la barriere est de creer son propre chemin ou de ralentir un adversaire. Dans ce");
    printf("dernier cas, il est interdit de fermer totalement l acces a la ligne de but de son(ses) adversaire(s).");

    printf("\n\nMATERIEL:\n\n");
    printf("- 1 plateau de jeu de 9x9 cases\n");
    printf("- 4 pions\n");
    printf("- 20 barrieres\n\n");
}

/**
 * Afficher les scores
 */
int display_scores() {
    FILE* file;
    file = fopen("scores.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, file))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        char* token = strtok(buffer, " ");
        printf("%s\n", token);
        token = strtok(NULL, " ");
        printf("%s\n", token);
    }

    fclose(file);
    printf("\n");
    return 0;
}

/**
 * Accesseur du choix du joueur
 * @param min Choix minimum
 * @param max Choix maximum
 * @return Choix du joueur
 */
int get_choice(int min, int max) {
    int choice;
    scanf("%d", &choice);
    while (choice < min || choice > max) {
        printf("Mauvais choix. Veuillez reessayer :\n");
        scanf("%d", &choice);
    }
    return choice;
}

/**
 * Accesseur du nombre de joueurs
 * @return Nombre de joueurs
 */
int get_player_count() {
    int choice;
    printf("Choisissez le type de partie : \n1 - 2 joueurs\n2 - 4 joueurs\n");
    int player_count = 2*get_choice(1, 2);
    printf("\n");
    return player_count;
}

/**
 * Enregistrement des joueurs
 * @param players Liste des joueurs
 * @param player_count Nombre de joueurs
 */
void register_players(Player players[], int player_count) {
    char available_tokens[] = {'@', '*', '#', '&', '%', '?', '$'};
    size_t number_of_tokens = sizeof(available_tokens) / sizeof(char);
    for (int i = 0; i < player_count; i++) {
        char name[MAX_LEN];
        printf("Entrez le nom du joueur n%d :\n", (i + 1));
        scanf("%s", name);
        strcpy(players[i].name, name);
        players[i].score = get_score(name);
        players[i].token = random_token(available_tokens, number_of_tokens);
        players[i].remaining_barrier = INITIAL_BARRIER_COUNT;
        printf("\n");
    }
}

/**
 * Génération aléatoire d'un jeton
 * @param available_tokens Jetons disponibles
 * @return Jeton aléatoire
 */
char random_token(char available_tokens[], size_t number_of_tokens) {
    time_t t;
    srand((unsigned) time(&t));
    int index;
    do {
        index = (int)((double)rand() / ((double)RAND_MAX + 1) * number_of_tokens);
    } while (available_tokens[index] == ' ');
    char token = available_tokens[index];
    available_tokens[index] = ' ';
    return token;
}

/**
 * Accesseur des coordonnées d'une case
 * @return Coordonnées
 */
Coordinate get_coordinate() {
    Coordinate coordinate;
    char user_input[MAX_LEN];
    scanf("%s", user_input);
    while (!is_valid_coordinate(user_input)) {
        printf("Coordonnees non valide. Veuillez reessayer :\n");
        scanf("%s", user_input);
    }
    coordinate.row = user_input[1] - '1';
    coordinate.column = user_input[0] - 'A';
    return coordinate;
}

/**
 * Accesseur de la case de départ en fonction de la position de départ
 * @param starting_position Position de départ
 * @return Coordonnées de la case de départ
 */
Coordinate get_starting_coordinate(StartingPosition starting_position) {
    display_starting_position(starting_position);
    Coordinate coordinate = get_coordinate();
    while (!is_valid_starting_position(starting_position, coordinate)) {
        printf("La case choisie n est pas valide pour la position donnee. Veuillez reessayer :\n");
        coordinate = get_coordinate();
    }
    return coordinate;
}

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
        printf("Les cases ne sont pas cotes a cotes. Veuillez recommencer :\n");
        return false;
    }

    // Vérifie que la direction est valide pour les cases
    if ((first_cell.row == second_cell.row && (direction == RIGHT || direction == LEFT))
        || (first_cell.row != second_cell.row && (direction == UP || direction == DOWN))) {
        printf("La direction choisie n est pas compatible avec le positionnement des cases. Veuillez reessayer :\n");
        return false;
    }

    // Vérifie qu'aucune barrière ne se trouve sur les cases considérées
    Coordinate offset = get_direction_offset(direction);
    Coordinate first_barrier_cell = {2*first_cell.row + offset.row, 2*first_cell.column + offset.column};
    Coordinate second_barrier_cell = {2*second_cell.row + offset.row, 2*second_cell.column + offset.column};
    if (ptr_game->grid[first_barrier_cell.row][first_barrier_cell.column] != ' ' ||
        ptr_game->grid[second_barrier_cell.row][second_barrier_cell.column] != ' ') {
        printf("Il y a collision avec une barriere existante. Veuillez reessayer :\n");
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

/**
 * Action de déplacer un pion
 * @param ptr_game Pointeur sur la structure Game
 * @param current_player_index Indice du joueur
 */
void move(Game* ptr_game, int current_player_index) {
    // Affichage du menu des mouvements
    printf("Choisissez votre deplacement :\n");
    display_move_menu();
    int user_choice = get_choice(1, 4);
    while (!is_move_valid(ptr_game, current_player_index, user_choice)) {
        printf("\nLe mouvement choisi n'est pas valide. Veuillez en reessayer :\n");
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
        printf("Choix d'une premiere case :\n");
        first_cell =  get_coordinate();
        printf("\nChoix d'une deuxieme case :\n");
        second_cell =  get_coordinate();
        printf("\nChoisissez votre deplacement :\n");
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
    printf("%s a decide de passer son tour.\n\n", ptr_game->players[current_player_index].name);
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
        printf("C'est au tour de %s de choisir sa position de depart.\n", ptr_game->players[i].name);
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
    printf("C'est a %s (%c) de jouer :\n", ptr_game->players[current_player_index].name, ptr_game->players[current_player_index].token);
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
                printf("Vous n avez pas assez de barrieres. Vous passez votre tour.\n");
            }
            break;
        case 3:
            miss_turn(ptr_game, current_player_index);
            break;
    }
}


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
        printf("Merci d'avoir joue à Quoridor. A une prochaine fois !\n");
            exit(1);
    }

    // Retour au menu
    menu();
}
