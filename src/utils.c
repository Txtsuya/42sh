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
        exit(1);
    }
    return 0;
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

static void setup_terminal_for_child(pid_t child_pid, struct sigaction *old_sa_ttou)
{
    struct sigaction sa_ttou;
    sa_ttou.sa_handler = SIG_IGN;
    sigemptyset(&sa_ttou.sa_mask);
    sa_ttou.sa_flags = 0;
    sigaction(SIGTTOU, &sa_ttou, old_sa_ttou);
    tcsetpgrp(STDIN_FILENO, child_pid);
}

static void restore_terminal(struct sigaction *old_sa_ttou)
{
    tcsetpgrp(STDIN_FILENO, getpgrp());
    sigaction(SIGTTOU, old_sa_ttou, NULL);
}

static void handle_job_status_after_wait(pid_t child_pid, int status, job_t *added_jobs, char *path_cmd, char **env_array, char **args)
{
    job_t *job = NULL;
    my_free(path_cmd);
    free_array(env_array);
    free_array(args);
    if (WIFSTOPPED(status)) {
        kill(-child_pid, SIGSTOP);
        job = find_job_by_pid(child_pid);
        printf("[%d]+  Stopped\t%s\n", job->id, job->command);
        job->state = JOB_STOPPED;
    } else {
        remove_job(added_jobs->id);
    }
}

static int handle_parent_process(char *path_cmd, char **args,
    pid_t child_pid, char **env_array)
{
    int status;
    struct sigaction old_sa_ttou;
    job_t *added_jobs = NULL;

    setpgid(child_pid, child_pid);
    added_jobs = add_job(child_pid, args[0]);
    setup_terminal_for_child(child_pid, &old_sa_ttou);
    waitpid(child_pid, &status, WUNTRACED);
    restore_terminal(&old_sa_ttou);
    handle_job_status_after_wait(child_pid, status, added_jobs, path_cmd, env_array, args);
    return seg_exit(status);
}

static void restore_signal(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}

int execute_command(char *path_cmd, char **args, minishel_t **llenv)
{
    pid_t pid;
    char **env_array;
    int shell = getpid();

    env_array = ll_to_array_env(*llenv);
    pid = fork();
    if (pid < 0) {
        perror("Erreur de fork");
        exit(1);
    }
    if (pid == 0) {
        restore_signal();
        setpgid(0, 0);
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

void safely_print_jobs_done(void)
{
    // Block SIGTTOU while manipulating terminal
    struct sigaction sa_ttou, old_sa_ttou;
    sa_ttou.sa_handler = SIG_IGN;
    sigemptyset(&sa_ttou.sa_mask);
    sa_ttou.sa_flags = 0;
    sigaction(SIGTTOU, &sa_ttou, &old_sa_ttou);
    
    // Ensure we own the terminal
    tcsetpgrp(STDIN_FILENO, getpgrp());
    
    // Now it's safe to print
    print_jobs_done();
    
    // Restore signal handler
    sigaction(SIGTTOU, &old_sa_ttou, NULL);
}

int main_loop(minishel_t **llenv)
{
    char *input = NULL;
    int status = 0;

    while (1) {
        update_jobs_status();
        safely_print_jobs_done();
        get_input(&input, status, llenv);
        status = execute_multi_cmd(llenv, input);
    }
    free(input);
    free_all();
    return status;
}
