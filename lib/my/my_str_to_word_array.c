/*
** EPITECH PROJECT, 2024
** myradar
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>
#include <stdio.h>

int is_alphanumeric(char c)
{
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9'));
}

static int count_words(char const *str, int (*func_cmp)(char))
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (in_word == 0 && func_cmp(str[i])) {
            in_word = 1;
            count++;
            continue;
        }
        if (in_word == 1 && !func_cmp(str[i]))
            in_word = 0;
    }
    return count;
}

static int word_l(char const *str, int start, int (*func_cmp)(char))
{
    int len = 0;

    while (str[start + len] && func_cmp(str[start + len]))
        len++;
    return len;
}

static void get_word(char *array, char const *str, int i, int len)
{
    for (int k = 0; k < len; k++) {
        array[k] = str[i + k];
    }
    array[len] = '\0';
}

char **my_str_to_word_array(char const *str, int (*func_cmp)(char))
{
    int word_count = count_words(str, func_cmp);
    char **array = malloc(sizeof(char *) * (word_count + 1));
    int len = 0;
    int i = 0;
    int j = 0;

    if (!str)
        return NULL;
    while (str[i]) {
        if (func_cmp(str[i])) {
            len = word_l(str, i, func_cmp);
            array[j] = malloc(sizeof(char) * (len + 1));
            get_word(array[j], str, i, len);
            j++;
            i += len;
        } else
            i++;
    }
    array[j] = NULL;
    return array;
}
