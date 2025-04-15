/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../../include/minishel.h"

int is_simple_sep(char c)
{
    return (c == '|' || c == '>' || c == '<' || c == '&');
}

int is_double_sep(char *str, int i)
{
    if (!str[i + 1])
        return 0;
    if (str[i] == '>' && str[i + 1] == '>')
        return 1;
    if (str[i] == '<' && str[i + 1] == '<')
        return 1;
    if (str[i] == '&' && str[i + 1] == '&')
        return 1;
    if (str[i] == '|' && str[i + 1] == '|')
        return 1;
    return 0;
}

int is_pipe(char c)
{
    return (c == '|');
}

int is_redirection(char c)
{
    return (c == '>' || c == '<' || c == '&');
}

int is_red_or_operator(char *cmd)
{
    char *all_red[] = {"<", "<<", ">", ">>", "&&", "||", NULL};

    for (int i = 0; i < 6; i++) {
        if (my_strcmp(all_red[i], cmd) == 0) {
            return i;
        }
    }
    return -1;
}
