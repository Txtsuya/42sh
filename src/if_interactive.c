/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Mode interactif pour if - version finale
*/

#include "../include/minishel.h"

char *read_interactive_line(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    FILE *term = NULL;
    int len = 0;

    term = fopen("/dev/tty", "r");
    if (!term)
        return NULL;
    write(STDOUT_FILENO, "if? ", 4);
    if (getline(&buffer, &buffer_size, term) == -1) {
        fclose(term);
        if (buffer)
            free(buffer);
        return NULL;
    }
    fclose(term);
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    return buffer;
}

int handle_if_interactive_mode(minishel_t **llenv, int condition_result)
{
    char *line = NULL;

    while (1) {
        line = read_interactive_line();
        if (!line)
            return 1;
        if (strcmp(line, "else") == 0 || strcmp(line, "endif") == 0) {
            free(line);
            return 0;
        }
        add_history(line);
        free(line);
    }
    return 0;
}
