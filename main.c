#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>

#include "ui_funcs.h"
#include "help_funcs.h"

int main(){
    setlocale(LC_ALL, "");
    int lines = (int) strtol(run_cmd("tput lines", 2),NULL, 10);
    int cols = (int) strtol(run_cmd("tput cols", 3),NULL, 10);
    cols -= 2;
    lines -= 3;
    DrawFrame(cols, lines);
    sleep(6);
    return 0;
}