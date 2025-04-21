/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** extract_cmd
*/

#include "minishel.h"

char *extract_then(char *str)
{
    char *start = my_strstr(str, "then");
    char *else_part = my_strstr(str, "else");
    char *endif_part = my_strstr(str, "endif");
    int len = 0;
    char *cmd = NULL;

    if (!start)
        return NULL;
    start += 4;
    while (*start && isspace(*start))
        start++;
    if (else_part && (!endif_part || else_part < endif_part))
        endif_part = else_part;
    if (!endif_part)
        return NULL;
    len = endif_part - start;
    cmd = my_malloc(len + 1);
    strncpy(cmd, start, len);
    cmd[len] = '\0';
    return cmd;
}

