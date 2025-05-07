/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_arrow.c
*/

#include "minishel.h"

marked_hisory_t *get_marked_history(void)
{
    static marked_hisory_t *mh = NULL;

    if (mh == NULL) {
        mh = my_malloc(sizeof(marked_hisory_t));
        mh->marked = NULL;
        mh->type = 0;
        mh->cursor = 0;
    }
    return mh;
}

void clean_marked(int type)
{
    marked_hisory_t *mh = get_marked_history();

    mh->marked = NULL;
    mh->type = type;
    mh->cursor = 0;
}

history_t *get_last_history(char *line, int sens, int is_first)
{
    marked_hisory_t *mark = get_marked_history();
    history_t *current = mark->marked;

    if (current == NULL)
        return NULL;
    if (!is_first)
        current = sens ? current->next : current->prev;
    while (current) {
        if (strncmp(current->cmd, line, mark->cursor) == 0) {
            return current;
        }
        current = sens ? current->next : current->prev;
    }
    return NULL;
}

static void handle_down_arrow_type_1(int *cursor, int *lenght,
    char **input, marked_hisory_t *marked)
{
    if (marked->marked->prev == NULL) {
        *input = my_strdup("");
        *lenght = 0;
        *cursor = 0;
        clean_marked(1);
        return;
    }
    marked->marked = marked->marked->prev;
    my_free(*input);
    *input = my_strdup(marked->marked->cmd);
    *lenght = my_strlen(*input);
    *cursor = *lenght;
}

static void handle_down_arrow_type_2(int *cursor, int *lenght, char **input,
    marked_hisory_t *marked)
{
    history_t *tmp = get_last_history(*input, 0, 0);

    if (tmp != NULL) {
        marked->marked = tmp;
        my_free(*input);
        *input = my_strdup(marked->marked->cmd);
        *lenght = my_strlen(*input);
        *cursor = *lenght;
    }
}

void handle_down_arrow(int *cursor, int *lenght, char **input)
{
    marked_hisory_t *marked = get_marked_history();

    if (marked->marked == NULL)
        return;
    if (marked->type == 1)
        handle_down_arrow_type_1(cursor, lenght, input, marked);
    if (marked->type == 2)
        handle_down_arrow_type_2(cursor, lenght, input, marked);
}

static void handle_left_right_arrow(int *cursor, int *lenght, char d)
{
    if (d == 67 && *cursor != *lenght) {
        *cursor += 1;
        get_marked_history()->type = 2;
        get_marked_history()->cursor = *cursor;
    }
    if (d == 68 && *cursor != 0) {
        *cursor -= 1;
        if (*cursor == 0)
            get_marked_history()->type = 1;
        else
            get_marked_history()->type = 2;
        get_marked_history()->cursor = *cursor;
    }
}

void handle_arrow(int *cursor, int *lenght, char **input)
{
    char c;
    char d;

    read(STDIN_FILENO, &c, 1);
    read(STDIN_FILENO, &d, 1);
    if (c != 91)
        return;
    if (d == 65) {
        handle_up_arrow(cursor, lenght, input);
        return;
    }
    if (d == 66) {
        handle_down_arrow(cursor, lenght, input);
        return;
    }
    handle_left_right_arrow(cursor, lenght, d);
}
