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
    char *value = NULL;

    if (my_strcmp(name, "term") == 0)
        return my_getenv(*env, "TERM");
    if (my_strcmp(name, "cwd") == 0)
        return get_cwd(env);
    value = check_variable(name, env);
    if (value)
        return value;
    return my_getenv(*env, name);
}

char *get_variable_name(char *input, int *i)
{
    char *var = NULL;
    int pos = *i;
    int j = 0;

    if (input[pos] != '\0' && (input[pos] == '_' || isalnum(input[pos]))) {
        var = my_malloc(sizeof(char) * (my_strlen(input) + 1));
        while (input[pos] != '\0' &&
            (input[pos] == '_' || isalnum(input[pos]))) {
            var[j] = input[pos];
            j++;
            pos++;
        }
        var[j] = '\0';
        *i = pos - 1;
    } else
        return NULL;
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
        result = concat_result(result, value, j);
        my_free(var);
    } else {
        result[*j] = '$';
        (*j)++;
    }
    result[*j] = '\0';
}

static char *extract_braced_variable(char *input, int *i)
{
    int start = *i + 1;
    int end = start;
    char *var = NULL;
    int len;

    while (input[end] != '\0' && input[end] != '}')
        end++;
    if (input[end] == '}') {
        len = end - start;
        var = my_malloc(sizeof(char) * (len + 1));
        strncpy(var, &input[start], len);
        var[len] = '\0';
        *i = end;
    } else
        *i = start - 2;
    return var;
}

static void process_braced_variable(char *input, char *result,
    minishel_t **env)
{
    char *var = NULL;
    char *value = NULL;
    iteration_t *iter = get_iterations();
    
    iter->i++;
    var = extract_braced_variable(input, &(iter->i));
    
    if (var) {
        value = get_expand_variables(env, var);
        result = concat_result(result, value, &(iter->j));
        my_free(var);
    } else {
        result[iter->j] = '$';
        iter->j++;
        result[iter->j] = '{';
        iter->j++;
        result[iter->j] = '\0';
    }
}

static void process_simple_variable(char *input, char *result,
    minishel_t **env)
{
    char *var = NULL;
    iteration_t *iter = get_iterations();

    iter->i++;
    var = get_variable_name(input, &(iter->i));
    manage_variable_value(&(iter->j), result, env, var);
}

static void process_variable(char *input, char *result, minishel_t **env)
{
    iteration_t *iter = get_iterations();

    if (input[iter->i + 1] == '{')
        process_braced_variable(input, result, env);
    else
        process_simple_variable(input, result, env);
}

char *expand_variables(char *input, minishel_t **env)
{
    char *result = my_malloc(sizeof(char) * (my_strlen(input) * 2
        + PATH_MAX + 1));
    iteration_t *iter = get_iterations();

    iter->i = 0;
    iter->j = 0;
    result[0] = '\0';
    for (; input[iter->i] != '\0'; iter->i++) {
        if (input[iter->i] == '$') {
            process_variable(input, result, env);
        } else {
            result[iter->j] = input[iter->i];
            iter->j++;
            result[iter->j] = '\0';
        }
    }
    return result;
}
