/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_arrow.c
*/

#include "minishel.h"

void handle_up_arrow(int *cursor, int *lenght, char **input)
{
    history_t *hty = *get_history();
}

void handle_arrow(int *cursor, int *lenght, char **input)
{
    char c;
    char d;

    read(STDIN_FILENO, &c, 1);
    read(STDIN_FILENO, &d, 1);
    if (c != 91)
        return;
    if (d == 67 && *cursor != *lenght)
        *cursor += 1;
    if (d == 68 && *cursor != 0)
        *cursor -= 1;
}