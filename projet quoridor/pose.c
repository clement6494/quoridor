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

    printf("selectionnez la premiere colonne, *s", tour_de->nom);
    scanf("%d",x1);
    while ((x1<=1)||(x1>8))
    {
        scanf("%d",x1);
    }

    printf("selectionnez la premiere ligne, *s", tour_de->nom);
    scanf("%c",yc1);
    while ((yc1<A)||((yc1>H)&&(yc1<a))||(yc1>h))
    {
        scanf("%c",yc1);
    }

    do
    {
        printf("selectionnez la seconde colonne, *s", tour_de->nom);
        scanf("%d",x);
        while ((x2<=1)||(x2>8))
        {
            scanf("%d",x);
        }

        printf("selectionnez la seconde ligne, *s", tour_de->nom);
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

                test_pose=test_chemin_possible(tab_pose,joueur[i]);
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
                    recale_axes();
                    tour_de->murs_dispo-=1                           // on replace les axes
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


int test_chemin_possible(int tab[17][17],t_joueur player)
{
    /** on va compter le nombre de deplacements effectues par le bot, si il fait 81 deplacements (le nombres de cases sur le plateau )
    alors on pose l'hypothese qu'il n'y a pas d'issus (faux mathematiquement mais tres peu probable)*/
    int tours=0;

    t_joueur bot=player;

    int x0,y0;  //position de depart pour voir si fini partie
    x0= bot->depart_x;
    y0= bot->depart_y;

    int x,y;    //on initialise la position du bot
    x= bot->lastx;
    y= bot->lasty;

    int bot_success=0; //variable test si le bot fini le jeu
    int i,j;
    int gauche=0,droite=0,haut=0,bas=0;
    while ((tours<=81)||(bot_success==1))
    {
        //on cherche d'abord a atteindre une extremité du plateau
        for (i=(x-1)*2; i>=2; i-=2) //cherche extremité gauche
        {
            if tab[i]==1
            {
                gauche=1;
            }
        }
        if (gauche==0)
        {
            x=1;
        }
        else
        {
            for (i=(x-1)*2; i<=8; i+=2) //cherche extremité droite
            {
                if tab[i]==1
                {
                    droite=1;
                }
            }
            if (droite==0)
            {
                x=9;
            }
            else
            {
                for (i=(y-1)*2; i<=2; i-=2) //cherche extremité haut
                {
                    if tab[i]==1
                    {
                        haut=1;
                    }
                }
                if (haut==0)
                {
                    y=1;
                }
                else
                {
                    for (i=(y-1)*2; i<=8; i+=2) //cherche extremité bas
                    {
                        if tab[i]==1
                        {
                            bas=1;
                        }
                    }
                    if (bas==0)
                    {
                        y=9;
                    }
                }
            }
        }

        //si on peu pas algo de traversee de labyrinthe en longeant le mur a gauche.





        tours+=1;
    }

    return 0;
}

