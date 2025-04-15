/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** pipe.c
*/

#include "../include/minishel.h"

static void handle_child(int read_fd,
    int write_fd, char *cmd, minishel_t **env)
{
    int status = 0;

    if (read_fd != -1) {
        dup2(read_fd, STDIN_FILENO);
        close(read_fd);
    }
    if (write_fd != -1) {
        dup2(write_fd, STDOUT_FILENO);
        close(write_fd);
    }
    status = execute_main_cmd(cmd, env);
    exit(status);
}

static int create_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }
    return 0;
}

static int launch_command(char *cmd, int read_fd,
    int write_fd, minishel_t **env)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0)
        handle_child(read_fd, write_fd, cmd, env);
    return pid;
}

static int create_pipe_and_launch(char *token, pipeline_t *pl, int i)
{
    int *curr_pipe = (i % 2 == 0) ? pl->pipe1 : pl->pipe2;

    if (i < pl->nbr_cmd - 1 && create_pipe(curr_pipe))
        return 1;
    if (launch_command(token, pl->read_fd,
        (i < pl->nbr_cmd - 1 ? curr_pipe[1] : -1), pl->env) == -1)
        return 1;
    if (pl->read_fd != -1)
        close(pl->read_fd);
    if (i < pl->nbr_cmd - 1) {
        close(curr_pipe[1]);
        pl->read_fd = curr_pipe[0];
    }
    return 0;
}

static int execute_last_command(char *token, int read_fd, minishel_t **env)
{
    int status = 0;
    int saved_stdin = -1;
    int saved_stdout = -1;

    if (read_fd != -1) {
        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        dup2(read_fd, STDIN_FILENO);
        close(read_fd);
    }
    status = execute_main_cmd(token, env);
    if (read_fd != -1) {
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
    }
    return status;
}

static int launch_pipeline_command(char *token, pipeline_t *pl, int i)
{
    int *curr_pipe = (i % 2 == 0) ? pl->pipe1 : pl->pipe2;
    pid_t pid;

    if (i < pl->nbr_cmd - 1 && create_pipe(curr_pipe))
        return 1;
    pid = launch_command(token, pl->read_fd,
        (i < pl->nbr_cmd - 1 ? curr_pipe[1] : -1), pl->env);
    if (pid == -1)
        return 1;
    if (pl->read_fd != -1)
        close(pl->read_fd);
    if (i < pl->nbr_cmd - 1) {
        close(curr_pipe[1]);
        pl->read_fd = curr_pipe[0];
    }
    return 0;
}

int process_command(char *token, pipeline_t *pl, int index, int *status)
{
    if (index == pl->nbr_cmd - 1) {
        *status = execute_last_command(token, pl->read_fd, pl->env);
        return *status;
    }
    return launch_pipeline_command(token, pl, index) ? 1 : 0;
}

int execute_pipeline(char *commands, int nbr_cmd, minishel_t **env)
{
    pipeline_t pl = {.read_fd = -1, .nbr_cmd = nbr_cmd, .env = env};
    char *ptr = NULL;
    char **token = string_to_array_with_priority(commands, is_pipe);
    int status = 0;

    for (int i = 0; token[i]; i++) {
        if (process_command(token[i], &pl, i, &status))
            return 1;
    }
    for (int i = 0; i < nbr_cmd; i++)
        wait(NULL);
    return status;
}
