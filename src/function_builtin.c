/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** function_builtin.c
*/

#include "../include/minishel.h"

int handle_env(char **args, minishel_t **llenv)
{
    print_env(*llenv);
    return 1;
}

int handle_setenv(char **args, minishel_t **llenv)
{
    my_setenv(args, llenv);
    return 1;
}

int handle_unsetenv(char **args, minishel_t **llenv)
{
    delete_llist(llenv, args[1]);
    return 1;
}

int handle_exit(char **args, minishel_t **llenv)
{
    free_all();
    exit(0);
    return 1;
}

int handle_cd(char **args, minishel_t **llenv)
{
    return builtin_cd(args, llenv);
}
