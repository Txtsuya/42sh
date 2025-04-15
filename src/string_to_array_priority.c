/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../include/minishel.h"

void update_level(level_ini_t *level, char input)
{
    if (input == '(')
        level->level_par += 1;
    if (input == ')')
        level->level_par -= 1;
    if (input == '\'') {
        if (level->level_signle == 1)
            level->level_signle -= 1;
        else
            level->level_signle += 1;
    }
    if (input == '\"') {
        if (level->level_double == 1)
            level->level_double -= 1;
        else
            level->level_double += 1;
    }
}

int is_level_0(level_ini_t *level)
{
    if (level->level_par == 0 &&
        level->level_double == 0 &&
        level->level_signle == 0) {
            return 1;
    } else {
        return 0;
    }
}

static int count_arg(char *input, int (*func)(char))
{
    level_ini_t level = {0};
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        update_level(&level, input[i]);
        if (func(input[i]) && is_level_0(&level)) {
            count++;
        }
    }
    return count + 1;
}

static char *copy_string_to_array(char *input,
    char **array, int start, int end)
{
    int length = end - start;
    char *temp = malloc(sizeof(char) * (length + 1));

    for (int i = 0; i < length; i++)
        temp[i] = input[start + i];
    temp[length] = '\0';
    return temp;
}

char *process_string(char *str)
{
    int len = strlen(str);
    char *cleaned = malloc(sizeof(char) * (len + 1));
    int j = 0;
    int k = 0;

    if (cleaned == NULL)
        return NULL;
    for (; j < len; j++) {
        if (str[j] != '\'' && str[j] != '\"') {
            cleaned[k] = str[j];
            k++;
        }
    }
    cleaned[k] = '\0';
    return cleaned;
}

char **clean_quote(char **array)
{
    char **cleaned;
    int i;
    int count = 0;

    for (i = 0; array[i] != NULL; i++)
        count++;
    cleaned = malloc(sizeof(char *) * (count + 1));
    if (cleaned == NULL)
        return NULL;
    for (i = 0; array[i] != NULL; i++) {
        cleaned[i] = process_string(array[i]);
    }
    cleaned[count] = NULL;
    for (i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
    return cleaned;
}

char **string_to_array_with_priority(char *input, int (*func)(char))
{
    int start = 0;
    level_ini_t level = {0};
    int count_word = count_arg(input, func);
    int index = 0;
    char **array = malloc(sizeof(char *) * (count_word + 1));

    for (int i = 0; input[i] != '\0'; i++) {
        update_level(&level, input[i]);
        if (func(input[i]) && is_level_0(&level)) {
            array[index] = copy_string_to_array(input, array, start, i);
            index++;
            start = i + 1;
        }
    }
    array[index] = copy_string_to_array(input, array, start, strlen(input));
    array[index + 1] = NULL;
    return array;
}
