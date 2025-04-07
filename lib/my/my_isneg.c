/*
** EPITECH PROJECT, 2024
** my_isneg.c
** File description:
** Display P if the parameter is positive, N if not
*/

#include "../../include/my.h"

int my_isneg(int n)
{
    if (n < 0) {
        my_putchar('N');
        return 1;
    } else {
        my_putchar('P');
        return 0;
    }
}
