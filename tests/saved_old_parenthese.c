/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../include/minishel.h"

static int is_space(char c)
{
    return (c <= ' ');
}

static int is_pipe(char c)
{
    return (c == '|');
}

static int is_redirection(char c)
{
    return (c == '>' || c == '<' || c == '&');
}

static int is_red_or_operator(char *cmd)
{
    char *all_red[] = {"<", "<<", ">", ">>", "&&", "||", NULL};

    for (int i = 0; i < 6; i++) {
        if (my_strcmp(all_red[i], cmd) == 0) {
            return i;
        }
    }
    return -1;
}

static int count_args_for_parentheses(char *input)
{
    int level = 0;
    int count = 0;
    int i = 0;
    int has_prev_char = 0;

    while (input[i] != '\0') {
        if (input[i] == '(')
            level++;
        else if (input[i] == ')')
            level--;
        else if (level == 0 && (input[i] == '|' || input[i] == '>' || input[i] == '<') || input[i] == '&') {
            // Séparateur trouvé à niveau 0
            if (has_prev_char)
                count++;  // Comptez l'argument avant le séparateur
            count++;      // Comptez le séparateur lui-même
            has_prev_char = 0;
            if ((input[i] == '>' && input[i+1] == '>') || 
                (input[i] == '<' && input[i+1] == '<') ||
                (input[i] == '&' && input[i+1] == '&') ||
                (input[i] == '|' && input[i+1] == '|'))
                i++;
        } else if (!is_space(input[i])) {
            has_prev_char = 1;
        }
        i++;
    }
    if (has_prev_char)
        count++;  // Dernier argument
    return count;
}

static char *copy_string_for_parentheses(char *input, int start, int end)
{
    char *result;
    int j = 0;
    
    // Ignorer les espaces au début et à la fin
    while (start < end && is_space(input[start]))
        start++;
    while (end > start && is_space(input[end - 1]))
        end--;
    
    if (start >= end)
        return NULL;
    
    result = malloc(sizeof(char) * (end - start + 1));
    if (!result)
        return NULL;
    
    for (int i = start; i < end; i++)
        result[j++] = input[i];
    result[j] = '\0';
    
    return result;
}

char **string_to_array_for_parentheses(char *input)
{
    int count = count_args_for_parentheses(input);
    char **array = malloc(sizeof(char *) * (count + 1));
    int index = 0;
    int start = 0;
    int level = 0;
    int i = 0;
    
    if (!array)
        return NULL;
    
    while (input[i] != '\0') {
        if (input[i] == '(')
            level++;
        else if (input[i] == ')')
            level--;
        else if (level == 0 && (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '&')) {
            char *arg = copy_string_for_parentheses(input, start, i);
            if (arg != NULL) {
                array[index++] = arg;
            }
            if ((input[i] == '>' && input[i+1] == '>') || 
                (input[i] == '<' && input[i+1] == '<') ||
                (input[i] == '&' && input[i+1] == '&') ||
                (input[i] == '|' && input[i+1] == '|')) {
                array[index] = malloc(3 * sizeof(char));
                array[index][0] = input[i];
                array[index][1] = input[i+1];
                array[index][2] = '\0';
                i++;
            } else {
                array[index] = malloc(2 * sizeof(char));
                array[index][0] = input[i];
                array[index][1] = '\0';
            }
            index++;
            start = i + 1;
        }
        i++;
    }
    
    // Ajouter le dernier argument
    if (start < i) {
        char *arg = copy_string_for_parentheses(input, start, i);
        if (arg != NULL) {
            array[index++] = arg;
        }
    }
    
    array[index] = NULL;
    return array;
}

char *clean_parenthese_argv(char *cmd)
{
    int len;
    char *cleaned_cmd;
    
    // Check if cmd is valid
    if (!cmd)
        return NULL;
    
    len = my_strlen(cmd);
    
    // Check if string is long enough to have parentheses
    if (len < 2)
        return my_strdup(cmd); // Return a copy of the original string
    
    // Check if string starts with '(' and ends with ')'
    if (cmd[0] != '(' || cmd[len - 1] != ')')
        return my_strdup(cmd); // Return a copy if no parentheses to remove
    cleaned_cmd = malloc(sizeof(char) * (len - 1));
    if (!cleaned_cmd)
        return NULL;
    strncpy(cleaned_cmd, cmd + 1, len - 2);
    cleaned_cmd[len - 2] = '\0';
    return cleaned_cmd;
}

static int redir_in(char **all_arg, minishel_t **llenv)
{
    int fd, status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);
    
    fd = open(all_arg[2], O_RDONLY);
    if (fd < 0) {
        perror(all_arg[2]);
        return 1;
    }
    int stdin_save = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    close(fd);
    status = execute_multi_cmd(llenv, cleaned_cmd);
    dup2(stdin_save, STDIN_FILENO);
    close(stdin_save);
    free(cleaned_cmd);
    return status;
}

