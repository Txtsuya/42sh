#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "my.h"
#include "my_malloc.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_strlen, basic_test)
{
    cr_assert_eq(my_strlen("Hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strcmp, basic_test)
{
    cr_assert_eq(my_strcmp("Hello", "Hello"), 0);
    cr_assert_gt(my_strcmp("Hello", "Hell"), 0);
    cr_assert_lt(my_strcmp("Hell", "Hello"), 0);
}

Test(my_strcat, basic_test)
{
    char dest[20] = "Hello";
    char *result = my_strcat(dest, " World");
    cr_assert_str_eq(result, "Hello World");
}

Test(my_strcpy, basic_test)
{
    char dest[20];
    my_strcpy(dest, "Hello");
    cr_assert_str_eq(dest, "Hello");
}

Test(my_getnbr, basic_test)
{
    cr_assert_eq(my_getnbr("42"), 42);
    cr_assert_eq(my_getnbr("-42"), -42);
    cr_assert_eq(my_getnbr("abc"), 0);
}

Test(my_putstr, basic_test, .init = redirect_all_stdout)
{
    my_putstr("Hello World");
    cr_assert_stdout_eq_str("Hello World");
}

Test(my_str_isnum, basic_test)
{
    cr_assert_eq(my_str_isnum("12345"), 1);
    cr_assert_eq(my_str_isnum("123a45"), 0);
}

Test(my_revstr, basic_test)
{
    char str[] = "Hello";
    cr_assert_str_eq(my_revstr(str), "olleH");
}

Test(my_strdup, basic_test)
{
    char *dup = my_strdup("Test");
    cr_assert_str_eq(dup, "Test");
    free(dup);
}

Test(my_compute_power_rec, basic_test)
{
    cr_assert_eq(my_compute_power_rec(2, 3), 8);
    cr_assert_eq(my_compute_power_rec(3, 0), 1);
    cr_assert_eq(my_compute_power_rec(2, -1), 0);
}

Test(my_compute_square_root, basic_test)
{
    cr_assert_eq(my_compute_square_root(16), 4);
    cr_assert_eq(my_compute_square_root(0), 0);
    cr_assert_eq(my_compute_square_root(-1), 0);
}

Test(my_str_islower, basic_test)
{
    cr_assert_eq(my_str_islower("hello"), 1);
    cr_assert_eq(my_str_islower("Hello"), 0);
    cr_assert_eq(my_str_islower("hello123"), 0);
}

Test(my_str_isupper, basic_test)
{
    cr_assert_eq(my_str_isupper("HELLO"), 1);
    cr_assert_eq(my_str_isupper("Hello"), 0);
    cr_assert_eq(my_str_isupper("HELLO123"), 0);
}

Test(my_str_isprintable, basic_test)
{
    cr_assert_eq(my_str_isprintable("Hello123!"), 1);
    cr_assert_eq(my_str_isprintable("\n\t"), 0);
}

Test(my_strlowcase, basic_test)
{
    char str[] = "HeLLo WoRLD";
    cr_assert_str_eq(my_strlowcase(str), "hello world");
}

Test(my_strupcase, basic_test)
{
    char str1[] = "hello world";
    char str2[] = "HELLO WORLD";
    cr_assert_str_eq(my_strupcase(str1), "HELLO WORLD");
    cr_assert_str_eq(my_strupcase(str2), "HELLO WORLD");
}

Test(my_strncmp, basic_test)
{
    cr_assert_eq(my_strncmp("Hello", "Hello", 5), 0);
    cr_assert_eq(my_strncmp("Hello", "Hell", 4), 0);
    cr_assert_gt(my_strncmp("Hello", "Hell", 5), 0);
}

Test(my_strncpy, basic_test)
{
    char dest[20] = {0};
    cr_assert_str_eq(my_strncpy(dest, "Hello", 5), "Hello");
    char dest2[20] = {0};
    cr_assert_str_eq(my_strncpy(dest2, "Hello", 3), "Hel");
}

Test(my_strncat, basic_test)
{
    char dest[20] = "Hello";
    cr_assert_str_eq(my_strncat(dest, " World", 3), "Hello Wo");
}

Test(my_strstr, basic_test)
{
    cr_assert_str_eq(my_strstr("Hello World", "World"), "World");
    cr_assert_null(my_strstr("Hello World", "xyz"));
}

Test(my_is_prime, basic_test)
{
    cr_assert_eq(my_is_prime(2), 1);
    cr_assert_eq(my_is_prime(17), 1);
    cr_assert_eq(my_is_prime(4), 0);
}

Test(my_find_prime_sup, basic_test)
{
    cr_assert_eq(my_find_prime_sup(10), 11);
    cr_assert_eq(my_find_prime_sup(2), 2);
}

Test(my_isneg, basic_test)
{
    cr_assert_eq(my_isneg(-1), 1);
    cr_assert_eq(my_isneg(1), 0);
}

Test(int_to_str, basic_test)
{
    cr_assert_str_eq(int_to_str(123), "123");
}

Test(my_str_isalpha, basic_test)
{
    cr_assert_eq(my_str_isalpha("abcDEF"), 1);
    cr_assert_eq(my_str_isalpha("abc123"), 0);
    cr_assert_eq(my_str_isalpha(""), 1);
}

Test(my_strchr, basic_test)
{
    cr_assert_eq(my_strchr("hello", 'e') - "hello", 1);
    cr_assert_null(my_strchr("hello", 'z'));
}

Test(my_strcspn, basic_test)
{
    cr_assert_eq(my_strcspn("hello", "l"), 2);
    cr_assert_eq(my_strcspn("hello", "z"), 5);
}

Test(my_strncpy, partial_test)
{
    char dest[10] = {0};
    cr_assert_str_eq(my_strncpy(dest, "abcdef", 3), "abc");
    char dest2[10] = {0};
    cr_assert_str_eq(my_strncpy(dest2, "abc", 5), "abc");
}

Test(my_strlen, edge_cases)
{
    cr_assert_eq(my_strlen("a"), 1);
    cr_assert_eq(my_strlen("ab"), 2);
}

Test(my_strncmp, edge_cases)
{
    cr_assert_eq(my_strncmp("abc", "abd", 2), 0);
    cr_assert_lt(my_strncmp("abc", "abd", 3), 0);
    cr_assert_gt(my_strncmp("abd", "abc", 3), 0);
}
