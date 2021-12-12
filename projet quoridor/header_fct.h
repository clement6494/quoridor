#ifndef HEADER_FCT_H_INCLUDED
#define HEADER_FCT_H_INCLUDED
#include "header_struct.h"


void greeting();


/**actions possibles*/

void pose();

void bouge(int tab[17][17] ,t_joueur player );

void annule(int tab[17][17], int tabn_l[17][17]);
/*************************************/

void partie(int tab[17][17]);

void affichage(int tab[17][17]);

int debut_tour(int d);

/**tests*/

int joueur_sur_case();
//renvoie 1 si un joueur est sur la case indiquée en parametre
// 0 sinon

int barriere_bloque(int tab[17][17],int x,int y,t_joueur player);
// renvoie 1 si le joueur tente de traverser une barrière.
// 0 sinon
#endif // HEADER_FCT_H_INCLUDED

int test_chemin_possible(int tab[17][17],t_joueur player)
/**renvoie 1 si il reste un chemin possible
pour les joueur apres pose de barriere, 0 sinon*/
