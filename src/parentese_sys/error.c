/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../../include/minishel.h"

static int open_parenthese(char input, int *level,
    int *is_sep, int *is_char_between)
{
    if (input == '(') {
        (*level)++;
        if (*is_sep == 0) {
            *level = -1;
        }
    }
    if (*level > 0) {
        *is_char_between += 1;
    }
}

static int check_parenthes(char input, int *level,
    int *is_char_between, int *is_sep)
{
    open_parenthese(input, level, is_sep, is_char_between);
    if (input == ')') {
        (*level)--;
        if (*is_char_between < 3 && *is_char_between > 0) {
            *level = -1;
        }
        *is_char_between = 0;
        *is_sep = 0;
    }
    if (is_redirection(input) || is_pipe(input)) {
        if (*level == 0) {
            *is_sep = 1;
        }
    }
}

int check_num_of_parenthese(char *input)
{
    int level = 0;
    int is_char_between = 0;
    int is_sep = 1;

    for (int i = 0; input[i] != '\0'; i++) {
        check_parenthes(input[i], &level, &is_char_between, &is_sep);
        if (level < 0) {
            my_putstr("Too many )'s.\n");
            return 1;
        }
    }
    if (level > 0) {
        my_putstr("Too many ('s.\n");
        return 1;
    }
    return 0;
}

static int is_valid_char_after_parenthese(char c)
{
    return (c == ' ' || c == '\t' || c == '\0' || c == '|' ||
            c == '>' || c == '<' || c == '&' || c == ';' || c == ')');
}

static int check_invalid_syntax_after_parenthese(char *input)
{
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ')' && input[i + 1] != '\0' &&
            !is_valid_char_after_parenthese(input[i + 1])) {
            my_putstr("Badly placed )'s.\n");
            return 1;
        }
    }
    return 0;
}

int check_error_parenthese(char **all_arg, char *input, int arraylen)
{
    if (check_num_of_parenthese(input) == 1) {
        return 1;
    }
    if (check_invalid_syntax_after_parenthese(input) == 1) {
        return 1;
    }
    if (arraylen % 2 == 0) {
        my_putstr("Invalid null command.\n");
        return 1;
    }
    return 0;
}
