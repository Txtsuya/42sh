/*
** EPITECH PROJECT, 2024
** my_str_isalpha
** File description:
** return 1 if there is only alphabetical characters in str
*/

int my_str_isalpha(char const *str)
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if ((str[i] >= 97 && str[i] <= 122) ||
            (str[i] >= 65 && str[i] <= 90)) {
            j++;
        }
        i++;
    }
    if (i == j || i == 0) {
        return 1;
    } else {
        return 0;
    }
}
