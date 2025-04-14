/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** mu_strchr.c
*/

#include "../../include/my.h"

char *my_strchr(const char *str, int c)
{
    while (*str != '\0') {
        if (*str == (char)c)
            return (char *)str;
        str++;
    }
    if ((char)c == '\0')
        return (char *)str;
    return NULL;
}
