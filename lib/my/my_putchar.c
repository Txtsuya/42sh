/*
** EPITECH PROJECT, 2024
** putchar
** File description:
** flm
*/
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
