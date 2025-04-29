/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** get_path_cmd.c
*/

#include "minishel.h"

int check_is_exec(char *args)
{
    if (my_strncmp(args, "./", 2) == 0)
        return 1;
    if (my_strncmp(args, "/", 1) == 0)
        return 1;
    return 0;
}

char *get_path_cmd(char *args, minishel_t **llenv)
{
    char *path_cmd;

    if (access(args, X_OK) != 0)
        path_cmd = build_path_cmd(args, llenv);
    else
        path_cmd = my_strdup(args);
    return path_cmd;
}
