/*
** EPITECH PROJECT, 2025
** String Cleaner
** File description:
** Functions to clean and format strings with proper spacing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_operator(char c)
{
    return (c == '|' || c == '&' || c == '<' ||
            c == '>' || c == ';' || c == '(' || c == ')');
}

static int is_double_operator(const char *str, int i)
{
    return ((str[i] == '&' && str[i + 1] == '&') ||
            (str[i] == '>' && str[i + 1] == '>') ||
            (str[i] == '<' && str[i + 1] == '<') ||
            (str[i] == '|' && str[i + 1] == '|'));
}

static void handle_whitespace(const char *input, char *result, int *i, int *j)
{
    if (*j > 0 && !isspace(result[*j - 1])) {
        result[*j] = ' ';
        (*j)++;
    }
    while (isspace(input[*i + 1])) {
        (*i)++;
    }
}

static void handle_double_operator(const char *input,
    char *result, int *i, int *j)
{
    if (*j > 0 && !isspace(result[*j - 1])) {
        result[*j] = ' ';
        (*j)++;
    }
    result[*j] = input[*i];
    (*j)++;
    (*i)++;
    result[*j] = input[*i];
    (*j)++;
    if (!isspace(input[*i + 1])) {
        result[*j] = ' ';
        (*j)++;
    }
}

static void handle_single_operator(const char *input,
    char *result, int *i, int *j)
{
    if (*j > 0 && !isspace(result[*j - 1])) {
        result[*j] = ' ';
        (*j)++;
    }
    result[*j] = input[*i];
    (*j)++;
    if (!isspace(input[*i + 1])) {
        result[*j] = ' ';
        (*j)++;
    }
}

int if_gestion(const char *input, char *result, int *i, int *j)
{
    if (isspace(input[*i])) {
        handle_whitespace(input, result, i, j);
        return 1;
    }
    if (is_double_operator(input, *i)) {
        handle_double_operator(input, result, i, j);
        return 1;
    }
    if (is_operator(input[*i])) {
        handle_single_operator(input, result, i, j);
        return 1;
    }
    return 0;
}

char *clean_str(const char *input)
{
    int len = strlen(input);
    char *result = malloc(len * 4 + 1);
    int j = 0;
    int i = 0;

    if (!result)
        return NULL;
    for (i = 0; i < len; i++) {
        if (if_gestion(input, result, &i, &j))
            continue;
        result[j] = input[i];
        j++;
    }
    if (j > 0 && isspace(result[j - 1]))
        j = j - 1;
    result[j] = '\0';
    return result;
}
