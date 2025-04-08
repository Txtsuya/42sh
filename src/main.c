/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../include/minishel.h"

int replace_in_list(minishel_t **head, char const *name, char *value)
{
    minishel_t *tmp = *head;

    while (tmp != NULL) {
        if (my_strcmp(name, tmp->name) == 0) {
            tmp->value = my_strdup(value);
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int seg_exit(int status)
{
    int detect;

    if (WIFSIGNALED(status)) {
        detect = WTERMSIG(status);
        if (detect == SIGSEGV) {
            write(2, "Segmentation fault\n", 19);
            return 139;
        }
        if (detect == SIGFPE) {
            write(2, "Floating exception\n", 19);
            return 136;
        }
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

void add_llist(minishel_t **head, const char *name, char *value)
{
    minishel_t *new = my_malloc(sizeof(minishel_t));
    minishel_t *temp;

    if (replace_in_list(head, name, value))
        return;
    new->name = my_strdup(name);
    new->value = NULL;
    if (value != NULL)
        new->value = my_strdup(value);
    new->next = NULL;
    if (*head == NULL) {
        *head = new;
    } else {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}

int main(int argc, char **argv, char **env)
{
    minishel_t *llenv;

    initialize_shell(env, &llenv);
    return main_loop(&llenv, env);
}
