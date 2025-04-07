/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** my strdup
*/
#include "../../include/my.h"
#include <stdlib.h>

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *dest;
    int i = 0;

    dest = malloc(sizeof(char) * len + 1);
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
