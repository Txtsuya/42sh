/*
** EPITECH PROJECT, 2025
** variable
** File description:
** handle local variable with a linked list
*/

#include "minishel.h"

minishel_t **get_variable(void)
{
    static minishel_t *variable = NULL;

    if (!variable) {
        variable = malloc(sizeof(minishel_t *));
        variable->name = NULL;
        variable->next = NULL;
        variable->value = NULL;
    }
    return &variable;
}

void print_var(void)
{
    minishel_t **variable = get_variable();
    minishel_t *tmp = *variable;

    while (tmp) {
        printf("%s", tmp->name);
        if (tmp->value)
            printf("\t%s", tmp->value);
        printf("\n");
        tmp = tmp->next;
    }
}

int handle_variable(char **args, minishel_t **llenv)
{
    minishel_t **variable = get_variable();
    int n = len_array(args);

    if (n == 1)
        print_var();
    else if (n == 2) {
        add_llist(variable, args[1], args[2]);
    } else {
        add_llist(variable, args[1], NULL);
    }
    return 1;
}
