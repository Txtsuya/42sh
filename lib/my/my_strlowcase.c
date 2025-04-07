/*
** EPITECH PROJECT, 2024
** my_strlowcase.c
** File description:
** transform every letter in lowercase
*/

#include <stdio.h>
#include "../../include/my.h"

char *my_strlowcase(char *besoin)
{
    int i = 0;
    char *str = my_strdup(besoin);

    while (str[i] != '\0') {
        if (str[i] >= 65 && str[i] <= 90) {
            str[i] = str[i] + 32;
        }
        i++;
    }
    return (str);
}
