/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** multicmd.c
*/

#include "../include/minishel.h"

int get_redirection_index(const char *arg)
{
    const char *redirection_tokens[] = {">", ">>", "<", "<<", NULL};

    for (int i = 0; redirection_tokens[i] != NULL; i++) {
        if (my_strcmp(arg, redirection_tokens[i]) == 0)
            return i;
    }
    return -1;
}

void free_array(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        my_free(tab[i]);
    }
    my_free(tab);
}

int execute_multi_cmd(minishel_t **llenv, char *input)
{
    int status;
    char *token;
    char *ptr;

    token = strtok_r(input, ";", &ptr);
    while (token != NULL) {
        if (nbr_instr(token, '|'))
            status = executepipe(token, llenv);
        else
            status = execute_main_cmd(token, llenv);
        token = strtok_r(NULL, ";", &ptr);
    }
    free(input);
    return status;
}

int len_array(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        i++;
    }
    return i;
}
