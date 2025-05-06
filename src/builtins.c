/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include "../include/minishel.h"

int check_is_builtin(char *type)
{
    const char *types[] = {"cd", "exit", "env", "alias", "unsetenv",
        "unalias", "set", "jobs", "history", "unset", "bg", "echo", NULL};

    for (int i = 0; types[i]; i++) {
        if (my_strcmp(type, types[i]) == 0)
            return 1;
    }
    return 0;
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
    if (check_right_argv(args[1], "setenv") == 1)
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
