//
// Created by idohacker on 7/20/19.
//

#ifndef LOG_IN_LOW_UI_FUNCS_H
#define LOG_IN_LOW_UI_FUNCS_H

#include <ncurses.h>

typedef struct {
    char * txt;
}Button;

typedef struct {
    char * file_name;
}FileLabel;

typedef struct {
    char * txt;
}TextLabel;

void mvwprintl(WINDOW * win, int y, int x, int len);
void mvwprintwh(WINDOW * win, int y, int x, char * txt);
void mvwprintbh(WINDOW * win, int y, int x, Button btn);
void mvwprintf(WINDOW * win, int y, int x, FileLabel f_lbl);
void mvwprintfh(WINDOW * win, int y, int x, FileLabel f_lbl);
void mvwprintb(WINDOW * win, int y, int x, Button btn);

#endif //LOG_IN_LOW_UI_FUNCS_H
