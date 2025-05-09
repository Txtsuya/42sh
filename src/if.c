/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** if - version modifiée
*/

#include "minishel.h"

char *extract_condition(char *str)
{
    char *start = strchr(str, '(');
    char *end = strchr(str, ')');
    int len = 0;
    char *condition = NULL;

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

int has_then_keyword(char *input)
{
    char *closing_paren = strchr(input, ')');

    if (!closing_paren)
        return 0;
    closing_paren++;
    while (*closing_paren && isspace(*closing_paren))
        closing_paren++;
    return (strcmp(closing_paren, "then") == 0);
}

static int parse_and_eval_if_condition(char *input, int *result)
{
    char *condition = NULL;

    input += 2;
    while (*input && isspace(*input))
        input++;
    condition = extract_condition(input);
    if (!condition) {
        printf("if: Expression Syntax.\n");
        return 1;
    }
    *result = bc_evaluation(condition);
    my_free(condition);
    return 0;
}

static int handle_if_exec(char *input, minishel_t **llenv, int result)
{
    char *cmd_after_if = NULL;

    if (has_then_keyword(input))
        return handle_if_interactive_mode(llenv, result);
    if (result) {
        cmd_after_if = strchr(input, ')');
        if (!cmd_after_if) {
            printf("Too many )'s.\n");
            return 1;
        }
        cmd_after_if++;
        while (*cmd_after_if && isspace(*cmd_after_if))
            cmd_after_if++;
        if (*cmd_after_if)
            return execute_multi_cmd(llenv, cmd_after_if);
    }
    return 0;
}

int handle_if(char *input, minishel_t **llenv)
{
    int result = 0;

    if (access("/usr/bin/bc", X_OK) == 0) {
        if (parse_and_eval_if_condition(input, &result))
            return 1;
        return handle_if_exec(input, llenv, result);
    }
    return 0;
}
