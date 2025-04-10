/*
** EPITECH PROJECT, 2025
** variable
** File description:
** handle local variable with a linked list
*/

#include "minishel.h"

static int is_equal(char c)
{
    return (c != '=');
}

minishel_t **get_variable(void)
{
    static minishel_t *variable = NULL;

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
    int len_args = len_array(args);
    char **cut_var;
    int len_cut = 0;

    if (len_args == 1)
        print_var();
    else {
        cut_var = my_str_to_word_array(args[1], is_equal);
        len_cut = len_array(cut_var);
        if (len_cut == 2) {
            add_llist(variable, cut_var[0], cut_var[1]);
        } else {
            add_llist(variable, cut_var[0], NULL);
        }
    }
    return 1;
}
