/*
** EPITECH PROJECT, 2025
** other
** File description:
** other
*/
#include "../include/minishel.h"

int count_arg(char *input)
{
    int level = 0;
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(') {
            level++;
        } else if (input[i] == ')') {
            level--;
        } else if (input[i] == ';' && level == 0) {
            count++;
        }
    }
    return count + 1;
}

char *copy_string_to_array(char *input, char **array, int start, int end)
{
    int length = end - start;
    char *temp = malloc(sizeof(char) * (length + 1));

    for (int i = 0; i < length; i++) {
        temp[i] = input[start + i];
    }
    temp[length] = '\0';
    return temp;
}

char **string_to_array_with_priority(char *input, int (*func)(char))
{
    int start = 0;
    int level = 0;
    int count_word = count_arg(input);
    int index = 0;
    char **array = malloc(sizeof(char *) * (count_word + 1));

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(') {
            level++;
        } else if (input[i] == ')') {
            level--;
        } else if (func(input[i]) && level == 0) {
            array[index] = copy_string_to_array(input, array, start, i);
            index++;
            start = i + 1;
        }
    }
    array[index] = copy_string_to_array(input, array, start, strlen(input));
    array[index + 1] = NULL;
    return array;
}
