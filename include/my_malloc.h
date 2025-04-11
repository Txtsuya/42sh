/*
** EPITECH PROJECT, 2024
** my_malloc
** File description:
** my_malloc.h
*/

#ifndef MY_MALLOC
    #define MY_MALLOC
    #include <stdlib.h>

typedef struct malloc_s {
    void *ptr;
    struct malloc_s *next;
} malloc_t;

void *my_malloc(size_t size);
char *my_strdup(char const *src);
void free_all(void);
void my_free(void *ptr);

#endif
