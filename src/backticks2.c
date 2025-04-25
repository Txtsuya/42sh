/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** backticks2.c
*/

#include "../include/minishel.h"

void fill_buffer(const char *tmp, char **src, int len)
{
    *src = realloc(*src, len + strlen(tmp) + 1);
    strcat(*src + len, tmp);
}

int setup_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    return 0;
}

void handle_child_process(int pipefd[2], minishel_t **llenv, char *cmd)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    execute_multi_cmd(llenv, cmd);
    exit(1);
}

char *read_from_pipe(int pipefd[0])
{
    char tmp[128];
    int total_len = 0;
    char *result = calloc(1, 1);
    ssize_t n;

    n = read(pipefd[0], tmp, sizeof(tmp) - 1);
    while (n > 0) {
        tmp[n] = '\0';
        fill_buffer(tmp, &result, total_len);
        total_len += n;
        n = read(pipefd[0], tmp, sizeof(tmp) - 1);
    }
    return result;
}

char *get_buffer_backticks(char *cmd, minishel_t **llenv)
{
    int pipefd[2];
    char *result;
    pid_t pid;

    if (setup_pipe(pipefd) == -1)
        return NULL;
    pid = fork();
    if (pid == 0) {
        handle_child_process(pipefd, llenv, cmd);
    } else {
        close(pipefd[1]);
        result = read_from_pipe(pipefd);
        close(pipefd[0]);
        wait(NULL);
    }
    return result;
}
