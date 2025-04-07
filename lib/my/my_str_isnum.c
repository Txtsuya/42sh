/*
** EPITECH PROJECT, 2024
** my_str_isnum.c
** File description:
** display 1 if contains only number 0 if not
*/

int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] > 57 || str[i] < 48) {
            return 0;
        }
        i++;
    }
    return 1;
}
