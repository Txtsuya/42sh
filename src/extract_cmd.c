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

char *extract_else(char *str)
{
    char *endif_part = my_strstr(str, "endif");
    int len = 0;
    char *cmd = NULL;

    if (!str || !endif_part)
        return NULL;
    str += 4;
    while (*str && isspace(*str))
        str++;
    len = endif_part - str;
    cmd = my_malloc(len + 1);
    strncpy(cmd, str, len);
    cmd[len] = '\0';
    return cmd;
}

static int is_if_statement_start(const char *str)
{
    return (my_strncmp(str, "if ", 3) == 0 || my_strncmp(str, "if(", 3) == 0);
}

static char *handle_nested_if(char *current, int *nesting)
{
    char *nested_then = strstr(current + 3, "then");

    if (!nested_then)
        return current + 1;
    *nesting += 1;
    return nested_then + 4;
}

static char *handle_endif(char *current, int *nesting, int *should_return_null)
{
    *nesting -= 1;
    *should_return_null = (*nesting == 0);
    return current + 5;
}

static char *handle_else(char *current, int nesting, int *found_else)
{
    *found_else = (nesting == 1);
    return current;
}

int should_continue_search(char *current, int *nesting, int *found_else,
    int *should_return_null)
{
    if (is_if_statement_start(current)) {
        *nesting += 1;
        return 1;
    }
    if (strncmp(current, "endif", 5) == 0) {
        *nesting -= 1;
        *should_return_null = (*nesting == 0);
        return 1;
    }
    if (strncmp(current, "else", 4) == 0) {
        *found_else = (*nesting == 1);
        return !(*found_else);
    }
    return 1;
}

char *process_tokens(char *current, int *nesting, int *found_else,
    int *should_return_null)
{
    while (*current && !*found_else && !*should_return_null) {
        if (!should_continue_search(current, nesting,
            found_else, should_return_null)) {
            break;
        }
        current++;
    }
    return current;
}

char *find_else(char *input)
{
    char *then_part = strstr(input, "then");
    char *current = NULL;
    int nesting = 1;
    int should_return_null = 0;
    int found_else = 0;

    if (!then_part)
        return NULL;
    current = then_part + 4;
    current = process_tokens(current, &nesting, &found_else,
        &should_return_null);
    if (should_return_null || !found_else)
        return NULL;
    return current;
}
