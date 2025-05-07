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

int is_parentese(char *input)
{
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(')
            return 1;
    }
    return 0;
}

int execute_simple_command(char *token, minishel_t **llenv)
{
    int status = 0;
    const char *cmd[] = {"repeat", "which", "&", NULL};
    int (*handlers[])(char *, minishel_t **) =
        {handle_repeat, handle_which, handle_background};

    for (int i = 0; cmd[i]; i++) {
        if (my_strstr(token, cmd[i]) != NULL) {
            return handlers[i](token, llenv);
        }
    }
    parse_token(token);
    return which_cmd(token, llenv);
}

int execute_multi_cmd(minishel_t **llenv, char *input)
{
    char **all_cmd = string_to_array_with_priority(input, is_separator);
    int status = 0;

    if (strncmp(input, "if ", 3) == 0 || strncmp(input, "if(", 3) == 0)
        return handle_if(input, llenv);
    if (strncmp(input, "foreach ", 8) == 0 ||
        strncmp(input, "foreach(", 8) == 0)
        return 0;
    if (validate_cmd_syntax(input) != 0)
        return 1;
    for (int i = 0; all_cmd[i] != NULL; i++)
        status = handle_tok(all_cmd[i], llenv);
    free_array(all_cmd);
    return status;
}
