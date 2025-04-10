/*
** EPITECH PROJECT, 2025
** other
** File description:
** refactored_other_clean_strict
*/

#include "../../include/minishel.h"

static int is_space(char c)
{
    return (c <= ' ');
}

static void skip_bound_spaces(char *input, int *start, int *end)
{
    while (*start < *end && is_space(input[*start]))
        (*start)++;
    while (*end > *start && is_space(input[*end - 1]))
        (*end)--;
}

static char *copy_cleaned_token(char *input, int start, int end)
{
    char *res;
    int j = 0;

    skip_bound_spaces(input, &start, &end);
    if (start >= end)
        return NULL;
    res = malloc(sizeof(char) * (end - start + 1));
    if (!res)
        return NULL;
    for (int i = start; i < end; i++) {
        res[j] = input[i];
        j++;
    }
    res[j] = '\0';
    return res;
}

static void update_count_state(int *count, int *has_prev, char *input, int *i)
{
    if (*has_prev)
        (*count)++;
    (*count)++;
    *has_prev = 0;
    if (is_double_sep(input, *i))
        (*i)++;
}

static int count_args_for_parentheses(char *input)
{
    int level = 0;
    int count = 0;
    int has_prev = 0;

    for (int i = 0; input[i]; i++) {
        if (input[i] == '(')
            level++;
        if (input[i] == ')')
            level--;
        if (level == 0 && is_simple_sep(input[i]))
            update_count_state(&count, &has_prev, input, &i);
        if (!is_space(input[i]) && !(level == 0 && is_simple_sep(input[i])))
            has_prev = 1;
    }
    if (has_prev)
        count++;
    return count;
}

static void add_arg_token(char **array, int *index,
    char *input, parse_ctx_t *ctx)
{
    char *arg = copy_cleaned_token(input, ctx->start, ctx->i);

    if (arg) {
        array[(*index)] = arg;
        (*index)++;
    }
}

static void add_sep_token(char **array, int *index, char *input, int *i)
{
    int len = is_double_sep(input, *i) ? 2 : 1;

    array[*index] = malloc(sizeof(char) * (len + 1));
    if (!array[*index])
        return;
    for (int j = 0; j < len; j++)
        array[*index][j] = input[*i + j];
    array[*index][len] = '\0';
    (*i) += len - 1;
    (*index)++;
}

static void handle_token(parse_ctx_t *ctx, char **array, char *input)
{
    add_arg_token(array, &ctx->index, input, ctx);
    add_sep_token(array, &ctx->index, input, &ctx->i);
    ctx->start = ctx->i + 1;
}

char **string_to_array_for_parentheses(char *input)
{
    int count = count_args_for_parentheses(input);
    char **array = malloc(sizeof(char *) * (count + 1));
    parse_ctx_t ctx = {0, 0, 0, 0};

    if (!array)
        return NULL;
    while (input[ctx.i]) {
        if (input[ctx.i] == '(')
            ctx.level++;
        if (input[ctx.i] == ')')
            ctx.level--;
        if (ctx.level == 0 && is_simple_sep(input[ctx.i]))
            handle_token(&ctx, array, input);
        ctx.i++;
    }
    add_arg_token(array, &ctx.index, input, &ctx);
    array[ctx.index] = NULL;
    return array;
}

char *clean_parenthese_argv(char *cmd)
{
    int len;
    char *new;

    if (!cmd)
        return NULL;
    len = my_strlen(cmd);
    if (len < 2 || cmd[0] != '(' || cmd[len - 1] != ')')
        return my_strdup(cmd);
    new = malloc(sizeof(char) * (len - 1));
    if (!new)
        return NULL;
    strncpy(new, cmd + 1, len - 2);
    new[len - 2] = '\0';
    return new;
}
