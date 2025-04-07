/*
** EPITECH PROJECT, 2024
** my_compute_square_root
** File description:
** renvoie la racine carrée d'un nombre
*/
#include <stdio.h>

int my_compute_square_root(int nb)
{
    int test = 0;
    int i = 1;

    while (test < nb) {
        test = i * i;
        if (test == nb) {
            return i;
        }
        i++;
    }
    return 0;
}
