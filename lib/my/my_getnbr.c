/*
** EPITECH PROJECT, 2024
** get_nbr
** File description:
** tranform string nb into int nb (hard)
*/

int my_getnbr(char const *str)
{
    int i = 0;
    int nb = 0;
    int sign = 1;

    while ((str[i] < 48 || str[i] > 57) && (str[i] != '\0')) {
        if (str[i] == '-') {
            sign = sign * - 1;
        }
        i++;
    }
    while ((str[i] >= 48 && str[i] <= 57) && (str[i] != '\0')) {
        nb = (nb * 10) + str[i] - 48 - 1 * ((str[i + 1] < 48 ||
        str[i + 1] > 57) && (sign < 0));
        i++;
    }
    if (nb < 0) {
        return 0;
    }
    nb = nb * sign - 1 * (sign < 0);
    return nb;
}
