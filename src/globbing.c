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

char *search_pattern(char **cmd)
{
    char *delim;

    for (int i = 0; cmd[i]; i++) {
        delim = strstr(cmd[i], "*");
        if (delim)
            return delim;
        delim = strstr(cmd[i], "?");
        if (delim)
            return delim;
        delim = strstr(cmd[i], "[");
        if (delim && strstr(cmd[i], "]"))
            return delim;
    }
    return NULL;
}

char **globbing(char **command)
{
    char **match;
    glob_t g_struct;
    char *pattern = search_pattern(command);
    int r = 0;

    if (!pattern)
        return command;
    r = glob(pattern, GLOB_ERR, NULL, &g_struct);
    if (r == 0) {
        match = g_struct.gl_pathv;
        globfree(&g_struct);
        return match;
    }
    globfree(&g_struct);
    return NULL;
}
