//
// Created by idohacker on 7/20/19.
//
#include "ui_funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#include "ui_funcs.h"

#define VERTICAL_PIPE L"║"
#define HORIZONTAL_PIPE L"═"
#define UP_RIGHT_CORNER L"╗"
#define UP_LEFT_CORNER L"╔"
#define DOWN_RIGHT_CORNER L"╝"
#define DOWN_LEFT_CORNER L"╚"

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

void DrawFrame(int w, int h){
    DrawUpLine(w);
    DrawSides(w, h);
    putwchar(L'\n');
    DrawDownLine(w);
    putwchar(L'\n');
}
