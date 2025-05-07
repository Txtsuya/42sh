/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** alias.c
*/

#include "../../include/minishel.h"

void set_input_mode(struct termios *signal)
{
    struct termios new_signal;

    tcgetattr(STDIN_FILENO, signal);
    new_signal = *signal;
    new_signal.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_signal);
}

static void handle_input(char **input, int *lenght, int *cursor, char c)
{
    char *old_text = my_malloc(sizeof(char) * (*lenght + 2));
    char *previous = *input;

    for (int i = 0; i < *cursor; i++)
        old_text[i] = (*input)[i];
    old_text[*cursor] = c;
    for (int i = *cursor; i < *lenght; i++)
        old_text[i + 1] = (*input)[i];
    old_text[*lenght + 1] = '\0';
    *input = old_text;
    *lenght += 1;
    *cursor += 1;
    my_free(previous);
    get_marked_history()->cursor = *cursor;
}

static void handle_del(int *cursor, char **input, int *lenght)
{
    char *old_text;
    char *previous;
    int k = 0;

    if (*lenght == 0 || *cursor == 0)
        return;
    old_text = my_malloc(sizeof(char) * (*lenght));
    if (!old_text)
        return;
    previous = *input;
    for (int i = 0; i < *lenght; i++) {
        old_text[k] = (*input)[i];
        if (i != *cursor - 1)
            k++;
    }
    old_text[k] = '\0';
    *input = old_text;
    *lenght -= 1;
    *cursor -= 1;
    my_free(previous);
}

static int handle_ctrl_a(int *cursor, int *lenght)
{
    *cursor = 0;
    get_marked_history()->cursor = *cursor;
    return 0;
}

static int handle_ctrl_e(int *cursor, int *lenght)
{
    *cursor = *lenght;
    get_marked_history()->cursor = *cursor;
    return 0;
}

static int handle_backspace(int *cursor, char **input, int *lenght)
{
    handle_del(cursor, input, lenght);
    get_marked_history()->cursor = *cursor;
    return 0;
}

static int is_sp_input(char c, int *cursor, char **input, int *lenght)
{
    if (c == 27) {
        handle_arrow(cursor, lenght, input);
        return 0;
    }
    if (c == 1) {
        return handle_ctrl_a(cursor, lenght);
    }
    if (c == 5) {
        return handle_ctrl_e(cursor, lenght);
    }
    if (c == 127 || c == 8) {
        return handle_backspace(cursor, input, lenght);
    }
    handle_input(input, lenght, cursor, c);
    return 0;
}

static void print_the_input(char **input, int *lenght, int *cursor,
    minishel_t **llenv)
{
    write(1, "\033[2K\r", 5);
    print_prompt(llenv);
    my_putstr(*input);
    write(1, " \b", 2);
    for (int i = 0; i < *lenght - *cursor; i++) {
        write(1, "\b", 1);
    }
}

int loop(char **input, minishel_t **llenv)
{
    int lenght = 0;
    int cursor = 0;
    char c;
    int returning = 0;

    *input = my_malloc(sizeof(char) * 1);
    (*input)[0] = '\0';
    while (1) {
        returning = read(STDIN_FILENO, &c, 1);
        if (c == 4)
            return -1;
        if (c == '\n')
            break;
        if (is_sp_input(c, &cursor, input, &lenght))
            continue;
        print_the_input(input, &lenght, &cursor, llenv);
    }
    return 0;
}

int my_getline(char **input, minishel_t **llenv)
{
    struct termios signal;
    int return_value = 0;
    size_t len = 0;

    if (!isatty(STDIN_FILENO))
        return getline(input, &len, stdin);
    set_input_mode(&signal);
    return_value = loop(input, llenv);
    tcsetattr(STDIN_FILENO, TCSANOW, &signal);
    write(STDOUT_FILENO, "\n", 1);
    return return_value;
}
