/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** extract_between_quotes.c
*/

#include "../../include/minishel.h"

char *extract_between_quotes(const char *str)
{
    const char *start;
    const char *end;
    char *result;
    int length;

    start = my_strchr(str, '"');
    if (start == NULL)
        return NULL;
    start++;
    end = my_strchr(start, '"');
    if (end == NULL)
        return NULL;
    length = end - start;
    result = (char *)my_malloc(sizeof(char) *(length + 1));
    if (result == NULL)
        return NULL;
    for (int i = 0; i < length; i++)
        result[i] = start[i];
    result[length] = '\0';
    return result;
}
