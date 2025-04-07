/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redir_herdoc.c
*/

#include "../include/minishel.h"

static int *create_heredoc_pipe(void)
{
    int *pipe_fd = malloc(2 * sizeof(int));

    if (!pipe_fd) {
        perror("Memory allocation for pipe");
        return NULL;
    }
    if (pipe(pipe_fd) == -1) {
        perror("pipe creation");
        free(pipe_fd);
        return NULL;
    }
    return pipe_fd;
}

static int write_line_to_pipe(int pipe_write_fd,
    const char *line, size_t line_length)
{
    if (write(pipe_write_fd, line, line_length) == -1) {
        perror("write line to pipe");
        return -1;
    }
    if (write(pipe_write_fd, "\n", 1) == -1) {
        perror("write newline to pipe");
        return -1;
    }
    return 0;
}

static size_t remove_trailing_newline(char *buffer, size_t *line_length)
{
    if (*line_length > 0 && buffer[*line_length - 1] == '\n') {
        buffer[*line_length - 1] = '\0';
        (*line_length)--;
    }
    return *line_length;
}

static int is_delimiter_line(const char *buffer, const char *delimiter)
{
    return my_strcmp(buffer, delimiter) == 0;
}

static ssize_t read_next_line(char **buffer, size_t *buffer_size)
{
    return getline(buffer, buffer_size, stdin);
}

static int process_single_line(
    char *buffer, size_t line_length,
    const char *delimiter, int pipe_write_fd)
{
    remove_trailing_newline(buffer, &line_length);
    if (is_delimiter_line(buffer, delimiter)) {
        return 1;
    }
    if (write_line_to_pipe(pipe_write_fd, buffer, line_length) != 0) {
        return 1;
    }
    return 0;
}

static int process_heredoc_input(const char *delimiter, int pipe_write_fd)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    int result = 0;
    int line_process_result;

    line_length = read_next_line(&buffer, &buffer_size);
    while (line_length != -1) {
        line_process_result = process_single_line(
            buffer, line_length, delimiter, pipe_write_fd
        );
        if (line_process_result != 0) {
            result = line_process_result == 1 ? 0 : 1;
            break;
        }
        line_length = read_next_line(&buffer, &buffer_size);
    }
    free(buffer);
    return result;
}

static int redirect_stdin_to_pipe(int *pipe_fd)
{
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
        perror("dup2");
        return 1;
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    return 0;
}

int redir_heredoc(char *delimiter)
{
    int *pipe_fd = create_heredoc_pipe();
    int redirect_result;

    if (!pipe_fd) {
        return 1;
    }
    if (process_heredoc_input(delimiter, pipe_fd[1]) != 0) {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        free(pipe_fd);
        return 1;
    }
    redirect_result = redirect_stdin_to_pipe(pipe_fd);
    free(pipe_fd);
    return redirect_result;
}
