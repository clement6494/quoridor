#include <stdio.h>
#include <stdlib.h>

void bouge(int tab[17][17] ,t_joueur tour_de );

void bouge(int tab[17][17], t_joueur tour_de ){
int x;
char y;
int distance;

// selection case prochain coup
clear_entete_bas();
printf("selectionnez une colonne");
do {scanf("%d",x);
}
while ((x<=1)||(x>9));                  //blindage saisie colonne


printf("selectionnez une colonne");

do {scanf("%c",y);
}
while ((y<A)||((y>I)&&(y<a))||(y>i));  //blindage saisie ligne plus conversion des majs en minuscules
if ((y<A))||(y>I)){
y+=32;}

distance=abs(x- tour_de.lastx)+abs(y- tour_de.lasty);    //calcul de la distance parcouru
if (distance==0){                                         // aucun deplacement
        printf("vous etes deja sur cette case");
    bouge(int tab[17][17], t_joueur tour_de );
}
if (distance>2){
    printf("TROP LOIN !!!");                            //on ne peux pas se deplacer sur plus de 2 cases
    bouge(int tab[17][17], t_joueur tour_de );}

if (distance==2){                                      // on teste si on enjambe bien un joueur et si deplacement possible
    if ((joueur_entre(nombre_de_joueurs)==1)&&(barrière_bloque(tabn[17][17])==0)&&(joueur_sur_case()==0)){
       tabn_l[17][17]=tabn[17][17];                    //on sauvegarde le tour n-1
       tabn[x][y-48]=tabn[lastx][lasty];               //on sauvegarde ce tour
        tabn[lastx][lasty]=0;
        affichage_pion(int x, char y);                  //affiche la nouvelle position joueur
    else {
        printf("mouvement impossible");
        bouge(int tab[17][17], t_joueur tour_de )
    }
    }
if (distance==1){                                         //on teste si deplacement possible
    if ((barrière_bloque(tabn[17][17])==0)&&(joueur_sur_case(tabn[17][17])==0)){
       tabn_l[17][17]=tabn[17][17];                       //on sauvegarde le tour n-1
       tabn[x][y-48]=tabn[lastx][lasty];                  //on sauvegarde ce tour
        tabn[lastx][lasty]=0;
        affichage_pion(int x, char y);                  //affiche la nouvelle position joueur
    else {
        printf("mouvement impossible");
        bouge(int tab[17][17], t_joueur tour_de )
    }
    }
}

}
