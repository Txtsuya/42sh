/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include "../include/minishel.h"

static int is_space(char c)
{
    return (c != ' ' && c != '\t');
}

void add_llist_env(char *pwd, minishel_t **llenv, const char *name)
{
    add_llist(llenv, name, pwd);
}

int my_setenv(char **args, minishel_t **llenv)
{
    int len = len_array(args);

    if (len > 3) {
        perror("setenv");
        return 1;
    }
    if (len == 1) {
        print_env(*llenv);
        return 1;
    }
    if (check_right_argv(args[1]) == 1)
        return 1;
    if (len == 2) {
        add_llist(llenv, args[1], NULL);
        return 1;
    } else {
        add_llist(llenv, args[1], args[2]);
        return 1;
    }
}

void print_env(minishel_t *head)
{
    if (head == NULL)
        return;
    while (head != NULL) {
        my_putstr(head->name);
        my_putstr("=");
        if (head->value != NULL)
            my_putstr(head->value);
        my_putstr("\n");
        head = head->next;
    }
}

int handle_builtin_cmd(char ***arguments, char *input, minishel_t **llenv)
{
    char **args = *arguments;
    command_t commands[] = {{"env", handle_env},
        {"/usr/bin/env", handle_env}, {"setenv", handle_setenv},
        {"unsetenv", handle_unsetenv}, {"exit", handle_exit},
        {"cd", handle_cd}, {"alias", handle_alias},
        {"unalias", handle_unalias}, {"set", handle_variable}, {NULL, NULL}};

    if (my_strcmp(input, "") == 0)
        return 1;
    for (int i = 0; commands[i].name != NULL; i++) {
        if (my_strcmp(args[0], commands[i].name) == 0) {
            return commands[i].handler(args, llenv);
        }
    }
    return 0;
}
