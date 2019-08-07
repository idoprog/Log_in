//
// Created by idohacker on 8/3/19.
//
#include <signal.h>
#include <stdlib.h>
#include "low_ui_funcs.h"
#include "help_funcs.h"

#include "high_ui_funcs.h"

void ShowElements(IWINDOW win);

IWINDOW CreateWindow(bool frame){
    ElementList * temp_head = malloc(sizeof(ElementList));
    temp_head->element.e_type = EMPTY_ELEMENT;
    temp_head->next = NULL;
    IWINDOW win = {.frame = frame, .element_list_h=temp_head};
    return win;
}

void _AddElement(IWINDOW win, Element element){
    ElementList * pos = win.element_list_h;
    if(pos->element.e_type == EMPTY_ELEMENT){
        pos->element = element;
        pos->next = NULL;
        return;
    }
    while (pos->next != NULL){
        pos = pos->next;
    }
    pos->next = malloc(sizeof(ElementList));
    pos->next->element = element;
    pos->next->next = NULL;
}

void AddButton(IWINDOW win, float x_precent, float y_precent, bool highlight, char * txt){
    Element button = {.x_percent = x_precent, .y_percent = y_precent, .highlight = highlight, .e_type = BUTTON, .btn = {.txt = txt}};
    _AddElement(win, button);
}

void AddFileLabel(IWINDOW win, float x_precent, float y_precent, bool highlight, char * fname){
    Element file_lbl = {.x_percent = x_precent, .y_percent = y_precent, .highlight = highlight, .e_type = FILE_LABEL, .file_lbl = {.file_name = fname}};
    _AddElement(win, file_lbl);
}

void AddLabel(IWINDOW win, float x_precent, float y_precent, bool highlight, char * txt){
    Element txt_lbl = {.x_percent = x_precent, .y_percent = y_precent, .highlight = highlight, .e_type = TEXT_LABEL, .txt_lbl = {.txt = txt}};
    _AddElement(win, txt_lbl);
}

void _InitWin(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    refresh();
}

void MainLoop(IWINDOW win){
    _InitWin();
    win.window = newwin(LINES, COLS, 0, 0);
    if(win.frame == true){
        box(win.window, 0, 0);
    }
    refresh();
    ShowElements(win);
    refresh();
    wrefresh(win.window);
    while(getch() != KEY_BACKSPACE){}
    endwin();
}


int CalculateX(float x_percent){
    return (int)((float)COLS * x_percent);
}

int CalculateY(float y_percent){
    return (int)((float)LINES * y_percent);
}

void WPrintButton(IWINDOW win, Element btn){
    if(btn.highlight == true){
        mvwprintbh(win.window, CalculateY(btn.y_percent), CalculateX(btn.x_percent), btn.btn);
    } else{
        mvwprintb(win.window, CalculateY(btn.y_percent), CalculateX(btn.x_percent), btn.btn);
    }
}

int CalculateFileLabelX(float x_percent, FileLabel f_lbl){
    return (int)((float)(COLS - FileMaxLength(f_lbl.file_name)) * x_percent);
}

void WPrintFileLabel(IWINDOW win, Element f_lbl){
    if(f_lbl.highlight == true){
        mvwprintfh(win.window, CalculateY(f_lbl.y_percent), CalculateFileLabelX(f_lbl.x_percent, f_lbl.file_lbl), f_lbl.file_lbl);
    } else{
        mvwprintf(win.window, CalculateY(f_lbl.y_percent), CalculateFileLabelX(f_lbl.x_percent, f_lbl.file_lbl), f_lbl.file_lbl);
    }
}

void WPrintTextLabel(IWINDOW win, Element txt_lbl){
    if(txt_lbl.highlight == true){
        mvwprintwh(win.window, CalculateY(txt_lbl.y_percent), CalculateX(txt_lbl.x_percent), txt_lbl.txt_lbl.txt);
    } else{
        mvwprintw(win.window, CalculateY(txt_lbl.y_percent), CalculateX(txt_lbl.x_percent), txt_lbl.txt_lbl.txt);
    }
}

void ShowElements(IWINDOW win){
    ElementList * pos = win.element_list_h;
    do{
        Element temp = pos->element;
        switch (temp.e_type){
            case BUTTON:
                WPrintButton(win, temp);
                break;

            case FILE_LABEL:
                WPrintFileLabel(win, temp);
                break;

            case TEXT_LABEL:
                WPrintTextLabel(win, temp);
                break;

            case ENTRY:
                break;
        }
        pos = pos->next;
    }while (pos != NULL);
}

