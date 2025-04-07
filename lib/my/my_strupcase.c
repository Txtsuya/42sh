/*
** EPITECH PROJECT, 2024
** my_strupcase
** File description:
** return char with all letter in uppercase
*/
#include <stdio.h>

char *my_strupcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] = str[i] - 32;
        }
        i++;
    }
    return (str);
}
