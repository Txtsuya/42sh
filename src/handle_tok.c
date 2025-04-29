/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** handle_tok
*/

#include "minishel.h"

int handle_tok(char *token, minishel_t **llenv)
{
    int status;

    if (validate_cmd_syntax(token) != 0)
        return 1;
    if (is_parentese(token))
        return handle_parenthese(llenv, token);
    status = handle_or_op(token, llenv);
    if (status != -1)
        return status;
    status = handle_and_op(token, llenv);
    if (status != -1)
        return status;
    return execute_simple_command(token, llenv);
}
