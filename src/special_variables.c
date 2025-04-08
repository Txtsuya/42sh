/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** special_variables
*/

#include "../include/minishel.h"

char *get_special_variables(minishel_t **env, char *name)
{
    if (my_strcmp(name, "term") == 0)
        return my_getenv(*env, "TERM");
    return my_getenv(*env, name);
}
