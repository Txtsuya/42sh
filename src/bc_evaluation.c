/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** bc_evaluation
*/

#include "minishel.h"

int exec_bc(char *condition)
{
    char *args[] = {"bc", "-l", NULL};
    int pipefd[2];

    if (pipe(pipefd) == -1)
        return -1;
    write(pipefd[1], condition, my_strlen(condition));
    write(pipefd[1], "\n", 1);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    execvp("bc", args);
    exit(1);
}

int bc_evaluation(char *condition, minishel_t **llenv)
{
    int pipefd[2];
    pid_t pid;
    int result = 0;

    if (pipe(pipefd) == -1)
        return 0;
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return 0;
    }
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exec_bc(condition);
    }
}