/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include "../include/minishel.h"

static int is_space(char c)
{
    return (c != ' ' && c != '\t');
}

void add_llist_env(char *pwd, minishel_t **llenv, const char *name)
{
    add_llist(llenv, name, pwd);
}

static void update_cd_env(char *current, minishel_t **llenv)
{
    char new_pwd[PATH_MAX];

    if (getcwd(new_pwd, PATH_MAX) != NULL) {
        add_llist_env(current, llenv, "OLDPWD");
        add_llist_env(new_pwd, llenv, "PWD");
    }
}

static void cd_error(char *path)
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

static int builtin_cd(char **args, minishel_t **llenv)
{
    char current_path[PATH_MAX];
    char *new_pwd;

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
    return 1;
}

int my_setenv(char **args, minishel_t **llenv)
{
    int len = len_array(args);

    if (len > 3) {
        perror("setenv");
        return 1;
    }
    if (len == 1) {
        print_env(*llenv);
        return 1;
    }
    if (check_right_argv(args[1]) == 1)
        return 1;
    if (len == 2) {
        add_llist(llenv, args[1], NULL);
        return 1;
    } else {
        add_llist(llenv, args[1], args[2]);
        return 1;
    }
}

int handle_env_commands(char **args, minishel_t **llenv)
{
    if (my_strcmp(args[0], "env") == 0
        || my_strcmp(args[0], "/usr/bin/env") == 0) {
        print_env(*llenv);
        return 1;
    }
    if (my_strcmp(args[0], "setenv") == 0) {
        my_setenv(args, llenv);
        return 1;
    }
    if (my_strcmp(args[0], "unsetenv") == 0) {
        delete_llist(llenv, args[1]);
        return 1;
    }
    return 0;
}

void print_env(minishel_t *head)
{
    if (head == NULL)
        return;
    while (head != NULL) {
        my_putstr(head->name);
        my_putstr("=");
        if (head->value != NULL)
            my_putstr(head->value);
        my_putstr("\n");
        head = head->next;
    }
}

int handle_builtin_cmd(char ***arguments,
    char *input, minishel_t **llenv)
{
    if (my_strcmp(input, "") == 0)
        return 1;
    if (handle_env_commands(*arguments, llenv))
        return 1;
    if (my_strcmp(*arguments[0], "exit") == 0)
        exit(0);
    if (my_strcmp(*arguments[0], "cd") == 0)
        return builtin_cd(*arguments, llenv);
    return 0;
}
