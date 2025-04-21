/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** if
*/

#include "minishel.h"

int check_if_args(char *str)
{
    if (my_strcmp("if ", str) == 0 || my_strcmp("if(", str) == 0)
        return 1;
    return 0;
}

char *extract_condition(char *str)
{
    char *start = my_strchr(str, '(');
    char *end = my_strchr(str, ')');
    int len = 0;
    char *condition = NULL;

    if (!start || !end || !str)
        return NULL;
    len = end - start - 1;
    condition = my_malloc(len + 1);
    strncpy(condition, start + 1, len);
    condition[len] = '\0';
    return condition;
}

int handle_if(char **args, minishel_t **llenv)
{
    int condition = 0;

    if (args[1] == NULL)
        printf("if: Too few arguments.\n");
}