static int here_doc(char **all_arg, minishel_t **llenv)
{
    int status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);
    
    if (redir_heredoc(all_arg[2]) != 0) {
        free(cleaned_cmd);
        return 1;
    }
    status = execute_multi_cmd(llenv, cleaned_cmd);
    free(cleaned_cmd);
    return status;
}

static int redir_out(char **all_arg, minishel_t **llenv)
{
    int fd, status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);

    fd = open(all_arg[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror(all_arg[2]);
        return 1;
    }
    int stdout_save = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    status = execute_multi_cmd(llenv, cleaned_cmd);
    dup2(stdout_save, STDOUT_FILENO);
    close(stdout_save);
    free(cleaned_cmd);
    return status;
}

static int redir_dout(char **all_arg, minishel_t **llenv)
{
    int fd, status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);

    fd = open(all_arg[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror(all_arg[2]);
        return 1;
    }
    int stdout_save = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    status = execute_multi_cmd(llenv, cleaned_cmd);
    dup2(stdout_save, STDOUT_FILENO);
    close(stdout_save);
    
    free(cleaned_cmd);
    return status;
}

static int and(char **all_arg, minishel_t **llenv)
{
    int status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);
    char *all_arg2 = clean_parenthese_argv(all_arg[2]);

    status = execute_multi_cmd(llenv, cleaned_cmd);
    if (status == 0) {
        status = execute_multi_cmd(llenv, all_arg2);
    }
    free(cleaned_cmd);
    return status;
}

static int or(char **all_arg, minishel_t **llenv)
{
    int status = 0;
    char *cleaned_cmd = clean_parenthese_argv(all_arg[0]);
    char *cleaned_cmd2 = clean_parenthese_argv(all_arg[2]);

    status = execute_multi_cmd(llenv, cleaned_cmd);
    if (status != 0) {
        status = execute_multi_cmd(llenv, cleaned_cmd2);
    }
    free(cleaned_cmd);
    return status;
}

int handle_redirection_in_parenthese(char **all_arg, minishel_t **llenv)
{
    int (*ptr[])(char **, minishel_t **) =
        {redir_in, here_doc, redir_out, redir_dout, and, or, NULL};
    int redir_index = is_red_or_operator(all_arg[1]);

    return ptr[redir_index](all_arg, llenv);
}

int handle_is_redirection_after_pipe(minishel_t **llenv, char **all_arg, int i)
{
    if (all_arg[i + 1] == NULL) {
        return execute_main_cmd(clean_parenthese_argv(all_arg[i]), llenv);
    } else {
        int redir_index = is_red_or_operator(all_arg[i + 1]);
        if (redir_index > 1) {
            return handle_redirection_in_parenthese(all_arg + i, llenv);
        } else {
            printf("Ambiguous input redirect.\n");
        }
    }
    return 0;
}

static void dup_middle_process(pipe_ctx_t *ctx, int i, int *argv_idx)
{
    if (ctx->pid[i] == 0) {
        dup2(ctx->pipefd[ctx->read_pipe][0], STDIN_FILENO);
        dup2(ctx->pipefd[ctx->write_pipe][1], STDOUT_FILENO);
        close(ctx->pipefd[0][0]);
        close(ctx->pipefd[0][1]);
        close(ctx->pipefd[1][0]);
        close(ctx->pipefd[1][1]);
        *argv_idx += 2;
        execute_multi_cmd(ctx->env, clean_parenthese_argv(ctx->argv[*argv_idx]));
        exit(0);
    }
}

static void middle_processes(pipe_ctx_t *ctx)
{
    int argv_idx = 0;

    if (ctx->num_of_pipe <= 1)
        return;
    for (int i = 1; i < ctx->num_of_pipe; i++) {
        ctx->read_pipe = (i - 1) % 2;
        ctx->write_pipe = i % 2;
        if (i > 1) {
            close(ctx->pipefd[ctx->write_pipe][0]);
            close(ctx->pipefd[ctx->write_pipe][1]);
            pipe(ctx->pipefd[ctx->write_pipe]);
        }
        ctx->pid[i] = fork();
        dup_middle_process(ctx, i, &argv_idx);
        close(ctx->pipefd[ctx->read_pipe][0]);
        close(ctx->pipefd[ctx->read_pipe][1]);
        if (i < ctx->num_of_pipe - 1) {
            pipe(ctx->pipefd[ctx->read_pipe]);
        }
    }
}

