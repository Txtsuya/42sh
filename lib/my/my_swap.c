/*
** EPITECH PROJECT, 2024
** my_swap
** File description:
** swap the content of two int given in parameters
*/

void my_swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}
