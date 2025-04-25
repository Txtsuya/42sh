/*
** EPITECH PROJECT, 2025
** utils
** File description:
** utils
*/

#include "../include/minishel.h"

static int check_valide_output(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\"') {
            return 0;
        }
    }
    return 1;
}

int get_input(char **input, int ret_status, minishel_t **llenv)
{
    size_t len = 0;

    free(*input);
    *input == NULL;
    if (my_getline(input, my_getenv(*llenv, "PWD")) == -1) {
        exit(ret_status);
    }
    if ((*input)[0] != '\0' && (*input)[my_strlen(*input) - 1] == '\n') {
        (*input)[my_strlen(*input) - 1] = '\0';
    }
    if (check_valide_output(*input))
        return 1;
    *input = clean_str(*input);
    if (handle_exclamation(input))
        printf("%s\n", *input);
    add_history(*input);
    return 0;
}

void initialize_shell(char **env, minishel_t **llenv)
{
    *llenv = NULL;
    env_array_to_env_ll(env, llenv);
}

void safely_print_jobs_done(void)
{
    struct sigaction sa_ttou;
    struct sigaction old_sa_ttou;

    sa_ttou.sa_handler = SIG_IGN;
    sigemptyset(&sa_ttou.sa_mask);
    sa_ttou.sa_flags = 0;
    sigaction(SIGTTOU, &sa_ttou, &old_sa_ttou);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    print_jobs_done();
    sigaction(SIGTTOU, &old_sa_ttou, NULL);
}

int main_loop(minishel_t **llenv)
{
    char *input = NULL;
    int status = 0;

    while (1) {
        update_jobs_status();
        safely_print_jobs_done();
        if (get_input(&input, status, llenv))
            continue;
        status = execute_multi_cmd(llenv, input);
    }
    free(input);
    free_all();
    return status;
}
