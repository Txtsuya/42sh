/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** show every prototypes in mylib
*/

#ifndef MINISHEL_H
    #define MINISHEL_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "my.h"
    #include <sys/wait.h>
    #include <limits.h>
    #include <errno.h>
    #include <fcntl.h>

typedef struct minishel_s {
    char *name;
    char *value;
    struct minishel_s *next;
} minishel_t;

typedef struct pipeline_s {
    int pipe1[2];
    int pipe2[2];
    int read_fd;
    int nbr_cmd;
    minishel_t **env;
} pipeline_t;

void add_llist(minishel_t **head, const char *name, char *value);
char *my_getenv(minishel_t *head, const char *name);
char *build_path_cmd(char *cmd, minishel_t **env);
void env_array_to_env_ll(char **env, minishel_t **head);
char **ll_to_array_env(minishel_t *head);
int delete_llist(minishel_t **head, char *name);
int handle_builtin_cmd(char ***arguments,
    char *input, minishel_t **llenv);
static int builtin_cd(char **args, minishel_t **llenv);
int my_setenv(char **args, minishel_t **llenv);
int handle_env_commands(char **args, minishel_t **llenv);
void print_env(minishel_t *head);
void get_input(char **input, int ret_status, minishel_t **llenv);
void initialize_shell(char **env, minishel_t **llenv);
int execute_command(char *path_cmd, char **args, minishel_t **llenv);
int main_loop(minishel_t **llenv, char **env);
int len_array(char **array);
int replace_in_list(minishel_t **head, char const *name, char *value);
int seg_exit(int status);
void free_array(char **tab);
int len_array(char **array);
char *get_path_cmd(char *args, minishel_t **llenv);
int execute_multi_cmd(minishel_t **llenv, char *input);
int execute_main_cmd(char *cmd, minishel_t **llenv);
int executepipe(char *token, minishel_t **llenv);
int nbr_instr(char const *str, char c);
void free_array(char **tab);
int parse_redirections(char **args);
char **remove_redirections(char **args);
int test_valid_pipe(char *token);
int execute_pipeline(char *commands, int nbr_cmd, minishel_t **env);
int check_right_argv(char *argv);

#endif
