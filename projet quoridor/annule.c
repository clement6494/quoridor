#include <stdio.h>
#include <stdlib.h>

#include "header_function.h"

void annule(int tab[17][17], int tabn_l[17][17]){
int i,j;
int tabtemp[17][17];

// on enregistre le plateau du tour dans un tableau temporaire
for (i=0;i<17;i++){
   for (i=0;i<17;i++){
    tabtemp[i][j]=tab[i][j];
   }
}
// on enregistre le plateau du tour precedent dans le tableau du tour
for (i=0;i<17;i++){
   for (i=0;i<17;i++){
    tab[i][j]=tabn_l[i][j];
   }
}
// on enregistre le plateau du tour dans le tableau du tour precedent
for (i=0;i<17;i++){
   for (i=0;i<17;i++){
    tabn_l[i][j]=tabtemp[i][j];
   }
}

}
