/*
** EPITECH PROJECT, 2024
** my_malloc
** File description:
** my_malloc.c
*/

#include "../../include/minishel.h"

malloc_t **get_malloc_struct(void)
{
    static malloc_t *head = NULL;

    return &head;
}

void add_malloc(malloc_t **llmalloc, void *ptr)
{
    malloc_t *new = malloc(sizeof(malloc_t));

    if (new == NULL)
        return;
    new->ptr = ptr;
    new->next = *llmalloc;
    *llmalloc = new;
}

void *my_malloc(size_t size)
{
    malloc_t **llmalloc = get_malloc_struct();
    void *new = malloc(size);

    if (new == NULL)
        return NULL;
    add_malloc(llmalloc, new);
    return new;
}

void free_all(void)
{
    malloc_t **zeub = get_malloc_struct();
    malloc_t *current = *zeub;
    malloc_t *tmp = NULL;

    while (current) {
        tmp = current->next;
        if (current->ptr != NULL)
            free(current->ptr);
        free(current);
        current = tmp;
    }
    *zeub = NULL;
}

void my_free(void *ptr)
{
    malloc_t **head_ref = get_malloc_struct();
    malloc_t *current = *head_ref;
    malloc_t *prev = NULL;

    while (current != NULL && current->ptr != ptr) {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    if (prev == NULL)
        *head_ref = current->next;
    else
        prev->next = current->next;
    free(ptr);
    free(current);
}
