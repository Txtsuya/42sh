/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** backtics.c
*/

#include "../include/minishel.h"

int count_backticks(char *line)
{
    int cpt = 0;

    for (int i = 0; line[i] != '\0'; i++)
        cpt += line[i] == '`';
    return cpt;
}

int len_backticks(char *line)
{
    int cpt = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '`')
            return i + 2;
    }
    return 2;
}

char *exec_backticks(char *line, minishel_t **llenv)
{
    char *new_val = extract_between_c(line, '`');
    char *buffer = get_buffer_backticks(new_val, llenv);

    my_free(new_val);
    return buffer;
}

char *replace_backticks(char **args, int i, minishel_t **llenv)
{
    int len1 = 0;
    int idx = 0;
    char *val = NULL;

    if ((*args)[i] == '`') {
        len1 = len_backticks(&(*args)[i + 1]);
        idx = i;
        val = exec_backticks(*args, llenv);
        if (val != NULL && len1 != 0)
            return replace_in_array(*args, val, idx, len1);
    }
    return NULL;
}

int handle_back_ticks(char **line, minishel_t **llenv)
{
    int nbr = count_backticks(*line);
    char *dest = NULL;

    if (nbr == 0)
        return 0;
    if (nbr % 2 == 1)
        return 1;
    for (int i = 0; (*line)[i] != '\0'; i++) {
        dest = replace_backticks(line, i, llenv);
        if (dest != NULL)
            break;
    }
    if (dest != NULL) {
        *line = dest;
        handle_back_ticks(line, llenv);
        return 1;
    }
    return 0;
}
