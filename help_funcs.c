//
// Created by idohacker on 7/20/19.
//

#include "help_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define gotoxy(x, y) wprintf(L"\033[%d;%dH", (y), (x))


void RunCmd(char *cmd, int len, char* pout){
    FILE *fcmd = popen(cmd, "r");
    fgets(pout, (len + 1)* sizeof(char), fcmd);
    fclose(fcmd);

}

int GetCols(){
    char* pout = malloc(sizeof(char) * 3);
    RunCmd("tput -T xterm-256color cols", 3, pout);
    int width = (int) strtol(pout, NULL, 10);
    free(pout);
    return width;
}

int GetLines(){
    char* pout = malloc(sizeof(char) * 3);
    RunCmd("tput -T xterm-256color lines", 3, pout);
    int height = (int) strtol(pout, NULL, 10);
    free(pout);
    return height;
}

void SigintHandler(){
    system("clear");
    gotoxy(0,0);
    exit(0);
}