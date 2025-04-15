/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../../include/minishel.h"

int is_sep(char c)
{
    return (c != '&');
}

int execute_background(char *cmd, minishel_t **llenv)
{
    job_t *added_jobs = NULL;
    pid_t pid = fork();

    if (pid == 0) {
        exit(execute_main_cmd(cmd, llenv));
    } else {
        added_jobs = add_job(pid, cmd);
        printf("[%d] %d\n", added_jobs->id, pid);
    }
    return 0;
}

int handle_background(char *cmd, minishel_t **llenv)
{
    char **all_cmd = my_str_to_word_array(cmd, is_sep);
    int len = len_array(all_cmd);

    for (int i = 0; all_cmd[i]; i++) {
        execute_background(all_cmd[i], llenv);
    }
    return 0;
}
