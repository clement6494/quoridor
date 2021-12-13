#include "input.h"

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
        printf("Mauvais choix. Veuillez réessayer :\n");
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
        printf("Entrez le nom du joueur n°%d :\n", (i + 1));
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
        printf("Coordonnées non valide. Veuillez réessayer :\n");
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
        printf("La case choisie n'est pas valide pour la position donnée. Veuillez réessayer :\n");
        coordinate = get_coordinate();
    }
    return coordinate;
}
