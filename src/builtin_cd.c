/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** builtin_cd.c
*/

#include "../include/minishel.h"

void update_cd_env(char *current, minishel_t **llenv)
{
    char new_pwd[PATH_MAX];

    if (getcwd(new_pwd, PATH_MAX) != NULL) {
        add_llist_env(current, llenv, "OLDPWD");
        add_llist_env(new_pwd, llenv, "PWD");
    }
}

void cd_error(char *path)
{
    if (path == NULL)
        my_putstr("cd: ");
    else {
        my_putstr("");
        my_putstr(path);
        my_putstr(": ");
    }
    my_putstr(strerror(errno));
    my_putstr(".\n");
}

int builtin_cd(char **args, minishel_t **llenv)
{
    char current_path[PATH_MAX];
    char *new_pwd;
    minishel_t *cwdcmd_value;

    getcwd(current_path, PATH_MAX);
    if (args[1] != NULL)
        new_pwd = args[1];
    if (args[1] != NULL && my_strcmp(args[1], "-") == 0)
        new_pwd = my_getenv(*llenv, "OLDPWD");
    if (args[1] == NULL)
        new_pwd = my_getenv(*llenv, "HOME");
    if (chdir(new_pwd) != 0) {
        cd_error(new_pwd);
        return 1;
    }
    update_cd_env(current_path, llenv);
    cwdcmd_value = (minishel_t *)get_special_variable("cwdcmd");
    if (cwdcmd_value && cwdcmd_value->value && isatty(STDIN_FILENO))
        execute_multi_cmd(llenv, cwdcmd_value->value);
    return 1;
}
