/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** if
*/

#include "minishel.h"

int check_if_args(char *str)
{
    if (my_strcmp("if ", str) == 0 || my_strcmp("if(", str) == 0)
        return 1;
    return 0;
}

char *extract_condition(char *str)
{
    char *start = my_strchr(str, '(');
    char *end = my_strchr(str, ')');
    int len = 0;
    char *condition = NULL;

    if (!start || !end || !str)
        return NULL;
    len = end - start - 1;
    condition = my_malloc(len + 1);
    strncpy(condition, start + 1, len);
    condition[len] = '\0';
    return condition;
}

static void extract_part(char *str, minishel_t **llenv)
{
    char *then_cmd = extract_then(str);

    if (then_cmd) {
        execute_multi_cmd(llenv, then_cmd);
        my_free(then_cmd);
    }
}

static void handle_else(char *str, minishel_t **llenv)
{
    char *else_part = find_else(str);
    char *else_cmd = NULL;

    if (else_part) {
        else_cmd = extract_else(else_part);
        if (else_cmd) {
            execute_multi_cmd(llenv, str);
            my_free(else_cmd);
        }
    }
}

static int handle_then(char *str)
{
    char *then_part = my_strstr(str, "then");

    if (!then_part)
        return 1;
    return 0;
}

int handle_if(char *str, minishel_t **llenv)
{
    char *condition = extract_condition(str);
    int condition_result = 0;

    if (!condition) {
        printf("if: Empty if.\n");
        return 1;
    }
    condition_result = bc_evaluation(condition);
    if (!handle_then)
        return 1;
    if (condition_result)
        extract_part(str, llenv);
    else
        handle_else(str, llenv);
    return 0;
}
