/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../../include/minishel.h"

int get_num(char *cmd)
{
    if (cmd[0] == '%') {
        return my_getnbr(&cmd[1]);
    }
    return my_getnbr(cmd);
}

int forground(char **args)
{
    int id = args[1] ? get_num(args[1]) : 1;
    job_t *job = find_job_by_id(id);
    int status;
    struct sigaction sa_ttou, old_sa_ttou;

    if (!job) {
        my_putstr("No such job\n");
        return 1;
    }
    my_putstr(job->command);
    my_putstr("\n");
    kill(-job->pid, SIGCONT);
    job->state = JOB_RUNNING;
    setpgid(job->pid, job->pid);
    sa_ttou.sa_handler = SIG_IGN;
    sigemptyset(&sa_ttou.sa_mask);
    sa_ttou.sa_flags = 0;
    sigaction(SIGTTOU, &sa_ttou, &old_sa_ttou);
    tcsetpgrp(STDIN_FILENO, job->pid);
    waitpid(job->pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    sigaction(SIGTTOU, &old_sa_ttou, NULL);
    if (WIFSTOPPED(status)) {
        job->state = JOB_STOPPED;
        printf("[%d]+  Stopped\t%s\n", job->id, job->command);
        return 1;
    }
    job->state = JOB_DONE;
    return 1;
}

int background(char **args)
{
    int id = args[1] ? get_num(args[1]) : 1;
    job_t *job = find_job_by_id(id);

    if (!job) {
        my_putstr("No such job\n");
        return 1;
    }
    kill(-job->pid, SIGCONT);
    job->state = JOB_RUNNING;
    return 1;
}