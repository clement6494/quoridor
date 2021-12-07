#ifndef HEADER_FUNCTION_H_INCLUDED
#define HEADER_FUNCTION_H_INCLUDED
#include "header_struct.h"


void greeting();


/**actions possibles*/

void pose();

void bouge(int tab[17][17] /**,t_joueur tour_de*/ );

void annule(int tab[17][17], int tabn_l[17][17]);
/*************************************/

void partie(int tab[17][17]);

void affichage(int tab[17][17]);

int debut_tour(int d);

/**tests*/

int joueur_sur_case();

int barriere_bloque(int tab[17][17],int x,int y,t_joueur tour_de);



#endif // HEADER_FUNCTION_H_INCLUDED

