#include <stdio.h>
#include <stdlib.h>

#include "header_function.h"


void greeting()
{
    printf("bienvenue nouveau joueur");
}

void partie(int tab[17][17])
{
    int tour=0;
    int fin_partie=1;
    int action;

    while (fin_partie!== 0)
    {
        action=debut_tour(tour);
        if action==1;
    pose();
        if action==2;
    bouge();
        if action==3;
    annule();
        if action==4;
    passe();
        tour+=1;
        test_fin_partie();
    }

}



int debut_tour(int d)
{
    t_joueur tour_de;
    int action;
    if d%2==0;
tour_de= joueur1;
if d%2==1;
tour_de= joueur2;

affiche_msg_tour(tour_de.nom);
    scanf(("%d",&action);
          if (tour_de.barriere==0)
{
    while ((action>1)&&(action<=6))
        {
            scanf("%d",&action);
        }
    }
    else
    {
        while ((action>=1)&&(action<=6))
        {
            scanf("%d",&action);
        }
    }
    return (action);
}
/*Il faut coder ttes les fonctions
coder*
pose()
annule()
bouge()
test_fin_partie()*/
