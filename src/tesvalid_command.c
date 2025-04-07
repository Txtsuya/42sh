/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** tesvalid_command.c
*/

#include "../include/minishel.h"

int cut_pipe(char c)
{
    return (c != ' ' && c != '\t');
}

int is_pipe_char(char *str)
{
    return str && str[0] == '|';
}

int validate_pipe_placement(char **args)
{
    for (int i = 0; args[i]; i++) {
        if (i == 0 && is_pipe_char(args[i])) {
            return 0;
        }
        if (args[i + 1] == NULL && is_pipe_char(args[i])) {
            return 0;
        }
        if (is_pipe_char(args[i]) &&
            i > 0 &&
            is_pipe_char(args[i - 1])) {
            return 0;
        }
    }
    return 1;
}

void free_args(char **args)
{
    if (!args)
        return;
    for (int i = 0; args[i]; i++) {
        free(args[i]);
    }
    free(args);
}

int test_valid_pipe(char *token)
{
    char **args = my_str_to_word_array(token, cut_pipe);
    int is_valid = validate_pipe_placement(args);

    free_args(args);
    if (!is_valid) {
        write(2, "Invalid null command.\n", 22);
        return 1;
    }
    return 0;
}
