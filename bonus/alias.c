/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../include/minishel.h"

static int backslash_cut(char c)
{
    return (c != '\n');
}

char *get_buffer(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char *buff;
    struct stat s;
    int size_stat;
    int size;

    if (stat(filepath, &s) || fd == -1)
        return NULL;
    size_stat = s.st_size;
    buff = my_malloc(sizeof(char) * size_stat + 1);
    size = read(fd, buff, size_stat);
    buff[size] = '\0';
    close(fd);
    return buff;
}

void init_ll_alias(void)
{
    char *buffer = get_buffer("bonus/.42shrc");
    char **line = my_str_to_word_array(buffer, backslash_cut);

    while (*line) {
        if (my_strncmp(*line, "alias", strlen("alias")) == 0)
            add_alias(*line);
        if (my_strncmp(*line, "color", my_strlen("color")) == 0)
            init_color(*line);
        *line++;
    }
    my_free(buffer);
}