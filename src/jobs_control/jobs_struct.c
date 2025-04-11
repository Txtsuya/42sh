/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../../include/minishel.h"

job_t **get_job_list(void)
{
    static job_t *jobs = NULL;
    return &jobs;
}

job_t *add_job(pid_t pid, char *cmd)
{
    job_t **jobs = get_job_list();
    job_t *new_job = my_malloc(sizeof(job_t));
    job_t *tmp = *jobs;
    int max_id = 0;

    if (!new_job)
        return NULL;
    while (tmp) {
        if (tmp->id > max_id)
            max_id = tmp->id;
        tmp = tmp->next;
    }
    new_job->id = max_id + 1;
    new_job->command = my_strdup(cmd);
    new_job->pid = pid;
    new_job->state = JOB_RUNNING;
    new_job->next = *jobs;
    *jobs = new_job;
    return new_job;
}

job_t *find_job_by_id(int job_id)
{
    job_t **jobs = get_job_list();
    job_t *current = *jobs;

    while (current) {
        if (current->id == job_id)
            return current;
        current = current->next;
    }
    return NULL;
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

void remove_job(int job_id)
{
    job_t **jobs = get_job_list();
    job_t *current = *jobs;
    job_t *prev = NULL;
    
    while (current) {
        if (current->id == job_id) {
            if (prev)
                prev->next = current->next;
            else
                *jobs = current->next;
            my_free(current->command);
            my_free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void update_jobs_status(void)
{
    job_t **jobs = get_job_list();
    job_t *current = *jobs;
    job_t *next;
    int status;
    
    while (current) {
        next = current->next;
        waitpid(current->pid, &status, WUNTRACED);
        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            current->state = JOB_DONE;
            remove_job(current->id);
        }
        current = next;
    }
}

void print_jobs(void)
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
}
