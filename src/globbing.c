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

int len_array(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        i++;
    }
    return i;
}

char *search_pattern(char **cmd)
{
    char *delim;

    for (int i = 0; cmd[i]; i++) {
        delim = strstr(cmd[i], "*");
        if (delim)
            return cmd[i];
        delim = strstr(cmd[i], "?");
        if (delim)
            return cmd[i];
        delim = strstr(cmd[i], "[");
        if (delim && strstr(cmd[i], "]"))
            return cmd[i];
    }
    return NULL;
}

char **my_concat_glob(char **command, glob_t *glob)
{
    char **match = glob->gl_pathv;
    int n = len_array(command) - 1;
    int i = 0;

    for (i = 0; match[i]; i++) {
        command = realloc(command, sizeof(char *) * (n + i + 1));
        if (!command)
            exit(84);
        command[n + i] = strdup(match[i]);
        if (!match[i])
            exit(84);
    }
    globfree(glob);
    command[n + i] = NULL;
    return command;
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
        return my_concat_glob(command, &g_struct);
    }
    globfree(&g_struct);
    return command;
}
