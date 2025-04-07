/*
** EPITECH PROJECT, 2025
** utils
** File description:
** utils
*/

#include "../include/minishel.h"

void get_input(char **input, int ret_status, minishel_t **llenv)
{
    size_t len = 0;

    if (isatty(STDIN_FILENO)) {
        my_putstr(my_getenv(*llenv, "PWD"));
        my_putstr(" > ");
    }
    if (getline(input, &len, stdin) == -1) {
        exit(ret_status);
    }
    if ((*input)[0] != '\0' && (*input)[my_strlen(*input) - 1] == '\n') {
        (*input)[my_strlen(*input) - 1] = '\0';
    }
}

void initialize_shell(char **env, minishel_t **llenv)
{
    *llenv = NULL;
    env_array_to_env_ll(env, llenv);
}

static int error_command_not_found(char *path_cmd, char *args)
{
    if (path_cmd == NULL) {
        my_putstr(args);
        my_putstr(": Command not found.\n");
        write(2, args, my_strlen(args));
        write(2, ": Command not found.\n", 21);
        exit(1);
    }
}

static int execve_error(char *command)
{
    if (errno == ENOENT) {
        my_putstr(command);
        my_putstr(": Permission denied.\n");
        return 1;
    } else if (errno == EACCES) {
        my_putstr(command);
        my_putstr(": Permission denied.\n");
        return 1;
    } else {
        my_putstr(command);
        my_putstr(": Exec format error. Binary file not executable.\n");
        return 1;
    }
}

static int handle_child_process(char *path_cmd, char **args, char **env_array)
{
    error_command_not_found(path_cmd, args[0]);
    if (execve(path_cmd, args, env_array) == -1)
        exit(execve_error(args[0]));
    return 0;
}

static int handle_parent_process(char *path_cmd, char **args,
    pid_t child_pid, char **env_array)
{
    int status;

    waitpid(child_pid, &status, 0);
    free(path_cmd);
    free_array(env_array);
    free_array(args);
    return seg_exit(status);
}

int execute_command(char *path_cmd, char **args, minishel_t **llenv)
{
    pid_t pid;
    char **env_array;

    env_array = ll_to_array_env(*llenv);
    pid = fork();
    if (pid < 0) {
        perror("Erreur de fork");
        exit(1);
    }
    if (pid == 0) {
        return handle_child_process(path_cmd, args, env_array);
    } else {
        return handle_parent_process(path_cmd, args, pid, env_array);
    }
}

char *get_path_cmd(char *args, minishel_t **llenv)
{
    char *path_cmd;

    if (access(args, X_OK) != 0)
        path_cmd = build_path_cmd(args, llenv);
    else
        path_cmd = my_strdup(args);
    return path_cmd;
}

int main_loop(minishel_t **llenv, char **env)
{
    char *input = NULL;
    int status = 0;

    while (1) {
        get_input(&input, status, llenv);
        status = execute_multi_cmd(llenv, input);
    }
    return status;
}
