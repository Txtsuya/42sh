/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** if
*/

#include "minishel.h"

int is_if_command(char *input)
{
    return (strncmp(input, "if ", 3) == 0 || strncmp(input, "if(", 3) == 0);
}

char *extract_condition(char *str)
{
    char *start = strchr(str, '(');
    char *end = strchr(str, ')');
    int len;
    char *condition;

    if (!start || !end || end <= start)
        return NULL;
    len = end - start - 1;
    if (len <= 0)
        return NULL;
    condition = my_malloc(len + 1);
    if (!condition)
        return NULL;
    strncpy(condition, start + 1, len);
    condition[len] = '\0';
    return condition;
}

int evaluate_condition(char *condition)
{
    return bc_evaluation(condition);
}

int exec_cmd_after_parenthesis(int result, minishel_t **llenv, char *input)
{
    if (result) {
        input = strchr(input, ')');
        if (!input) {
            printf("Too many )'s.");
            return 1;
        }
        input++;
        while (*input && isspace(*input))
            input++;
        if (*input)
            return execute_multi_cmd(llenv, input);
    }
    return 0;
}

int handle_if(char *input, minishel_t **llenv)
{
    char *condition;
    int result;
    char *then_part;
    char *command;

    input += 2;
    while (*input && isspace(*input))
        input++;
    condition = extract_condition(input);
    if (!condition) {
        printf("if: Expression Syntax.\n");
        return 1;
    }
    result = evaluate_condition(condition);
    my_free(condition);
    if (exec_cmd_after_parenthesis(result, llenv, input) == 1)
        return 1;
    return 0;
}
