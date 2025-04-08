/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** special_variables
*/

#include "../include/minishel.h"

void initialize_variable_term(minishel_t **llenv)
{
    char *term_var = my_getenv(*llenv, "TERM");

    if (term_var != NULL)
        add_llist(llenv, "term", term_var);
    else
        add_llist(llenv, "term", "unknown");
    return;
}

void call_special_variables(minishel_t **llenv)
{
    initialize_variable_term(llenv);
    return;
}

void update_special_variables(minishel_t **llenv)
{
    char *term_var = my_getenv(*llenv, "TERM");

    if (term_var != NULL) {
        replace_in_list(llenv, "term", term_var);
    }
    return;
}
