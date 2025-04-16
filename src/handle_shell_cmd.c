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
    if (check_is_builtin(cmd) == 1)
        printf("%s: shell built-in command.\n", cmd);
    else {
        which_cmd = build_path_cmd(cmd, llenv);
        if (which_cmd)
            printf("%s\n", which_cmd);
        else
            printf("%s: Command not found.\n", cmd);
    }
    return 0;
}

static int is_two_dote(char c)
{
    return (c != ':');
}

static char *base_path(char *cmd)
{
    const char *path = "/bin/";
    char *path_cmd = my_malloc(my_strlen(path) + my_strlen(cmd));

    my_strcpy(path_cmd, path);
    my_strcat(path_cmd, cmd);
    return path_cmd;
}

int handle_where(char *cmd, minishel_t **llenv)
{
    char *path;
    char **path_env;
    char *concat_path;
    int i = 0;

    while (*cmd != ' ' && *cmd != '\0')
        cmd++;
    while (*cmd == ' ')
        cmd++;
    path = my_getenv(*llenv, "PATH");
    if (path == NULL)
        return base_path(cmd);
    path_env = my_str_to_word_array(path, is_two_dote);
    while (path_env[i] != NULL) {
        concat_path = my_malloc(my_strlen(path_env[i]) + my_strlen(path) + 1);
        my_strcpy(concat_path, path_env[i]);
        my_strcat(concat_path, "/");
        my_strcat(concat_path, cmd);
        if (access(concat_path, X_OK) == 0) {
            printf("%s\n", concat_path);
        }
        my_free(concat_path);
        i++;
    }
    return 0;
}
