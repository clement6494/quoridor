#include <stdio.h>
#include <stdlib.h>
#include "header_function.h"
#include <windows.h>
#include <time.h>
#include<string.h>



void pose()
{

//variables**************
    int x1;
    char yc1;
    int x2;
    char yc2;
    int y1,y2;
    int taille_mur;
    /*************************/
//selection position des deux extremites du  mur
    clear_entete_bas();
    decale_axes();

    printf("selectionnez la premiere colonne *s", tour_de.nom);
    scanf("%d",x1);
    while ((x1<=1)||(x1>8))
    {
        scanf("%d",x1);
    }

    printf("selectionnez la premiere ligne *s", tour_de.nom);
    scanf("%c",yc1);
    while ((yc1<A)||((yc1>H)&&(yc1<a))||(yc1>h))
    {
        scanf("%c",yc1);
    }

    do
    {
        printf("selectionnez la seconde colonne *s", tour_de.nom);
        scanf("%d",x);
        while ((x2<=1)||(x2>8))
        {
            scanf("%d",x);
        }

        printf("selectionnez la seconde ligne *s", tour_de.nom);
        scanf("%c",yc2);
        while ((yc2<A)||((yc2>H)&&(yc2<a))||(yc2>h))
        {
            scanf("%c",yc2);
        }

        /*************************/

        if ((y1<A))||(y1>I));
            yc1+=32;

            if ((y2<A))||(y2>I));
                yc2+=32;
            }
    While ((x1==x2)&&(yc1==yc2));    //blindage les dux extremites sont differentes
    /******************************************************************************/
//on convertis les la lettre de ligne en numero
    y1=(int)(yc1) -96;
    y2=(int) (yc2) -96;
    taille_mur=abs(x1 - x2)+abs(y1 - y2);
    if taille_mur!==1
{
    printf("le mur doit etre rectiligne et couvrir deux case seulement");
        void pose(int tab[17][17]);
    }
    else
    {
//test superposition

        if ((tab[y1*2-1][x1*2-1]==1)||(tab[y2*2-1][x2*2-1]))
        {
            printf("les murs ne doivent pas se superposer");
            void pose(int tab[17][17]);
        }
        else
        {
            int i,j;
            int tab_pose[17][17];
            int test_pose=1;
            //test chemin toujours possible pour les joueurs
            for (i=0; i<17; i++)                   //creation d un tableau test temporaire
            {
                for (j=0; j<17; j++)
                {
                    tab_pose[i][j]=tab[i][j];
                }
            }
            tab_pose[y1*2-1][x1*2-1]=1;
            tab_pose[y2*2-1][x2*2-1]=1;
            for (i=0; i<nombre_de_joueurs; i++)
            {

                test_pose=test_chemin_possible(tab_pose[17][17],i);
            }
            if test_pose=1
        {
            for (i=0; i<17; i++)                   //on enregistre tour precedent
                {
                    for (j=0; j<17; j++)
                    {
                        tabn_1[i][j]=tab[i][j];
                    }
                    tab[y1*2-1][x1*2-1]=1;                //on pose le mur
                    tab[y2*2-1][x2*2-1]=1;
                    recale_axes();                            // on replace les axes
                }
            }
            else
            {
                printf("la barriere enferme un joueur, choississez un autre emplacement");
                void pose(int tab[17][17]);

            }
        }
    }

}




