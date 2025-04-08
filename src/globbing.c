/*
** EPITECH PROJECT, 2025
** globbings
** File description:
** handle *.c ?.c [a,c].c
** Author:
** Simon Puccio
*/

#include "minishel.h"
#include <glob.h>

int globbing(char *command)
{
    char **match;
    glob_t g_struct;
    int r = glob(command, GLOB_ERR, NULL, &g_struct);

    if (r == 0) {
        match = g_struct.gl_pathv;
        for (int i = 0; match[i]; i++)
            printf("%s\n", match[i]);
    }
    globfree(&g_struct);
    return 0;
}
