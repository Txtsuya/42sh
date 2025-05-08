#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "my_malloc.h"

Test(my_malloc, alloc_and_write)
{
    int *ptr = my_malloc(sizeof(int));
    cr_assert_not_null(ptr);
    *ptr = 42;
    cr_assert_eq(*ptr, 42);
    my_free(ptr);
}

Test(my_malloc, double_alloc_and_free)
{
    char *a = my_malloc(10);
    char *b = my_malloc(20);
    cr_assert_not_null(a);
    cr_assert_not_null(b);
    my_free(a);
    my_free(b);
}

Test(my_malloc, free_all)
{
    int *a = my_malloc(sizeof(int));
    char *b = my_malloc(100);
    cr_assert_not_null(a);
    cr_assert_not_null(b);
    free_all(); // doit tout libérer sans crash
}

Test(my_malloc, free_nonexistent)
{
    int x;
    my_free(&x); // ne doit pas crash
}
