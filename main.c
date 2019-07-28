#include <stdlib.h>
#include <stdio.h>
#include <locale.h>


#include "ui_funcs.h"
#include "help_funcs.h"

void OpeningScreen();

int main(){
    setlocale(LC_ALL, "");
    atexit(ClearScreen);
    OpeningScreen();
}

void OpeningScreen(){
    element element_arr[3] = {
            {.e_type = LABEL,
             .lbl = {.x_percent = 0.5, .y_percent = 0.1, .l_type = FILE_CONTENT, .file_name = "logo.txt", .buffer= 200000}
            }
            ,
            {.e_type = BUTTON,
             .btn = {.x_percent = 0.4, .y_percent = 0.6, .txt=L"Log in", .highlighted=true}
            }
            ,
            {.e_type = BUTTON,
             .btn = {.x_percent = 0.4, .y_percent = 0.8, .txt=L"Register", .highlighted=false}
            }
    };
    ShowUI(3, element_arr);
}