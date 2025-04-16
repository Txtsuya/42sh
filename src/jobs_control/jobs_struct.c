/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../../include/minishel.h"

static void remove_job_if_match(job_t **jobs, job_t *current,
    job_t *prev, int job_id)
{
    if (current->id == job_id) {
        if (prev)
            prev->next = current->next;
        else
            *jobs = current->next;
        my_free(current->command);
        my_free(current);
    }
}

void remove_job(int job_id)
{
    job_t **jobs = get_job_list();
    job_t *current = *jobs;
    job_t *prev = NULL;

    while (current) {
        if (current->id == job_id) {
            remove_job_if_match(jobs, current, prev, job_id);
            return;
        }
        prev = current;
        current = current->next;
    }
}

job_t *find_job_by_pid(pid_t pid)
{
    job_t **jobs = get_job_list();
    job_t *current = *jobs;

    while (current) {
        if (current->pid == pid)
            return current;
        current = current->next;
    }
    return NULL;
}

void print_jobs_done(void)
{
    job_t **jobs = get_job_list();
    job_t *current = *jobs;

    while (current) {
        if (current->state == JOB_DONE) {
            printf("[%d] %s:Done\n", current->id, current->command);
            remove_job(current->id);
        }
        current = current->next;
    }
}

static void update_job_status_for_pid(pid_t pid, int status)
{
    job_t *job = NULL;

    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        job = find_job_by_pid(pid);
        if (job) {
            job->state = JOB_DONE;
        }
    }
}

void update_jobs_status(void)
{
    int status;
    pid_t pid;

    for (
        pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
        pid > 0;
        pid = waitpid(-1, &status, WNOHANG | WUNTRACED)
    ) {
        update_job_status_for_pid(pid, status);
    }
}

int print_jobs(char **args, minishel_t **llenv)
{
    job_t **jobs = get_job_list();
    job_t *current = *jobs;

    while (current) {
        printf("[%d] %s %s\n",
            current->id,
            current->state == JOB_RUNNING ? "Running" : "Stopped",
            current->command);
        current = current->next;
    }
    return 1;
}
