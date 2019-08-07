#include <ncurses.h>
#include <string.h>

#include "low_ui_funcs.h"


void mvwprintl(WINDOW * win, int y, int x, int len){
    mvwaddch(win, y, x, '+');
    for(int i = 1; i<=len; i++){
        mvwaddch(win, y, x + i, '-');
    }
    mvwaddch(win, y, x + len + 1, '+');
}

void mvwprintwh(WINDOW * win, int y, int x, char * txt){
    wattron(win, A_REVERSE);
    mvwprintw(win, y, x, txt);
    wattroff(win, A_REVERSE);
}

void mvwprintbh(WINDOW * win, int y, int x, Button btn){
    int txt_len = strlen(btn.txt);

    mvwprintl(win, y, x, txt_len);

    mvwaddch(win, y + 1, x, '|');
    mvwprintwh(win, y + 1, x + 1, btn.txt);
    mvwaddch(win, y + 1, x + txt_len + 1, '|');

    mvwprintl(win, y + 2, x, txt_len);


}

void mvwprintb(WINDOW * win, int y, int x, Button btn){
    int txt_len = strlen(btn.txt);

    mvwprintl(win, y, x, txt_len);

    mvwaddch(win, y + 1, x, '|');
    mvwprintw(win, y + 1, x + 1, btn.txt);
    mvwaddch(win, y + 1, x + txt_len + 1, '|');

    mvwprintl(win, y + 2, x, txt_len);

}


void mvwprintf(WINDOW * win, int y, int x, FileLabel f_lbl){
    FILE * fp = fopen(f_lbl.file_name, "r");
    char ch;
    int current_x = x, current_y = y;
    while (( ch = fgetc(fp)) != EOF){
        if(ch == '\n'){
            current_y++;
            current_x = x;
        } else{
            mvwaddch(win, current_y, current_x, ch);
            current_x++;
        }
    }
    fclose(fp);
}

void mvwprintfh(WINDOW * win, int y, int x, FileLabel f_lbl){
    wattron(win, A_REVERSE);
    mvwprintf(win, y, x, f_lbl);
    wattroff(win, A_REVERSE);
}




