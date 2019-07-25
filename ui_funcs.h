//
// Created by idohacker on 7/20/19.
//

#ifndef LOG_IN_UI_FUNCS_H
#define LOG_IN_UI_FUNCS_H

#include <unistd.h>
#include <stdbool.h>
#include <wchar.h>

int cols, lines;

typedef struct Button{
    wchar_t* txt;
    float x_percent;
    float y_percent;
    bool highlighted;
}button;

enum LabelType { TEXT, FILE_CONTENT };

typedef struct Label{
    enum LabelType l_type;
    float x_percent;
    float y_percent;
    union {
        char* file_name;
        wchar_t* txt;
    };
    __useconds_t buffer;
}label;

enum ElementType { BUTTON, LABEL};

typedef struct Element{
    enum ElementType e_type;
    union {
        label lbl;
        button btn;
    };
}element;

void ShowUI(int element_num, element * element_arr);

#endif //LOG_IN_UI_FUNCS_H
