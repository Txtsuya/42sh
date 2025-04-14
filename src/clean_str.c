/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** clean_str.c
*/

#include "../include/minishel.h"
#include "minishel.h"

static int find_start(const char *str)
{
    int i = 0;

    while (str[i] && isspace((unsigned char)str[i]))
        i++;
    return i;
}

static int find_end(const char *str, int start)
{
    int end = strlen(str) - 1;

    while (end > start && isspace((unsigned char)str[end]))
        end--;
    return end;
}

static int calculate_trimmed_length(const char *str, int start, int end)
{
    int len = 0;
    int space = 0;

    for (int i = start; i <= end; i++) {
        checklen(str, i, &len, &space);
    }
    return len;
}

void checklen(const char *str, int i, int *len, int *space)
{
    if (isspace((unsigned char)str[i])) {
        if (!space) {
            (*len)++;
            *space = 1;
        }
    } else {
        (*len)++;
        *space = 0;
    }
}

static void chexkcpoy(const char *str, int i, char *result, int *k)
{
    static int space = 0;

    if (isspace((unsigned char)str[i])) {
        if (!space) {
            result[*k] = ' ';
            space = 1;
            (*k)++;
        }
    } else {
        result[*k] = str[i];
        space = 0;
        (*k)++;
    }
}

void copy_trimmed(const char *str, int start, int end, char *result)
{
    int k = 0;

    for (int i = start; i <= end; i++) {
        chexkcpoy(str, i, result, &k);
    }
    result[k] = '\0';
}

char *clean_str(const char *str)
{
    int start = find_start(str);
    int end = find_end(str, start);
    int new_len = calculate_trimmed_length(str, start, end);
    char *result = malloc(new_len + 1);

    if (!result)
        return NULL;
    copy_trimmed(str, start, end, result);
    return result;
}
