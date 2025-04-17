/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** main.c
*/

#include "include/minishel.h"

void print_prompt(minishel_t **llenv)
{
    if (isatty(STDIN_FILENO)) {
        my_putstr(my_getenv(*llenv, "PWD"));
        my_putstr(" > ");
    }
}

int handle_builtin_cmd(char ***arguments, char *input, minishel_t **llenv)
{
    char **args = *arguments;
    command_t commands[] = {{"env", handle_env},
        {"/usr/bin/env", handle_env}, {"setenv", handle_setenv},
        {"unsetenv", handle_unsetenv}, {"exit", handle_exit},
        {"cd", handle_cd}, {"alias", handle_alias},
        {"unalias", handle_unalias}, {"history", print_history},
        {"set", handle_variable}, {"jobs", print_jobs}, {"fg", forground},
        {"bg", background}, {"unset", handle_unset}, {"where", handle_where},
        {NULL, NULL}};

    if (my_strcmp(input, "") == 0)
        return 1;
    for (int i = 0; commands[i].name != NULL; i++) {
        if (my_strcmp(args[0], commands[i].name) == 0) {
            return commands[i].handler(args, llenv);
        }
    }
    return 0;
}

int main(int argc, char **argv, char **env)
{
    minishel_t *llenv;

    init_jobs();
    initialize_shell(env, &llenv);
    return main_loop(&llenv);
}
