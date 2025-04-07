/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_strcspn.c
*/


int is_in_reject(char c, const char *reject)
{
    for (int i = 0; reject[i] != '\0'; i++) {
        if (reject[i] == c)
            return 1;
    }
    return 0;
}

int my_strcspn(const char *str, const char *reject)
{
    int i = 0;

    while (str[i] && !is_in_reject(str[i], reject))
        i++;
    return i;
}
