/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../../include/minishel.h"

static int redir_in(char **all_arg, minishel_t **llenv)
{
    int stdin_save = dup(STDIN_FILENO);
    int fd = open(all_arg[2], O_RDONLY);
    int status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);

    if (fd < 0) {
        perror(all_arg[2]);
        return 1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    status = execute_multi_cmd(llenv, cleaned_cmd);
    dup2(stdin_save, STDIN_FILENO);
    close(stdin_save);
    free(cleaned_cmd);
    return status;
}

static int here_doc(char **all_arg, minishel_t **llenv)
{
    int status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);

    if (redir_heredoc(all_arg[2]) != 0) {
        free(cleaned_cmd);
        return 1;
    }
    status = execute_multi_cmd(llenv, cleaned_cmd);
    free(cleaned_cmd);
    return status;
}

static int redir_out(char **all_arg, minishel_t **llenv)
{
    int stdout_save = dup(STDOUT_FILENO);
    int status = 0;
    int fd = open(all_arg[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);

    if (fd < 0) {
        perror(all_arg[2]);
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    status = execute_multi_cmd(llenv, cleaned_cmd);
    dup2(stdout_save, STDOUT_FILENO);
    close(stdout_save);
    free(cleaned_cmd);
    return status;
}

static int redir_dout(char **all_arg, minishel_t **llenv)
{
    int stdout_save = dup(STDOUT_FILENO);
    int status = 0;
    int fd = open(all_arg[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);

    if (fd < 0) {
        perror(all_arg[2]);
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    status = execute_multi_cmd(llenv, cleaned_cmd);
    dup2(stdout_save, STDOUT_FILENO);
    close(stdout_save);
    free(cleaned_cmd);
    return status;
}

static int redir_and(char **all_arg, minishel_t **llenv)
{
    int status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);
    char *all_arg2 = clean_parenthese_argv(all_arg[2]);

    status = execute_multi_cmd(llenv, cleaned_cmd);
    if (status == 0) {
        status = execute_multi_cmd(llenv, all_arg2);
    }
    free(cleaned_cmd);
    return status;
}

static int redir_or(char **all_arg, minishel_t **llenv)
{
    int status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);
    char *cleaned_cmd2 = clean_parenthese_argv(all_arg[2]);

    status = execute_multi_cmd(llenv, cleaned_cmd);
    if (status != 0) {
        status = execute_multi_cmd(llenv, cleaned_cmd2);
    }
    free(cleaned_cmd);
    return status;
}

int handle_redirection_in_parenthese(char **all_arg, minishel_t **llenv)
{
    int (*ptr[])(char **, minishel_t **) =
        {redir_in, here_doc, redir_out, redir_dout,
            redir_and, redir_or, NULL};
    int redir_index = is_red_or_operator(all_arg[1]);

    return ptr[redir_index](all_arg, llenv);
}