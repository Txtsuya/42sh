/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../../include/minishel.h"

void handle_ctrlz(int child_pid)
{
    job_t *job = find_job_by_pid(child_pid);

    if (!job) {
        return;
    }
    job->state = JOB_STOPPED;
    tcsetpgrp(STDIN_FILENO, getpid());
    my_putstr("Suspended\n");
}

int check_stop_status(pid_t child_pid, int status)
{
    if (WIFSTOPPED(status)) {
        handle_ctrlz(child_pid);
        return 1;
    }
    return 0;
}
