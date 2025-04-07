/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** concatenate 2 string into one
*/

char *my_strcat(char *dest, const char *src)
{
    int i = 0;
    int n = 0;

    while (dest[n] != '\0') {
        n++;
    }
    while (src[i] != '\0') {
        dest[n + i] = src[i];
        i++;
    }
    dest[n + i] = '\0';
    return dest;
}
