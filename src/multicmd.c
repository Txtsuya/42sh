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

static int is_space(char c)
{
    return (c != ' ' && c != '\t' && c != '\"');
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

int handle_token(char *token, minishel_t **llenv)
{
    int status = 0;
    int len = 0;
    const char *cmd[] = {"repeat", "which", "where", "&&", "&", "||", NULL};
    int (*handlers[])(char *, minishel_t **) = {handle_repeat, handle_which,
        handle_where, handle_and, handle_background, handle_or};

    if (is_parentese(token))
        return handle_parenthese(llenv, token);
    for (int i = 0; cmd[i]; i++) {
        if (my_strstr(token, cmd[i]) != NULL)
            return handlers[i](token, llenv);
    }
    parse_token(token);
    status = which_cmd(token, llenv);
    return status;
}

int execute_multi_cmd(minishel_t **llenv, char *input)
{
    char **all_cmd = string_to_array_with_priority(input, is_separator);
    int status = 0;

    for (int i = 0; all_cmd[i] != NULL; i++)
        status = handle_token(all_cmd[i], llenv);
    return status;
}
