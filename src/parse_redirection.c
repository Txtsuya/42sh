/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** parse_redirection.c
*/

#include "../include/minishel.h"

static int redir_out(char *name)
{
    int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open");
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

static int redir_append(char *name)
{
    int fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd < 0) {
        perror("open");
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

static int redir_in(char *name)
{
    int fd = open(name, O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}

static int is_redirection_token(char *arg)
{
    char *tab[] = {">", ">>", "<", "<<", NULL};

    for (int j = 0; tab[j] != NULL; j++) {
        if (my_strcmp(arg, tab[j]) == 0)
            return 1;
    }
    return 0;
}

int count_valid_args(char **args)
{
    int count = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (is_redirection_token(args[i]) && args[i + 1] != NULL) {
            i++;
            continue;
        }
        count++;
    }
    return count;
}

void fill_filtered_args(char **args, char **new_args)
{
    int new_index = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (is_redirection_token(args[i]) && args[i + 1] != NULL) {
            i++;
            continue;
        }
        new_args[new_index] = args[i];
        new_index++;
    }
    new_args[new_index] = NULL;
}

char **remove_redirections(char **args)
{
    int valid_count = count_valid_args(args);
    char **new_args = malloc((valid_count + 1) * sizeof(char *));

    if (!new_args)
        return NULL;
    fill_filtered_args(args, new_args);
    return new_args;
}

int handle_redirection(char **args, int index)
{
    const char *redirection_tokens[] = {">", ">>", "<", "<<", NULL};
    int (*redir_func[])(char *) = {redir_out,
        redir_append, redir_in, redir_heredoc};
    int token_index = get_redirection_index(args[index]);

    if (token_index == -1)
        return 0;
    return redir_func[token_index](args[index + 1]);
}

int parse_redirections(char **args)
{
    int token_index;

    for (int i = 0; args[i] != NULL; i++) {
        token_index = is_redirection_token(args[i]);
        if (token_index == -1)
            continue;
        if (handle_redirection(args, i) != 0)
            return 1;
    }
    return 0;
}
