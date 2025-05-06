/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_if.c
*/

#include "../include/minishel.h"

if_ctx_t get_if(void)
{
    static if_ctx_t if_context = {0};
    return &if_context;
}

int is_complete(char *input)
{
    int lvl = 0;
    char *then = NULL;

    if (strncmp(input, "if ", 3) != 0 && strncmp(input, "if(", 3) != 0)
        return 1;

}