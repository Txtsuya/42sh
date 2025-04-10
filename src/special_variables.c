/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** special_variables
*/

#include "../include/minishel.h"

static char *get_term(minishel_t **env, char *name)
{
    return my_getenv(*env, "TERM");
}

char *get_special_variables(minishel_t **env, char *name)
{
    if (strcmp(name, "term") == 0)
        return get_term(env, name);
    if (strcmp(name, "cwd") == 0)
        return get_cwd(env);
}

char *get_variable_name(char *input, int *i)
{
    char *var = NULL;
    int pos = *i;
    int j = 0;

    while (input[pos] != '\0' && (input[pos] == '_' || isalnum(input[pos]))) {
        if (j == 0)
            var = my_malloc(sizeof(char) * (my_strlen(input) + 1));
        var[j] = input[pos];
        j++;
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

char *concat_result(char *result, char *value, int *j)
{
    for (int k = 0; value[k] != '\0'; k++) {
        result[*j] = value[k];
        (*j)++;
    }
    return result;
}

char *expand_variables(char *input, minishel_t **env)
{
    char *result = my_malloc(sizeof(char) * (my_strlen(input) * 2 + 1));
    char *var = NULL;
    char *value = NULL;
    int i = 0;
    int j = 0;

    result[0] = '\0';
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == '$') {
            i++;
            var = get_variable_name(input, &i);
            value = get_special_variables(env, var);
            result = concat_result(result, value, &j);
            my_free(var);
        } else {
                result[j] = input[i];
                j++;
        }
        result[j] = '\0';
    }
    return result;
}
