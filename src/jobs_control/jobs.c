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
    int pid = fork();

    if (pid == 0) {
        setpgid(0, 0);
        exit(execute_multi_cmd(llenv, cmd));
    } else {
        printf("[%d] %d\n", pid, getpid());
        setpgid(pid, pid);
    }
    return 0;
}

int jobs_control(char *cmd, minishel_t **llenv)
{
    int status = 0;
    char **all_cmd = my_str_to_word_array(cmd, is_sep);
    int len = len_array(all_cmd);

    for (int i = 0; all_cmd[i]; i++) {
        status = execute_background(all_cmd[i], llenv);
    }
    return status;
}
