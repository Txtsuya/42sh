/*
** EPITECH PROJECT, 2024
** my_strcmp.c
** File description:
** has the behavior of strcmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while ((i < n) && (s1[i] != '\0') && (s2[i] != '\0')) {
        if (s1[i] != s2[i]) {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    if (i < n) {
        return (s1[i] - s2[i]);
    }
    return 0;
}
