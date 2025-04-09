/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** special_variables
*/

#include "../include/minishel.h"

char *get_special_variables(minishel_t **env, char *name)
{
    if (my_strcmp(name, "term") == 0)
        return my_getenv(*env, "TERM");
    return my_getenv(*env, name);
}

char *get_variable_name(char *input, int *i)
{
    char *var = NULL;
    int pos = *i;
    int j = 0;

    while (input[pos] != '\0' && (input[pos] == '_' || isalnum(input[pos]))) {
        if (j == 0)
            var = my_malloc(sizeof(char) * (my_strlen(input) + 1));
        var[j++] = input[pos];
        pos++;
    }
    *i = pos;
    if (j == 0) {
        free(var);
        return NULL;
    }
    var[j] = '\0';
    return var;
}

char *expand_variables(char *input, minishel_t **env)
{
    char *result = my_malloc(sizeof(char) * (my_strlen(input) * 2 + 1));
    char *var = NULL;
    char *value = NULL;
    int i = 0;
    int j = 0;

    result[0] = '\0';
    while (input[i] != '\0') {
        if (input[i] == '$') {
            i++;
            var = get_variable_name(input, &i);
            value = get_special_variables(env, var);
            result = my_strcat(result, value);
            free(var);
        } else
            result[j++] = input[i++];
            result[j] = '\0';
        i++;
    }
    return result;
}
