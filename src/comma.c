/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** comma.c
*/

#include "../include/minishel.h"

static char *process_expvar_backticks(char *cmd, minishel_t **llenv)
{
    handle_back_ticks(&cmd, llenv);
    cmd = expand_variables(cmd, llenv);
    return cmd;
}

static int is_space(char c)
{
    return (c != ' ' && c != '\t' && c != '\n');
}

int reset_redirection(int value_ret, int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    return value_ret;
}

int execute_main_cmd(char *cmd, minishel_t **llenv)
{
    char *path_cmd;
    char **args;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    int ret;

    cmd = process_expvar_backticks(cmd, llenv);
    args = my_str_to_word_array(cmd, is_space);
    check_alias(&args);
    args = globbing(args);
    if (args == NULL)
        return 1;
    if (handle_builtin_cmd(&args, cmd, llenv) == 1)
        return reset_redirection(0, saved_stdin, saved_stdout);
    if (parse_redirections(args) != 0)
        return reset_redirection(1, saved_stdin, saved_stdout);
    args = remove_redirections(args);
    path_cmd = get_path_cmd(args[0], llenv);
    ret = execute_command(path_cmd, args, llenv);
    return reset_redirection(ret, saved_stdin, saved_stdout);
}

int nbr_instr(char *str, char c)
{
    level_ini_t level = {0};
    int cpt = 0;

    for (int i = 0; str[i]; i++) {
        update_level(&level, str, i);
        if (str[i] == c && is_level_0(&level))
            cpt++;
    }
    return cpt > 0 ? cpt + 1 : 0;
}

int executepipe(char *token, minishel_t **llenv)
{
    int nbr_pipe = nbr_instr(token, '|');

    if (test_valid_pipe(token))
        return 0;
    return execute_pipeline(token, nbr_pipe, llenv);
}
