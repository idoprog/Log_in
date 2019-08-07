//
// Created by idohacker on 8/3/19.
//

#ifndef LOG_IN_HIGH_UI_FUNCS_H
#define LOG_IN_HIGH_UI_FUNCS_H
#include "low_ui_funcs.h"
#include <ncurses.h>

enum ElementType {FILE_LABEL, BUTTON, TEXT_LABEL, ENTRY, EMPTY_ELEMENT};

typedef struct {
    bool highlight;
    float x_percent;
    float y_percent;
    enum ElementType e_type;
    union {
        Button btn;
        TextLabel txt_lbl;
        FileLabel file_lbl;
    };
}Element;

typedef struct e_list{
    Element element;
    struct e_list * next;
} ElementList;

typedef struct {
    WINDOW * window;
    ElementList * element_list_h;
    bool frame;
}IWINDOW;

IWINDOW CreateWindow(bool frame);
void AddButton(IWINDOW win, float x_precent, float y_precent, bool highlight, char * txt);
void AddFileLabel(IWINDOW win, float x_precent, float y_precent, bool highlight, char * fname);
void AddLabel(IWINDOW win, float x_precent, float y_precent, bool highlight, char * txt);
void MainLoop(IWINDOW win);



#endif //LOG_IN_HIGH_UI_FUNCS_H
