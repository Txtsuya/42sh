/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** display number given in argument
*/

#include <unistd.h>
#include "../../include/my.h"

int my_put_nbr(int nb)
{
    if (nb == -2147483648) {
        my_putstr("-2147483648");
        return 0;
    }
    if (nb < 0) {
        write(1, "-", 1);
        nb = nb * - 1;
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    my_putchar(nb % 10 + 48);
    return 0;
}
