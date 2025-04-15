/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** multicmd.c
*/

#include "../include/minishel.h"

static int is_separator(char c)
{
    return (c == ';');
}

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

static int which_cmd(char *cmd, minishel_t **llenv)
{
    if (nbr_instr(cmd, '|'))
        return executepipe(cmd, llenv);
    else
        return execute_main_cmd(cmd, llenv);
}

static int handle_and(char *cmd, minishel_t **llenv)
{
    int status = 0;
    char *tkt_ptr;
    char *token = strtok_r(cmd, "&&", &tkt_ptr);
    int len = 0;

    while (token != NULL) {
        while (*token == ' ')
            token++;
        len = my_strlen(token);
        while (len > 0 && token[len - 1] == ' ') {
            token[len] = '\0';
            len--;
        }
        status = which_cmd(token, llenv);
        if (status != 0)
            break;
        token = strtok_r(NULL, "&&", &tkt_ptr);
    }
    return status;
}

static int handle_or(char *cmd, minishel_t **llenv)
{
    int status = 1;
    char *tkt_ptr;
    char *token = strtok_r(cmd, "||", &tkt_ptr);
    int len = 0;

    while (token != NULL) {
        while (*token == ' ')
            token++;
        len = my_strlen(token);
        while (len > 0 && token[len - 1] == ' ') {
            token[len - 1] = '\0';
            len--;
        }
        if (status != 0)
            status = which_cmd(token, llenv);
        if (status == 0)
            break;
        token = strtok_r(NULL, "||", &tkt_ptr);
    }
    return status;
}

static void parse_token(char *token)
{
    int len = my_strlen(token);

    while (*token == ' ')
        token++;
    while (len > 0 && token[len - 1] == ' ') {
        token[len - 1] = '\0';
        len--;
    }
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

static int handle_token(char *token, minishel_t **llenv)
{
    int status = 0;
    int len = 0;

    if (is_parentese(token)) {
        return handle_parenthese(llenv, token);
    }
    if (my_strstr(token, "&") != NULL) {
        return handle_background(token, llenv);
    }
    if (my_strstr(token, "&&") != NULL)
        status = handle_and(token, llenv);
    else if (my_strstr(token, "||") != NULL)
        status = handle_or(token, llenv);
    else {
        parse_token(token);
        status = which_cmd(token, llenv);
    }
    return status;
}

int execute_multi_cmd(minishel_t **llenv, char *input)
{
    char **all_cmd = string_to_array_with_priority(input, is_separator);
    int status = 0;

    for (int i = 0; all_cmd[i] != NULL; i++) {
        status = handle_token(all_cmd[i], llenv);
    }
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
