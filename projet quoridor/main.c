#include <stdio.h>
#include <stdlib.h>
#include "header_function.h"
#include <windows.h>
#include <time.h>
#include<string.h>

int main()
{
    int tab[17][17];
    int i,j;
    printf("Hello world!\n");
    for (i=0; i<17; i++)                   //on enregistre tour precedent
    {
        for (j=0; j<17; j++)
        {
            tab[i][j]=0;
        }

    }
    greeting();
    return 0;
}
