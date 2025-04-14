/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** len_exclamation.c
*/

#include "../include/minishel.h"

static int is_empty(char *line)
{
    return line[0] == '\0';
}

static int is_exclamation(char *line)
{
    return line[0] == '!';
}

static int is_number_start(char *line)
{
    return (line[0] >= '0' && line[0] <= '9') || line[0] == '-';
}

static int get_number_length(char *line)
{
    int i;

    for (i = 1; line[i] != '\0'; i++) {
        if (!(line[i] >= '0' && line[i] <= '9'))
            return i + 1;
    }
    return i + 1;
}

static int get_word_length(char *line)
{
    int j;

    for (j = 0; line[j] != ' ' && line[j] != '\0'; j++);
    return j + 1;
}

int get_len_exclamation(char *line)
{
    if (is_empty(line))
        return 0;
    if (is_exclamation(line))
        return 2;
    if (is_number_start(line))
        return get_number_length(line);
    return get_word_length(line);
}
