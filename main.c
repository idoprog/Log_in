#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "ui_funcs.h"
#include "help_funcs.h"

void OpeningScreen();
void UpdateSize();
void Clear();

int main(){
    setlocale(LC_ALL, "");
    OpeningScreen();
    atexit(Clear);
    for (; ;) {
        usleep(50000);
        if(lines != (int) strtol(run_cmd("tput lines", 3), NULL, 10) || cols != (int) strtol(run_cmd("tput cols", 3), NULL, 10)){
            OpeningScreen();
        }
    }
    return 0;
}

void OpeningScreen(){
    system("clear");
    UpdateSize();
    DrawFrame();
    PrintLogo(0);
}

void UpdateSize(){
    lines = (int) strtol(run_cmd("tput lines", 3), NULL, 10);
    cols = (int) strtol(run_cmd("tput cols", 3), NULL, 10);
}

void Clear(){
    system("clear");
}