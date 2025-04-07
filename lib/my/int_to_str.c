/*
** EPITECH PROJECT, 2025
** myradar
** File description:
** int_to_str
*/

#include "../../include/my.h"
#include <stdlib.h>

char *int_to_str_zero(void)
{
    char *str = my_strdup("0");

    return str;
}

char *int_to_str(int num)
{
    int temp = num;
    int length = 0;
    char *str;
    int i;

    if (num == 0)
        return int_to_str_zero();
    while (temp > 0) {
        length++;
        temp /= 10;
    }
    str = malloc((length + 1) * sizeof(char));
    str[length] = '\0';
    i = length - 1;
    while (num > 0) {
        str[i] = '0' + (num % 10);
        num /= 10;
        i--;
    }
    return str;
}
