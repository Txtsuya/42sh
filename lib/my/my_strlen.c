/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** display the len of a string
*/

int my_strlen(char const *str)
{
    int cpt = 0;

    while (str[cpt] != '\0') {
        cpt = cpt + 1;
    }
    return (cpt);
}

int my_strlen_c(char const *str, char c)
{
    int cpt = 0;

    while (str[cpt] != '\0' && str[cpt] != c) {
        cpt = cpt + 1;
    }
    return (cpt);
}
