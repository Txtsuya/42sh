/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_alias.c
*/

#include "../include/minishel.h"

static int space_cut(char c)
{
    return (c != ' ');
}

static void add_ll_alias(char *name, char **value)
{
    alias_ll_t **head = get_ll_alias();
    alias_ll_t *new = my_malloc(sizeof(alias_ll_t));

    if (!new)
        return;
    new->name = name;
    new->value = value;
    new->next = *head;
    *head = new;
}

char **my_array_dup(char **array)
{
    char **new_array;
    int i = 0;
    int len = 0;

    if (!array)
        return NULL;
    while (array[len])
        len++;
    new_array = my_malloc(sizeof(char *) * (len + 1));
    if (!new_array)
        return NULL;
    for (i = 0; i < len; i++) {
        new_array[i] = my_strdup(array[i]);
    }
    new_array[i] = NULL;
    return new_array;
}

int print_alias(void)
{
    alias_ll_t **head = get_ll_alias();
    alias_ll_t *current = *head;
    int i = 0;

    while (current) {
        my_putstr(current->name);
        my_putstr("=");
        for (i = 0; current->value[i + 1] != NULL; i++) {
            my_putstr(current->value[i]);
            my_putstr(" ");
        }
        my_putstr(current->value[i]);
        my_putstr("\n");
        current = current->next;
    }
    return 1;
}

void add_alias(char *line)
{
    char *alias = extract_between_quotes(line);
    char **value;
    int len_name;
    char *name;
    char *tmp;

    if (!alias)
        return;
    len_name = my_strlen_c(alias, '=');
    name = my_malloc(sizeof(char) * (len_name + 1));
    my_strncpy(name, alias, len_name);
    tmp = my_strchr(alias, '=');
    if (tmp == NULL)
        return;
    value = my_str_to_word_array(tmp + 1, space_cut);
    add_ll_alias(name, value);
}

int handle_alias(char **args, minishel_t **llenv)
{
    int len = len_array(args);
    char *name;
    char **value;

    if (len == 1)
        return print_alias();
    if (len < 2)
        return 1;
    name = my_strdup(args[1]);
    value = my_array_dup(&args[2]);
    add_ll_alias(name, value);
    return 1;
}
