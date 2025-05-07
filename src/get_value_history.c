/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** get_value_history.c
*/

#include "../include/minishel.h"

static void recur_print_history(history_t *current)
{
    int i = 0;

    if (current == NULL)
        return;
    recur_print_history(current->next);
    my_put_nbr(current->idx);
    my_putstr("\t");
    my_putstr(current->hour);
    my_putstr("\t");
    my_putstr(current->cmd);
    my_putstr("\n");
}

int print_history(char **args, minishel_t **llenv)
{
    history_t **head = get_history();
    history_t *current = *head;

    recur_print_history(current);
    return 1;
}

char *history_pos(history_t *current, int n, int *cpt)
{
    char *tab = NULL;

    if (current == NULL)
        return NULL;
    tab = history_pos(current->next, n, cpt);
    (*cpt)++;
    if (*cpt == n)
        return my_strdup(current->cmd);
    return tab;
}

char *history_neg(history_t *current, int n)
{
    int cpt = 0;

    while (current && cpt < n) {
        current = current->next;
        cpt++;
    }
    if (cpt == n && current != NULL)
        return my_strdup(current->cmd);
    return NULL;
}

char *history_cmp(history_t *current, char *line, int len)
{
    if (current == NULL)
        return NULL;
    while (current) {
        if (strncmp(current->cmd, line, len) == 0)
            return my_strdup(current->cmd);
        current = current->next;
    }
    return NULL;
}

char *get_value_in_history(char *line, int len)
{
    history_t **head = get_history();
    history_t *current = *head;
    int nbr = my_getnbr(line);
    int cpt = 0;

    if (len == 0)
        return NULL;
    if (line[0] == '!')
        return history_neg(current, 0);
    if (nbr > 0)
        return history_pos(current, nbr, &cpt);
    if (nbr < 0)
        return history_neg(current, (nbr * -1) - 1);
    return history_cmp(current, line, len);
}
