/*
** EPITECH PROJECT, 2024
** my_strstr.c
** File description:
** task5
*/
#include <stddef.h>

static int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}

static int besoin(int cpt, char *str, char const *to_find)
{
    int i = 0;
    int longeur_tofind = my_strlen(to_find);

    while (str[cpt + i] == to_find[i] && to_find[i] != '\0') {
        i++;
        if (i == longeur_tofind) {
            return 1;
        }
    }
    return 0;
}

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int k;

    while (str[i] != '\0') {
        k = besoin(i, str, to_find);
        if (k == 1)
            return &str[i];
        i++;
    }
    if (to_find[0] == '\0')
        return str;
    return NULL;
}