static void first_process(pipe_ctx_t *ctx)
{
    ctx->pid[0] = fork();
    if (ctx->pid[0] == 0) {
        close(ctx->pipefd[0][0]);
        if (ctx->num_of_pipe > 1) {
            close(ctx->pipefd[1][0]);
            close(ctx->pipefd[1][1]);
        }
        dup2(ctx->pipefd[0][1], STDOUT_FILENO);
        close(ctx->pipefd[0][1]);
        execute_multi_cmd(ctx->env, clean_parenthese_argv(ctx->argv[0]));
        exit(0);
    }
}

static void last_process(pipe_ctx_t *ctx)
{
    int last = ctx->num_of_pipe;
    int last_read_pipe = (last - 1) % 2;

    ctx->pid[last] = fork();
    if (ctx->pid[last] == 0) {
        dup2(ctx->pipefd[last_read_pipe][0], STDIN_FILENO);
        close(ctx->pipefd[0][0]);
        close(ctx->pipefd[0][1]);
        if (ctx->num_of_pipe > 1) {
            close(ctx->pipefd[1][0]);
            close(ctx->pipefd[1][1]);
        }
        handle_is_redirection_after_pipe(ctx->env, ctx->argv, last * 2);
        exit(0);
    }
}

static int wait_processes(int num_of_pipe, pid_t *pid)
{
    int return_value = 0;

    for (int i = 0; i <= num_of_pipe; i++) {
        if (pid[i] != getpid())
            waitpid(pid[i], &return_value, 0);
    }
    return return_value;
}

int handle_pipe_in_parenthese(char **all_arg, minishel_t **llenv, int num_sep)
{
    int pipefd[2][2];
    pid_t pid[num_sep + 1];
    int return_value;
    pipe_ctx_t ctx = {num_sep, pipefd, pid, llenv, all_arg, 0, 0};
    int pipes_needed = (num_sep > 1) ? 2 : num_sep;

    for (int i = 0; i < pipes_needed; i++)
        pipe(pipefd[i]);
    first_process(&ctx);
    middle_processes(&ctx);
    last_process(&ctx);
    for (int i = 0; i < pipes_needed; i++) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }
    return_value = wait_processes(num_sep, pid);
    return return_value;
}

int handle_redirection_parenthese(char **all_arg, minishel_t **llenv, int num_of_sep)
{
    if (is_red_or_operator(all_arg[1]) > -1) {
        return handle_redirection_in_parenthese(all_arg, llenv);
    } else {
        return handle_pipe_in_parenthese(all_arg, llenv, num_of_sep);
    }
}

int search_pipe(char *input)
{
    int level = 0;
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(')
            level++;
        if (input[i] == ')')
            level--;
        if (level == 0 && input[i] == '|') {
            count++;
        }
    }
    return count;
}

static int open_parenthese(char input, int *level,
    int *is_sep, int *is_char_between)
{
    if (input == '(') {
        (*level)++;
        if (*is_sep == 0) {
            *level = -1;
        }
    }
    if (*level > 0) {
        *is_char_between += 1;
    }
}

static int check_parenthes(char input, int *level,
    int *is_char_between, int *is_sep)
{
    open_parenthese(input, level, is_sep, is_char_between);
    if (input == ')') {
        (*level)--;
        if (*is_char_between < 3 && *is_char_between > 0) {
            *level = -1;
        }
        *is_char_between = 0;
        *is_sep = 0;
    }
    if (is_redirection(input) || is_pipe(input)) {
        if (*level == 0) {
            *is_sep = 1;
        }
    }
}

int check_num_of_parenthese(char *input)
{
    int level = 0;
    int is_char_between = 0;
    int is_sep = 1;

    for (int i = 0; input[i] != '\0'; i++) {
        check_parenthes(input[i], &level, &is_char_between, &is_sep);
        if (level < 0) {
            my_putstr("Too many )'s.\n");
            return 1;
        }
    }
    if (level > 0) {
        my_putstr("Too many ('s.\n");
        return 1;
    }
    return 0;
}

int check_error_parenthese(char **all_arg, char *input, int arraylen)
{
    if (check_num_of_parenthese(input) == 1) {
        return 1;
    }
    if (arraylen % 2 == 0) {
        my_putstr("Invalid null command.\n");
        return 1;
    }
    return 0;
}


int handle_parenthese(minishel_t **llenv, char *input)
{
    int num_sep = search_pipe(input);
    char **all_arg = string_to_array_for_parentheses(input);
    int arraylen = len_array(all_arg);

    if (check_error_parenthese(all_arg, input, arraylen) == 1) {
        free_array(all_arg);
        return 1;
    }
    if (len_array(all_arg) == 1) {
        return execute_multi_cmd(llenv, clean_parenthese_argv(all_arg[0]));
    } else {
        return handle_redirection_parenthese(all_arg, llenv, num_sep);
    }
}
