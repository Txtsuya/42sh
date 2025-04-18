/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** varible_handling
*/

#include "minishel.h"

iteration_t *get_iterations(void)
{
    static iteration_t iteration;

    return &iteration;
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

void manage_variable_value(int *j, char *result, minishel_t **env,
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

char *check_variable(char *name, minishel_t **env)
{
    minishel_t **var = get_variable();
    minishel_t *current = *var;

    while (current) {
        if (my_strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}
