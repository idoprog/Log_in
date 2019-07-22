#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <signal.h>


#include "ui_funcs.h"
#include "help_funcs.h"


int main(){
    setlocale(LC_ALL, "");
    signal(SIGINT, SigintHandler);
    OpeningScreen(200000);
    for (; ;) {
        usleep(50000);
        fflush(stdout);
        if(lines != GetLines() || cols != GetCols()){
            OpeningScreen(0);
        }
    }
}

