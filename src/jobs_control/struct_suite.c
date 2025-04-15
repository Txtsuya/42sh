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

int len_array(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        i++;
    }
    return i;
}
