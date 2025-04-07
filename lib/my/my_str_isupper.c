/*
** EPITECH PROJECT, 2024
** my_str_isupper.c
** File description:
** return 1 if all in upper case
*/

int my_str_isupper(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] < 65 || str[i] > 90) {
            return 0;
        }
        i++;
    }
    return 1;
}
