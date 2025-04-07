/*
** EPITECH PROJECT, 2024
** my_strncopy
** File description:
** copy n characters of src file into dest
*/

#include "../../include/my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
