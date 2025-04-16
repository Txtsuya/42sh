/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCE-2-1-42sh-simon.puccio
** File description:
** handle_shell_cmd
*/

#include "../include/minishel.h"
#include "minishel.h"

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

int is_two_dote(char c)
{
    return (c != ':');
}

static void my_concat_path(char *concat_path, char **path_env, int i, char *cmd)
{
    my_strcpy(concat_path, path_env[i]);
    my_strcat(concat_path, "/");
    my_strcat(concat_path, cmd);
}

static void print_command_paths(char **path_env, char *cmd)
{
    char *concat_path;
    int i = 0;

    while (path_env[i] != NULL) {
        concat_path = my_malloc(my_strlen(path_env[i]) + my_strlen(cmd) + 2);
        my_concat_path(concat_path, path_env, i, cmd);
        if (access(concat_path, X_OK) == 0)
            printf("%s\n", concat_path);
        my_free(concat_path);
        i++;
    }
}

int handle_where(char **args, minishel_t **llenv)
{
    char *path;
    char **path_env;
    char *concat_path;
    int i = 0;
    int len_args = len_array(args);

    path = my_getenv(*llenv, "PATH");
    if (path == NULL)
        path = "/bin";
    path_env = my_str_to_word_array(path, is_two_dote);
    if (len_args == 1) {
        fprintf(stderr, "where: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args[i]; i++)
        print_command_paths(path_env, args[i]);
    return 1;
}
