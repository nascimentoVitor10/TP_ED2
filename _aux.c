#include <stdio.h>
#include <stdlib.h>
#include "aux.h"

void limparTela() {
    #ifdef _WIN32
        system("cls");
    
    #else
        system("clear");
    
    #endif
    printf("\033[H\033[2J");
}