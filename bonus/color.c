/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** color.c
*/

#include "../include/minishel.h"

static int space_cut(char c)
{
    return (c != ' ');
}

color_t **get_index(void)
{
    static color_t *color = NULL;

    return &color;
}

void print_char_color(char c, int i)
{
    const char *colors[] = {"\033[0;30m",
        "\033[0;31m", "\033[0;32m", "\033[0;33m",
        "\033[0;34m", "\033[0;35m", "\033[0;36m", "\033[0;37m",
        "\033[1;30m", "\033[1;31m", "\033[1;32m", "\033[1;33m",
        "\033[1;34m", "\033[1;35m", "\033[1;36m", "\033[1;37m", NULL};

    if (i == -1)
        i = 6;
    my_putstr(colors[i]);
    my_putchar(c);
    my_putstr(RESET);
}

void print_prompt(minishel_t **llenv)
{
    char *path = my_getenv(*llenv, "PWD");
    color_t *color = *get_index();
    int len = color->len;
    int j = -1;

    for (int i = 0; path[i]; i++) {
        if (path[i] == '/') {
            j++;
            print_char_color('-', color->index[j % len]);
            print_char_color('>', color->index[j % len]);
            continue;
        }
        print_char_color(path[i], color->index[j % len]);
    }
    j++;
    print_char_color(' ', color->index[j % len]);
    print_char_color('$', color->index[j % len]);
    print_char_color('>', color->index[j % len]);
    print_char_color(' ', color->index[j % len]);
}

int get_index_color(char *color)
{
    const char *color_names[] = {"BLACK", "RED",
        "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE",
        "BRIGHT_BLACK", "BRIGHT_RED", "BRIGHT_GREEN", "BRIGHT_YELLOW",
        "BRIGHT_BLUE", "BRIGHT_MAGENTA", "BRIGHT_CYAN", "BRIGHT_WHITE",
        NULL};

    for (int i = 0; color_names[i]; i++) {
        if (my_strcmp(color, color_names[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void init_color(char *line)
{
    color_t **color = get_index();
    char *list = extract_between_c(line, '"');
    char **array = my_str_to_word_array(list, space_cut);

    my_free(list);
    *color = my_malloc(sizeof(color_t));
    (*color)->len = len_array(array);
    (*color)->index = my_malloc(sizeof(int) * ((*color)->len + 1));
    for (int i = 0; i < (*color)->len; i++)
        (*color)->index[i] = get_index_color(array[i]);
    (*color)->index[(*color)->len] = -1;
    free_array(array);
}

int handle_color(char **list, minishel_t **llenv)
{
    int nbr;
    int len = len_array(list);
    color_t **color = get_index();
    int index;

    if (len < 3)
        return 1;
    nbr = my_getnbr(list[1]);
    if ((nbr == 0 && list[1][0] != '0') || (*color)->len < nbr) {
        my_putstr(list[1]);
        my_putstr(": not find index color\n");
        return 1;
    }
    index = get_index_color(list[2]);
    if (index == -1) {
        my_putstr(list[2]);
        my_putstr(": color not fund\n");
        return 1;
    }
    (*color)->index[nbr] = index;
    return 1;
}