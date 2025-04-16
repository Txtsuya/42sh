/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** and_or_errors.c
*/
#include "../include/minishel.h"

int validate_and(char *cmd)
{
    int len;

    if (cmd[0] == '&' && cmd[1] == '&') {
        write(2, "Invalid null command.\n", 22);
        return 1;
    }
    len = my_strlen(cmd);
    if (len >= 2 && cmd[len - 2] == '&' && cmd[len - 1] == '&') {
        write(2, "Invalid null command.\n", 22);
        return 1;
    }
    for (int i = 0; i < len - 3; i++) {
        if (cmd[i] == '&' && cmd[i + 1] == '&' &&
            cmd[i + 2] == '&' && cmd[i + 3] == '&') {
            write(2, "Invalid null command.\n", 22);
            return 1;
        }
    }
    return 0;
}

int validate_or(char *cmd)
{
    int len;

    if (cmd[0] == '|' && cmd[1] == '|') {
        write(2, "Invalid null command.\n", 22);
        return 1;
    }
    len = my_strlen(cmd);
    if (len >= 2 && cmd[len - 2] == '|' && cmd[len - 1] == '|') {
        write(2, "Invalid null command.\n", 22);
        return 1;
    }
    for (int i = 0; i < len - 3; i++) {
        if (cmd[i] == '|' && cmd[i + 1] == '|' &&
            cmd[i + 2] == '|' && cmd[i + 3] == '|') {
            write(2, "Invalid null command.\n", 22);
            return 1;
        }
    }
    return 0;
}

int validate_mixed(char *cmd)
{
    int len = my_strlen(cmd);

    for (int i = 0; i < len - 3; i++) {
        if (cmd[i] == '&' && cmd[i + 1] == '&' &&
            cmd[i + 2] == '|' && cmd[i + 3] == '|') {
            write(2, "Invalid null command.\n", 22);
            return 1;
        }
    }
    for (int i = 0; i < len - 3; i++) {
        if (cmd[i] == '|' && cmd[i + 1] == '|' &&
            cmd[i + 2] == '&' && cmd[i + 3] == '&') {
            write(2, "Invalid null command.\n", 22);
            return 1;
        }
    }
    return 0;
}

int validate_cmd_syntax(char *cmd)
{
    if (validate_and(cmd) != 0)
        return 1;
    if (validate_or(cmd) != 0)
        return 1;
    if (validate_mixed(cmd) != 0)
        return 1;
    return 0;
}

int process_token(char *token, minishel_t **llenv)
{
    int status = 0;
    int len = my_strlen(token);

    while (*token == ' ')
        token++;
    while (len > 0 && token[len - 1] == ' ') {
        token[len] = '\0';
        len--;
    }
    status = which_cmd(token, llenv);
    return status;
}
