//
// Created by idohacker on 7/20/19.
//

#include "help_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *run_cmd(char *cmd, int len){
    FILE *fcmd = popen(cmd, "r");
    char *result = malloc(sizeof(char) * len);
    fgets(result, (len + 1)* sizeof(char), fcmd);
    return result;

}