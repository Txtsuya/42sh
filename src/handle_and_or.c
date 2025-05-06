/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** handle_op_and
*/

#include "minishel.h"

int handle_or_op(char *token, minishel_t **llenv)
{
    int status;
    char *or_token = my_strstr(token, "||");
    char *or_copy;
    error_t *err = get_error();

    if (or_token == NULL)
        return -1;
    or_copy = my_strdup(token);
    if (or_copy == NULL)
        return 1;
    or_copy[or_token - token] = '\0';
    err->error_cd = 0;
    status = handle_tok(or_copy, llenv);
    if (err->error_cd == 2)
        status = 1;
    if (status != 0)
        status = handle_tok(or_token + 2, llenv);
    my_free(or_copy);
    return status;
}

int handle_and_op(char *token, minishel_t **llenv)
{
    int status;
    char *and_token = my_strstr(token, "&&");
    char *and_copy;
    error_t *err = get_error();

    if (and_token == NULL)
        return -1;
    and_copy = my_strdup(token);
    if (and_copy == NULL)
        return 1;
    and_copy[and_token - token] = '\0';
    err->error_cd = 0;
    status = handle_tok(and_copy, llenv);
    if (err->error_cd == 2)
        status = 1;
    if (status == 0 && err->error_cd != 2)
        status = handle_tok(and_token + 2, llenv);
    my_free(and_copy);
    return status;
}
