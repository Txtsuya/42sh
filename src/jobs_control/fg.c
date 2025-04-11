/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../../include/minishel.h"

static void get_id_from_cmd(int *id, char **all_cmd)
{
    if (len_array(all_cmd) == 1) {
        *id = 1;
    }
    if (len_array(all_cmd) == 2) {
        *id = my_getnbr(&all_cmd[1][0]);
    }
}

static int get_job(int id, job_t **job_ptr)
{
    *job_ptr = find_job_by_id(id);
    if (*job_ptr == NULL) {
        my_putstr("No such job\n");
        return 84;
    }
    if ((*job_ptr)->state == JOB_RUNNING) {
        my_putstr("Job is already running\n");
        return 84;
    }
    return 0;
}

static int run_job(job_t *job_ptr)
{
    if (job_ptr->state == JOB_STOPPED) {
        kill(-job_ptr->pid, SIGCONT);
    }
    job_ptr->state = JOB_RUNNING;
    return 0;
}

static int wait_status(job_t *job_ptr)
{
    int is_stopped = 0;
    int status = 0;

    while (!is_stopped) {
        waitpid(-job_ptr->pid, &status, WUNTRACED);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            remove_job(job_ptr->id);
            is_stopped = 1;
        }
        if (WIFSTOPPED(status)) {
            job_ptr->state = JOB_STOPPED;
            is_stopped = 1;
        }
    }
    return status;
}

int forground(char **all_cmd, minishel_t **env)
{
    job_t *job_ptr = NULL;
    int id = 0;
    int shell_pgid = getpid();

    get_id_from_cmd(&id, all_cmd);
    if (get_job(id, &job_ptr) == 84)
        return 84;
    tcsetpgrp(STDIN_FILENO, job_ptr->pid);
    run_job(job_ptr);
    wait_status(job_ptr);
    tcsetpgrp(STDIN_FILENO, shell_pgid);
    printf("[%d] %d\n", job_ptr->id, job_ptr->pid);
    return 1;
}