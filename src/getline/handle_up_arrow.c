/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_up_arrow.c
*/

#include "minishel.h"

static int init_marked_type_1(int *cursor, int *len,
    char **input, marked_hisory_t *marked)
{
    my_free(*input);
    *input = my_strdup(marked->marked->cmd);
    *len = my_strlen(*input);
    *cursor = *len;
    return 1;
}

static int init_marked_type_2(int *cursor, int *len,
    char **input, marked_hisory_t *marked)
{
    history_t *tmp = get_last_history(*input, 1, 1);

    if (tmp != NULL) {
        marked->marked = tmp;
        my_free(*input);
        *input = my_strdup(marked->marked->cmd);
        *len = my_strlen(*input);
        *cursor = *len;
    }
    return 1;
}

int init_marked(int *cursor, int *len, char **input, marked_hisory_t *marked)
{
    history_t **h = get_history();

    if (h == NULL)
        return 1;
    marked->cursor = *cursor;
    marked->marked = *h;
    marked->type = *cursor == 0 ? 1 : 2;
    if (marked->type == 1)
        return init_marked_type_1(cursor, len, input, marked);
    if (marked->type == 2)
        return init_marked_type_2(cursor, len, input, marked);
    return 0;
}

void handle_up_arrow_type_1(int *cursor,
    int *lenght, char **input, marked_hisory_t *marked)
{
    if (marked->marked->next != NULL)
        marked->marked = marked->marked->next;
    my_free(*input);
    *input = my_strdup(marked->marked->cmd);
    *lenght = my_strlen(*input);
    *cursor = *lenght;
}

void handle_up_arrow_type_2(int *cursor, int *lenght,
    char **input, marked_hisory_t *marked)
{
    history_t *tmp = get_last_history(*input, 1, 0);

    if (tmp != NULL) {
        marked->marked = tmp;
        my_free(*input);
        *input = my_strdup(marked->marked->cmd);
        *lenght = my_strlen(*input);
        *cursor = *lenght;
    }
}

void handle_up_arrow(int *cursor, int *lenght, char **input)
{
    marked_hisory_t *marked = get_marked_history();

    if (marked->marked == NULL)
        if (init_marked(cursor, lenght, input, marked))
            return;
    if (marked->marked == NULL)
        return;
    if (marked->type == 1)
        handle_up_arrow_type_1(cursor, lenght, input, marked);
    if (marked->type == 2)
        handle_up_arrow_type_2(cursor, lenght, input, marked);
}
