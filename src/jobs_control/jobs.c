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

int jobs_control(char *cmd, minishel_t **llenv)
{
    int status = 0;
    char **all_cmd = my_str_to_word_array(cmd, is_sep);
    int len = len_array(all_cmd);

    for (int i = 0; all_cmd[i]; i++) {
        printf("all_cmd[%d] = %s$\n", i, all_cmd[i]);
    }
    return status;
}