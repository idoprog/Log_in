//
// Created by idohacker on 7/20/19.
//
#include "ui_funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "ui_funcs.h"
#include "help_funcs.h"

#define VERTICAL_PIPE L"║"
#define HORIZONTAL_PIPE L"═"
#define UP_RIGHT_CORNER_PIPE L"╗"
#define UP_LEFT_CORNER_PIPE L"╔"
#define DOWN_RIGHT_CORNER_PIPE L"╝"
#define DOWN_LEFT_CORNER_PIPE L"╚"

#define VERTICAL_LINE L"│"
#define HORIZONTAL_LINE L"─"
#define UP_RIGHT_CORNER_LINE L"┐"
#define UP_LEFT_CORNER_LINE L"┌"
#define DOWN_RIGHT_CORNER_LINE L"┘"
#define DOWN_LEFT_CORNER_LINE L"└"


#define gotoxy(x, y) wprintf(L"\033[%d;%dH", (y), (x))


// Function to print the top line
void DrawUpLine(int w){
    wprintf(UP_LEFT_CORNER_PIPE);
    for (int i = 0; i < w; i++)
    {
        wprintf(HORIZONTAL_PIPE);
    }
    wprintf(UP_RIGHT_CORNER_PIPE);
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
    wprintf(DOWN_LEFT_CORNER_PIPE);
    for (int i = 0; i < w; i++)
    {
        wprintf(HORIZONTAL_PIPE);
    }
    wprintf(DOWN_RIGHT_CORNER_PIPE);
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
    int ucols = cols / 2 - 25, ulines = (int) ((double) lines * 0.1);
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
    fflush(stdout);
    fclose(fp);
    gotoxy(0, lines);
}

void PrintButton(int x, int y, wchar_t *txt){
    gotoxy(x, y);
    int len = wcslen(txt);
    wprintf(UP_LEFT_CORNER_LINE);
    for (int i = 0; i < len + 2; ++i) {
        wprintf(HORIZONTAL_LINE);
    }
    wprintf(UP_RIGHT_CORNER_LINE);

    gotoxy(x, y + 1);

    wprintf(VERTICAL_LINE);
    wprintf(L" %ls ", txt);
    wprintf(VERTICAL_LINE);

    gotoxy(x, y + 2);

    wprintf(DOWN_LEFT_CORNER_LINE);
    for (int i = 0; i < len + 2; ++i) {
        wprintf(HORIZONTAL_LINE);
    }
    wprintf(DOWN_RIGHT_CORNER_LINE);

    gotoxy(0, lines);

}

void UpdateSize(){
    lines = GetLines();
    cols = GetCols();
}

void OpeningScreen(__useconds_t buff){
    system("clear");
    UpdateSize();
    DrawFrame();
    PrintLogo(buff);
    PrintButton(cols / 2 - 5 ,(int) ((double)lines * 0.65) , L"Log in");
    PrintButton(cols / 2 - 5 , (int) ((double)lines * 0.65) + 4, L"Register");
}

