/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** history.c
*/

#include "../include/minishel.h"

history_t **get_history(void)
{
    static history_t *htr = NULL;

    return &htr;
}

char *get_time(void)
{
    time_t temps_actuel = time(NULL);
    struct tm *temps_info = localtime(&temps_actuel);
    char *heure = my_malloc(sizeof(char) * 6);

    strftime(heure, sizeof(heure), "%H:%M", temps_info);
    return heure;
}

void add_history(char *args)
{
    history_t *new = my_malloc(sizeof(history_t));
    history_t **head = get_history();
    static int idx = 1;

    new->cmd = my_strdup(args);
    new->idx = idx;
    new->hour = get_time();
    idx++;
    new->next = *head;
    new->prev = NULL;
    if (*head != NULL)
        (*head)->prev = new;
    *head = new;
}

char *replace_in_array(char *dest, char *src, int idx_start, int len_last)
{
    int len_dest = strlen(dest);
    int len_src = strlen(src);
    char *new = my_malloc(sizeof(char) * (len_dest - len_last + len_src + 1));
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; dest[i] != '\0' && i < idx_start; i++)
        new[i] = dest[i];
    for (j = 0; src[j] != '\0'; j++)
        new[i + j] = src[j];
    for (k = idx_start + len_last; dest[k] != '\0'; k++) {
        new[j + i] = dest[k];
        i++;
    }
    new[j + i] = '\0';
    return new;
}

static char *get_remplace(char **args, int i)
{
    int len1 = 0;
    int idx = 0;
    char *val = NULL;

    if ((*args)[i] == '!') {
        len1 = get_len_exclamation(&(*args)[i + 1]);
        idx = i;
        val = get_value_in_history(&(*args)[i + 1], len1 - 1);
        if (val != NULL && len1 != 0)
            return replace_in_array(*args, val, idx, len1);
    }
    return NULL;
}

int handle_exclamation(char **args)
{
    char *dest = NULL;

    for (int i = 0; (*args)[i] != '\0'; i++) {
        dest = get_remplace(args, i);
        if (dest != NULL)
            break;
    }
    if (dest != NULL) {
        *args = dest;
        handle_exclamation(args);
        return 1;
    }
    return 0;
}
