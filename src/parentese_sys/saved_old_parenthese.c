/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../../include/minishel.h"

int handle_is_redirection_after_pipe(minishel_t **llenv, char **all_arg, int i)
{
    int redir_index = 0;

    if (all_arg[i + 1] == NULL) {
        return execute_main_cmd(clean_parenthese_argv(all_arg[i]), llenv);
    } else {
        redir_index = is_red_or_operator(all_arg[i + 1]);
        if (redir_index > 1) {
            return handle_redirection_in_parenthese(all_arg + i, llenv);
        } else {
            printf("Ambiguous input redirect.\n");
        }
    }
    return 0;
}

static void dup_middle_process(pipe_ctx_t *ctx, int i)
{
    int cmd_idx = 2 * i;

    if (ctx->pid[i] == 0) {
        dup2(ctx->pipefd[ctx->read_pipe][0], STDIN_FILENO);
        dup2(ctx->pipefd[ctx->write_pipe][1], STDOUT_FILENO);
        close(ctx->pipefd[0][0]);
        close(ctx->pipefd[0][1]);
        close(ctx->pipefd[1][0]);
        close(ctx->pipefd[1][1]);
        execute_multi_cmd(ctx->env, clean_parenthese_argv(ctx->argv[cmd_idx]));
        exit(0);
    }
}

static void middle_processes(pipe_ctx_t *ctx)
{
    if (ctx->num_of_pipe <= 1)
        return;
    for (int i = 1; i < ctx->num_of_pipe; i++) {
        ctx->read_pipe = (i - 1) % 2;
        ctx->write_pipe = i % 2;
        if (i > 1) {
            close(ctx->pipefd[ctx->write_pipe][0]);
            close(ctx->pipefd[ctx->write_pipe][1]);
            pipe(ctx->pipefd[ctx->write_pipe]);
        }
        ctx->pid[i] = fork();
        dup_middle_process(ctx, i);
        close(ctx->pipefd[ctx->read_pipe][0]);
        close(ctx->pipefd[ctx->read_pipe][1]);
        if (i < ctx->num_of_pipe - 1) {
            pipe(ctx->pipefd[ctx->read_pipe]);
        }
    }
}

static void first_process(pipe_ctx_t *ctx)
{
    ctx->pid[0] = fork();
    if (ctx->pid[0] == 0) {
        close(ctx->pipefd[0][0]);
        if (ctx->num_of_pipe > 1) {
            close(ctx->pipefd[1][0]);
            close(ctx->pipefd[1][1]);
        }
        dup2(ctx->pipefd[0][1], STDOUT_FILENO);
        close(ctx->pipefd[0][1]);
        execute_multi_cmd(ctx->env, clean_parenthese_argv(ctx->argv[0]));
        exit(0);
    }
}

static void last_process(pipe_ctx_t *ctx)
{
    int last = ctx->num_of_pipe;
    int last_read_pipe = (last - 1) % 2;

    ctx->pid[last] = fork();
    if (ctx->pid[last] == 0) {
        dup2(ctx->pipefd[last_read_pipe][0], STDIN_FILENO);
        close(ctx->pipefd[0][0]);
        close(ctx->pipefd[0][1]);
        if (ctx->num_of_pipe > 1) {
            close(ctx->pipefd[1][0]);
            close(ctx->pipefd[1][1]);
        }
        handle_is_redirection_after_pipe(ctx->env, ctx->argv, last * 2);
        exit(0);
    }
}

static int wait_processes(int num_of_pipe, pid_t *pid)
{
    int return_value = 0;

    for (int i = 0; i <= num_of_pipe; i++) {
        if (pid[i] != getpid())
            waitpid(pid[i], &return_value, 0);
    }
    return return_value;
}

int handle_pipe_in_parenthese(char **all_arg, minishel_t **llenv, int num_sep)
{
    int pipefd[2][2];
    pid_t pid[num_sep + 1];
    int return_value;
    pipe_ctx_t ctx = {num_sep, pipefd, pid, llenv, all_arg, 0, 0};
    int pipes_needed = (num_sep > 1) ? 2 : num_sep;

    for (int i = 0; i < pipes_needed; i++)
        pipe(pipefd[i]);
    first_process(&ctx);
    middle_processes(&ctx);
    last_process(&ctx);
    for (int i = 0; i < pipes_needed; i++) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }
    return_value = wait_processes(num_sep, pid);
    return return_value;
}

int handle_redirection_parenthese(char **all_arg,
    minishel_t **llenv, int num_of_sep)
{
    if (is_red_or_operator(all_arg[1]) > -1) {
        return handle_redirection_in_parenthese(all_arg, llenv);
    } else {
        return handle_pipe_in_parenthese(all_arg, llenv, num_of_sep);
    }
}

int search_pipe(char *input)
{
    int level = 0;
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(')
            level++;
        if (input[i] == ')')
            level--;
        if (level == 0 && input[i] == '|') {
            count++;
        }
    }
    return count;
}

int handle_parenthese(minishel_t **llenv, char *input)
{
    int num_sep = search_pipe(input);
    char **all_arg = string_to_array_for_parentheses(input);
    int arraylen = len_array(all_arg);

    if (check_error_parenthese(all_arg, input, arraylen) == 1) {
        free_array(all_arg);
        return 1;
    }
    if (len_array(all_arg) == 1) {
        return execute_multi_cmd(llenv, clean_parenthese_argv(all_arg[0]));
    } else {
        return handle_redirection_parenthese(all_arg, llenv, num_sep);
    }
}