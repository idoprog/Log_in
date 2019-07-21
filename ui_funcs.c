//
// Created by idohacker on 7/20/19.
//
#include "ui_funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>

#include "ui_funcs.h"

#define VERTICAL_PIPE L"║"
#define HORIZONTAL_PIPE L"═"
#define UP_RIGHT_CORNER L"╗"
#define UP_LEFT_CORNER L"╔"
#define DOWN_RIGHT_CORNER L"╝"
#define DOWN_LEFT_CORNER L"╚"

#define gotoxy(x, y) wprintf(L"\033[%d;%dH", (y), (x))


// Function to print the top line
void DrawUpLine(int w){
    wprintf(UP_LEFT_CORNER);
    for (int i = 0; i < w; i++)
    {
        wprintf(HORIZONTAL_PIPE);
    }
    wprintf(UP_RIGHT_CORNER);
}

// Function to print the sides
void DrawSides(int w, int h){
    for (int i = 0; i < h; i++)
    {
        putwchar(L'\n');
        wprintf(VERTICAL_PIPE);
        for (int j = 0; j < w; j++)
        {
            putwchar(L' ');
        }
        wprintf(VERTICAL_PIPE);
    }
}

// Function to print the bottom line
void DrawDownLine(int w){
    wprintf(DOWN_LEFT_CORNER);
    for (int i = 0; i < w; i++)
    {
        wprintf(HORIZONTAL_PIPE);
    }
    wprintf(DOWN_RIGHT_CORNER);
}

void DrawFrame(){
    gotoxy(0, 0);
    int ucols = cols - 2, ulines = lines - 3;
    DrawUpLine(ucols);
    DrawSides(ucols, ulines);
    putwchar(L'\n');
    DrawDownLine(ucols);
    putwchar(L'\n');
}

void PrintLogo(__useconds_t buffer){
    int ucols = cols / 2 - 25, ulines = lines / 2 - 8;
    gotoxy(ucols, ulines);
    wchar_t ch;
    int counter = 0;
    FILE *fp = fopen("logo.txt", "r");
    while( (ch = fgetwc(fp)) != EOF){
        if(ch == L'\n'){
            usleep(buffer);
            counter++;
            gotoxy(ucols, ulines + counter);
        } else {
            putwchar(ch);
        }
        fflush(stdout);
    }
    gotoxy(0, lines);
}

