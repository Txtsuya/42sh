/*
** EPITECH PROJECT, 2025
** env
** File description:
** env
*/

#include "../include/minishel.h"

static int is_two_dote(char c)
{
    return (c != ':');
}

static char *base_path(char *cmd)
{
    const char *path = "/bin/";
    char *path_cmd = my_malloc(my_strlen(path) + my_strlen(cmd));

    my_strcpy(path_cmd, path);
    my_strcat(path_cmd, cmd);
    return path_cmd;
}

char *my_getenv(minishel_t *head, const char *name)
{
    while (head != NULL) {
        if (my_strcmp(name, head->name) == 0)
            return head->value;
        head = head->next;
    }
    return NULL;
}

static char *free_and_return(char *path_cmd, char **path_env)
{
    free_array(path_env);
    return path_cmd;
}

char *build_path_cmd(char *cmd, minishel_t **env)
{
    int i = 0;
    char *path;
    char **path_env;
    char *path_cmd;

    path = my_getenv(*env, "PATH");
    if (path == NULL)
        return base_path(cmd);
    path_env = my_str_to_word_array(path, is_two_dote);
    while (path_env[i] != NULL) {
        path_cmd = my_malloc(my_strlen(path_env[i]) + my_strlen(path) + 1);
        my_strcpy(path_cmd, path_env[i]);
        my_strcat(path_cmd, "/");
        my_strcat(path_cmd, cmd);
        if (access(path_cmd, X_OK) == 0)
            return free_and_return(path_cmd, path_env);
        my_free(path_cmd);
        i++;
    }
    return NULL;
}

void env_array_to_env_ll(char **env, minishel_t **head)
{
    int len_name;
    char *name;

    if (env == NULL) {
        head = NULL;
        return;
    }
    for (int i = 0; env[i] != NULL; i++) {
        len_name = my_strlen_c(env[i], '=');
        name = my_malloc(sizeof(char) * (len_name + 1));
        my_strncpy(name, env[i], len_name);
        add_llist(head, name, env[i] + len_name + 1);
        my_free(name);
    }
}

static int sizell(minishel_t *head)
{
    int cpt = 0;

    while (head != NULL) {
        cpt++;
        head = head->next;
    }
    return cpt;
}

char **ll_to_array_env(minishel_t *head)
{
    char **env_tab = my_malloc(sizeof(char *) * (sizell(head) + 1));
    char *tmp;
    int len = 0;
    int i = 0;

    while (head != NULL) {
        len = my_strlen(head->name) + 2;
        if (head->value != NULL)
            len += my_strlen(head->value);
        tmp = my_malloc(sizeof(char) * (len));
        my_strcpy(tmp, head->name);
        my_strcat(tmp, "=");
        if (head->value != NULL)
            my_strcat(tmp, head->value);
        env_tab[i] = tmp;
        i++;
        head = head->next;
    }
    env_tab[i] = NULL;
    return env_tab;
}

static int delete_first_node(minishel_t **head, char *name)
{
    minishel_t *tmp;

    if (*head == NULL || my_strcmp((*head)->name, name) != 0)
        return 0;
    tmp = *head;
    *head = (*head)->next;
    my_free(tmp->name);
    my_free(tmp->value);
    my_free(tmp);
    return 1;
}

int delete_llist(minishel_t **head, char *name)
{
    minishel_t *prev;
    minishel_t *curr;

    if (head == NULL || *head == NULL)
        return 0;
    if (delete_first_node(head, name))
        return 1;
    prev = *head;
    curr = (*head)->next;
    while (curr && my_strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr) {
        prev->next = curr->next;
        my_free(curr->name);
        my_free(curr->value);
        my_free(curr);
    }
    return 1;
}
