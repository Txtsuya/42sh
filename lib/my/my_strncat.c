/*
** EPITECH PROJECT, 2024
** my_strncat
** File description:
** concatenate 2 string into one
*/

#include "../../include/my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int j = 0;

    while (dest[j] != '\0') {
        j++;
    }
    while (src[i] != '\0' && nb > i) {
        dest[j + i] = src[i];
        i++;
    }
    if (nb > i + j){
        dest[j + i] = '\0';
    }
    return dest;
}
