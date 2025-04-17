/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** check_valid_args.c
*/

#include "../include/minishel.h"

int valid_name(const char *name)
{
    if (nbr_instr(name, '=') > 0)
        return 0;
    if (!((name[0] >= 'a' && name[0] <= 'z')
        || (name[0] >= 'A' && name[0] <= 'Z')))
        return 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'a' && name[i] <= 'z') ||
            (name[i] >= 'A' && name[i] <= 'Z') ||
            (name[i] >= '0' && name[i] <= '9') ||
            name[i] == '_' || name[i] == '=' || name[i] == '$'))
            return 0;
    }
    return 1;
}

int check_right_argv(char *argv)
{
    if (!valid_name(argv)) {
        my_putstr("setenv: Variable name must "
            "contain alphanumeric characters.\n");
        return 1;
    }
    return 0;
}
