#include <stdio.h>
#include <stdlib.h>

#include "header_function.h"

int test_fin_partie ( t_joueur tour_de){


if ((abs(tour_de.lastx-tour_de.depart_x)==17)||(abs(tour_de.lasty-tour_de.depart_y)==17)){
    return 1;
}
else{
    return 0;
}

}
