/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** varible_handling
*/

#include "minishel.h"

iteration_t *get_iterations(void)
{
    static iteration_t iteration;

    return &iteration;
}

char *check_variable(char *name, minishel_t **env)
{
    minishel_t **var = get_variable();
    minishel_t *current = *var;

    while (current) {
        if (my_strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}
