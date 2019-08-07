//
// Created by idohacker on 8/3/19.
//

#include "help_funcs.h"
#include <ncurses.h>

int FileMaxLength(char * fname){
    FILE * fp = fopen(fname, "r");
    int max_len = 0, current_len = 0;
    char ch;
    while ( (ch  = fgetc(fp)) != EOF){
        if(ch == '\n'){
            if(current_len > max_len){
                max_len = current_len;
            }
            current_len = 0;
        } else{
            current_len++;
        }
    }
    return max_len;
}