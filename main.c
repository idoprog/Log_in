#include <ncurses.h>
#include <signal.h>

#include "high_ui_funcs.h"

void OpeningWindow();

int main(){
    OpeningWindow();
    return 0;
}

void OpeningWindow(){
    IWINDOW * win = CreateWindow(true, KEY_BACKSPACE);
    AddFileLabel(win, 0.5, 0.1, false, "logo.txt");
    AddButton(win, 0.4, 0.6, true, "Log in");
    AddButton(win, 0.4, 0.8, false, "Register");
    MainLoop(win);
}