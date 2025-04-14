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

static char *get_cwd(minishel_t **env)
{
    static char cwd_var[PATH_MAX];

    if (getcwd(cwd_var, PATH_MAX) != NULL)
        return cwd_var;
    return my_getenv(*env, "PWD");
}

char *get_special_variable(char *name)
{
    minishel_t **precmd_var = get_variable();
    minishel_t *tmp = *precmd_var;

    while (tmp) {
        if (my_strcmp(tmp->name, name) == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return NULL;
}

char *get_special_variables(minishel_t **env, char *name)
{
    if (my_strcmp(name, "term") == 0)
        return get_term(env, name);
    if (my_strcmp(name, "cwd") == 0)
        return get_cwd(env);
    return NULL;
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
        return NULL;
    }
    var[j] = '\0';
    return var;
}

char *concat_result(char *result, char *value, int *j)
{
    if (!value)
        return result;
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
        } else {
                result[j] = input[i];
                j++;
        }
        result[j] = '\0';
    }
    return result;
}
