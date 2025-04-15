/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** clean_str.c
*/

#include "../include/minishel.h"
#include "minishel.h"

static int find_end(const char *str, int start)
{
    int end = strlen(str) - 1;

    while (end > start && isspace((unsigned char)str[end]))
        end--;
    return end;
}

static int is_special_char(char c)
{
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' ||
        c == ']' || c == ';' || c == '|' ||
        c == '&' || c == '<' || c == '>';
}

static int should_add_space(const char *str, int i, int end)
{
    return (i + 1 <= end &&
        !isspace((unsigned char)str[i + 1]) &&
        !is_special_char(str[i + 1]) && i > 0 &&
        !is_special_char(str[i - 1]));
}

static void handle_space(const char *str, int *i, int end, int *len)
{
    if (should_add_space(str, *i, end))
        (*len)++;
    (*i)++;
}

static void handle_normal_char(int *i, int *len)
{
    (*len)++;
    (*i)++;
}

static int calculate_trimmed_length(const char *str, int start, int end)
{
    int len = 0;
    int i = start;

    while (i <= end) {
        if (isspace((unsigned char)str[i])) {
            handle_space(str, &i, end, &len);
            continue;
        }
        if (is_special_char(str[i])) {
            handle_normal_char(&i, &len);
            continue;
        }
        handle_normal_char(&i, &len);
    }
    return len;
}

static void copy_space(const char *str, int end, char *result, int *ik[2])
{
    if (should_add_space(str, *(ik[0]), end)) {
        result[*(ik[1])] = ' ';
        (*(ik[1]))++;
    }
    (*(ik[0]))++;
}

static void copy_normal_char(const char *str, int *i, char *result, int *k)
{
    result[*k] = str[*i];
    (*k)++;
    (*i)++;
}

void copy_trimmed(const char *str, int start, int end, char *result)
{
    int k = 0;
    int i = start;

    while (i <= end) {
        if (isspace((unsigned char)str[i])) {
            copy_space(str, end, result, (int *[]){&i, &k});
            continue;
        }
        if (is_special_char(str[i])) {
            copy_normal_char(str, &i, result, &k);
            continue;
        }
        copy_normal_char(str, &i, result, &k);
    }
    result[k] = '\0';
}

char *clean_str(const char *str)
{
    char *result;
    int new_len;
    int start;
    int end;

    if (!str)
        return NULL;
    start = find_start(str);
    end = find_end(str, start);
    new_len = calculate_trimmed_length(str, start, end);
    result = malloc(new_len + 1);
    if (!result)
        return NULL;
    copy_trimmed(str, start, end, result);
    return result;
}
