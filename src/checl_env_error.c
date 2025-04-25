/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** checl_env_error.c
*/
#include "../include/minishel.h"

char *my_get_env_char(char *name, char **env)
{
    int j = my_strlen(name);

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], name, j) == 0 && env[i][j] == '=')
            return env[i] + j + 1;
    }
    return NULL;
}

int check_env_void(char **env)
{
    if (env == NULL || my_get_env_char("PATH", env) == NULL)
        return 1;
    return 0;
}
