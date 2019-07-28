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
#include <pthread.h>
#include <signal.h>

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

static int element_x, element_y;
pthread_t button_thread_id;
static pthread_mutex_t cusror_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    wchar_t txt[20];
    int x;
    int y;
    int len;
}button_info;

void SigintHandler(){
    system("setterm -cursor on");
    pthread_cancel(button_thread_id);
    system("clear");
    gotoxy(0,0);
    exit(1);
}

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

void BlinkButtonCleanUp(void *arg){
    free(arg);
    system("clear");
    pthread_mutex_unlock(&cusror_mutex);
}

void *BlinkButtonThread(void *args){
    button_info *b_info = args;

    bool blink = true;
    wchar_t ch;

    pthread_cleanup_push(BlinkButtonCleanUp, b_info)
    pthread_mutex_lock(&cusror_mutex);
    while (1){
        gotoxy(b_info->x + 1, b_info->y + 1);
        if(blink == true){
            wprintf(L"\e[48;5;15m");
            wprintf(L"\e[38;5;0m");
            putwchar(L' ');
            for (int i = 0; i < b_info->len; ++i) {
                ch = b_info->txt[i];
                putwchar(ch);
            }
            putwchar(L' ');
            wprintf(L"\e[0m");
            blink = false;
        } else{
            wprintf(L" %ls ", b_info->txt);
            blink = true;
        }
        gotoxy(0, lines);
        usleep(600000);
        fflush(stdout);
    }
    pthread_cleanup_pop(1);
    free(b_info);
    return 0;
}

void PrintButton(button btn){
    gotoxy(element_x, element_y);
    int len = wcslen(btn.txt);
    wprintf(UP_LEFT_CORNER_LINE);
    for (int i = 0; i < len + 2; ++i) {
        wprintf(HORIZONTAL_LINE);
    }
    wprintf(UP_RIGHT_CORNER_LINE);

    gotoxy(element_x, element_y + 1);

    wprintf(VERTICAL_LINE);
    if(btn.highlighted == true){
        button_info *args = malloc(sizeof(button_info));
        args->x = element_x;
        args->y = element_y;
        args->len = len;
        wcpcpy(args->txt, btn.txt);
        pthread_create(&button_thread_id, NULL, BlinkButtonThread, args);
    } else{
        wprintf(L" %ls ", btn.txt);
    }
    gotoxy(element_x + len + 3, element_y + 1);
    wprintf(VERTICAL_LINE);

    gotoxy(element_x, element_y + 2);

    wprintf(DOWN_LEFT_CORNER_LINE);
    for (int i = 0; i < len + 2; ++i) {
        wprintf(HORIZONTAL_LINE);
    }
    wprintf(DOWN_RIGHT_CORNER_LINE);
}

void UpdateSize(){
    lines = GetLines();
    cols = GetCols();
}

void PrintFile(label lbl){
    gotoxy(element_x, element_y);
    FILE *fp = fopen(lbl.file_name, "r");
    wchar_t ch;
    int counter = 0;
    while( (ch = fgetwc(fp)) != EOF){
        if(ch == L'\n'){
            usleep(lbl.buffer);
            counter++;
            gotoxy(element_x, element_y + counter);
        } else {
            putwchar(ch);
        }
        fflush(stdout);
    }
    fflush(stdout);
    fclose(fp);
}

void PrintText(label lbl){
    gotoxy(element_x, element_y);
    for(int i = 0; i < wcslen(lbl.txt); i++){
        usleep(lbl.buffer);
        putwchar(lbl.txt[i]);
        fflush(stdout);
    }
}

int FileMaxLength(char * file_name){
    FILE *fp = fopen(file_name, "r");
    int max_line = 0;
    int count = 0;
    char ch;
    while( (ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            if(count > max_line){
                max_line = count;
            }
            count = 0;
        } else{
            count++;
        }
    }
    return max_line;
}

void ShowUI(int element_num, element * element_arr){
    system("setterm -cursor off");
    signal(SIGINT, SigintHandler);
    bool first_draw = true;
    while (1){
        if(lines != GetLines() || cols != GetCols()){
            pthread_cancel(button_thread_id);
            UpdateSize();
            system("clear");
            pthread_mutex_lock(&cusror_mutex);
            DrawFrame();
            for (int i = 0; i < element_num; ++i) {
                switch (element_arr[i].e_type){

                    case BUTTON:
                        element_x = (int) (element_arr[i].btn.x_percent * (double)cols);
                        element_y = (int) (element_arr[i].btn.y_percent * (double)lines);
                        PrintButton(element_arr[i].btn);
                        break;

                    case LABEL:
                        element_y = (int) (element_arr[i].lbl.y_percent * (double)lines);
                        switch (element_arr[i].lbl.l_type){
                            case TEXT:
                                element_x = (int) (element_arr[i].lbl.x_percent * (double)cols);
                                PrintText(element_arr[i].lbl);
                                break;

                            case FILE_CONTENT:
                                element_x = (int) (element_arr[i].lbl.x_percent * (double)(cols - FileMaxLength(element_arr[i].lbl.file_name)));
                                PrintFile(element_arr[i].lbl);
                                break;
                        }
                        if(first_draw == true){
                            first_draw = false;
                            element_arr[i].lbl.buffer = 0;
                        }
                        break;
                }
                gotoxy(0, lines);
                fflush(stdout);
            }
        }
        pthread_mutex_unlock(&cusror_mutex);
    }
}
