/*
** EPITECH PROJECT, 2024
** my_find_prime_sup
** File description:
** return the smallest prime number greater than the parameter
*/

#include <stdio.h>
#include "../../include/my.h"

int my_find_prime_sup(int nb)
{
    int i = nb;

    while (i < 2147483647) {
        if (my_is_prime(i) == 1) {
            return i;
        }
        i++;
    }
    return 0;
}
