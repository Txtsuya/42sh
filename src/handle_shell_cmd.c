/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** handle_shell_cmd
*/

#include "../include/minishel.h"

int which_cmd(char *cmd, minishel_t **llenv)
{
    if (nbr_instr(cmd, '|'))
        return executepipe(cmd, llenv);
    else
        return execute_main_cmd(cmd, llenv);
}

int handle_repeat(char *cmd, minishel_t **llenv)
{
    int nb_repeat = 0;
    char *repeat_cmd = NULL;

    while (*cmd != ' ' && *cmd != '\0')
        cmd++;
    while (*cmd == ' ')
        cmd++;
    nb_repeat = atoi(cmd);
    while (*cmd != ' ' && *cmd != '\0')
        cmd++;
    while (*cmd == ' ')
        cmd++;
    repeat_cmd = my_strdup(cmd);
    for (int i = 0; i < nb_repeat; i++)
        which_cmd(repeat_cmd, llenv);
    return 0;
}

int handle_which(char *cmd, minishel_t **llenv)
{
    char *which_cmd = NULL;

    while (*cmd != ' ' && *cmd != '\0')
        cmd++;
    while (*cmd == ' ')
        cmd++;
    which_cmd = my_strdup(cmd);
    which_cmd = build_path_cmd(cmd, llenv);
    if (!which_cmd) {
        if (check_type(cmd) == 1) {
            printf("%s: shell built-in command.\n", cmd);
            return 1;
        } else {
            write(2, cmd, strlen(cmd));
            write(2, ": Command not found.\n", 22);
        }
        return 1;
    }
    printf("%s\n", which_cmd);
    return 0;
}
