/*
** EPITECH PROJECT, 2024
** my_revstr.c
** File description:
** return a char in reversed
*/
#include <unistd.h>
#include "../../include/my.h"

char *my_revstr(char *str)
{
    int i;
    int len = my_strlen(str);
    int temp;

    for (i = 0; i < (len / 2); i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}
