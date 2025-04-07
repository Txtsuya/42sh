/*
** EPITECH PROJECT, 2024
** my_is_prime
** File description:
** dit si un nombre est premier ou pas
*/
#include <stdio.h>

int my_is_prime(int nb)
{
    int i;

    if (nb < 2) {
        return 0;
    }
    for (i = 2; i < nb; i++) {
        if (nb % i == 0) {
            return 0;
        }
    }
    return 1;
}
