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

alias_ll_t **get_ll_alias(void)
{
    static alias_ll_t *head = NULL;

    return &head;
}

void free_alias(alias_ll_t *current)
{
    for (int i = 0; current->value[i] != NULL; i++)
        my_free(current->value[i]);
    my_free(current->value);
    my_free(current->name);
    my_free(current);
}

static void delete_ll_alias(char *name)
{
    alias_ll_t **head = get_ll_alias();
    alias_ll_t *current = *head;
    alias_ll_t *previous = NULL;

    if (*head == NULL)
        return;
    if (strcmp(current->name, name) == 0) {
        *head = current->next;
        free_alias(current);
        return;
    }
    while (current != NULL && strcmp(current->name, name) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    previous->next = current->next;
    free_alias(current);
}

char **get_value_alias(char *name)
{
    alias_ll_t **head = get_ll_alias();
    alias_ll_t *current = *head;

    if (!name)
        return NULL;
    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void check_alias(char ***args)
{
    char **value = get_value_alias(*args[0]);
    char **new;
    int len;
    int i = 0;

    if (!value || !value[0])
        return;
    len = len_array(value) + len_array(*args) - 1;
    new = my_malloc(sizeof(char *) * (len + 1));
    for (i = 0; value[i]; i++)
        new[i] = my_strdup(value[i]);
    for (int j = 1; (*args)[j]; j++) {
        new[i] = my_strdup((*args)[j]);
        i++;
    }
    new[i] = NULL;
    free_array(*args);
    *args = new;
    check_alias(args);
}

int handle_unalias(char **args, minishel_t **llenv)
{
    int len = len_array(args);

    if (len < 2 || len > 2)
        return 1;
    delete_ll_alias(args[1]);
    return 1;
}
