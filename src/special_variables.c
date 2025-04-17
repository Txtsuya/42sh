/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** special_variables
*/

#include "../include/minishel.h"

static char *get_cwd(minishel_t **env)
{
    static char cwd_var[PATH_MAX];

    if (getcwd(cwd_var, PATH_MAX) != NULL)
        return cwd_var;
    return my_getenv(*env, "PWD");
}

int handle_ignoreeof(char **input, minishel_t **env)
{
    if (get_special_variable("ignoreeof", env) != NULL
        && isatty(STDIN_FILENO)) {
        printf("\nUse 'exit' to leave 42sh.\n");
        *input = my_strdup("");
        clearerr(stdin);
        return 0;
    }
    return 84;
}

minishel_t *get_special_variable(char *name, minishel_t **env)
{
    minishel_t **var = get_variable();
    minishel_t *current;

    if (var == NULL || *var == NULL)
        return NULL;
    current = *var;
    while (current != NULL) {
        if (my_strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

static char *get_expand_variables(minishel_t **env, char *name)
{
    minishel_t *var = get_special_variable(name, env);

    if (my_strcmp(name, "term") == 0)
        return my_getenv(*env, "TERM");
    if (my_strcmp(name, "cwd") == 0)
        return get_cwd(env);
    if (check_variable(name, env) == NULL)
        return my_getenv(*env, name);
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
    *i = pos - 1;
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
    result[*j] = '\0';
    return result;
}

static void manage_variable_value(int *j, char *result, minishel_t **env,
    char *var)
{
    char *value = NULL;

    if (var) {
        value = get_expand_variables(env, var);
        result = concat_result(result, value, &j);
    } else {
        result[*j] = '$';
        (*j)++;
    }
    result[*j] = '\0';
}

char *expand_variables(char *input, minishel_t **env)
{
    char *result = my_malloc(sizeof(char) * (my_strlen(input) * 2 + PATH_MAX + 1));
    char *var = NULL;
    char *value = NULL;
    int i = 0;
    int j = 0;

    result[0] = '\0';
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == '$') {
            i++;
            var = get_variable_name(input, &i);
            manage_variable_value(&j, result, env, var);
        } else {
            result[j] = input[i];
            j++;
            result[j] = '\0';
        }
    }
    return result;
}
