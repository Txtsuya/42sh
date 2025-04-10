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

static int handle_special_cmd(char *token, minishel_t **llenv)
{
    int status = 0;

    if (my_strstr(token, "&") != NULL)
        return jobs_control(token, llenv);
    if (my_strstr(token, "&&") != NULL)
        return handle_and(token, llenv);
    if (my_strstr(token, "||") != NULL)
        return handle_or(token, llenv);
    return -1;
}

int handle_token(char *token, minishel_t **llenv)
{
    int status = 0;
    int len = 0;

    status = handle_special_cmd(token, llenv);
    if (status != -1)
        return status;
    parse_token(token);
    status = which_cmd(token, llenv);
    return status;
}

int execute_multi_cmd(minishel_t **llenv, char *input)
{
    int status = 0;
    char *token;
    char *ptr;
    char *new = my_strdup(input);

    free(input);
    token = strtok_r(new, ";", &ptr);
    while (token != NULL) {
        status = handle_token(token, llenv);
        token = strtok_r(NULL, ";", &ptr);
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
