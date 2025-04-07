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
        free(tab[i]);
    }
    free(tab);
}

static int is_parentese(char *input)
{
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(')
            return 1;
    }
    return 0;
}

int warp_execution(char *cmd, minishel_t **llenv)
{
    if (is_parentese(cmd)) {
        return handle_parenthese(llenv, cmd);
    }
    if (nbr_instr(cmd, '|') > 0) {
        return executepipe(cmd, llenv);
    }
    return execute_main_cmd(cmd, llenv);
}

int execute_multi_cmd(minishel_t **llenv, char *input)
{
    char **all_cmd = string_to_array_with_priority(input);
    int status = 0;

    for (int i = 0; all_cmd[i] != NULL; i++) {
        status = warp_execution(all_cmd[i], llenv);
    }
    return status;
}

/*
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
    return status;
}*/

int len_array(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        i++;
    }
    return i;
}
