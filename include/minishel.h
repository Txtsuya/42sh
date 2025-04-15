/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** show every prototypes in mylib
*/

#ifndef MINISHEL_H
    #define MINISHEL_H

    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "my.h"
    #include "my_malloc.h"
    #include <sys/wait.h>
    #include <limits.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <termios.h>

typedef struct alias_ll {
    char *name;
    char **value;
    struct alias_ll *next;
} alias_ll_t;

typedef struct minishel_s {
    char *name;
    char *value;
    struct minishel_s *next;
} minishel_t;

typedef struct command_s {
    char *name;
    int (*handler)(char **args, minishel_t **llenv);
} command_t;

typedef struct pipeline_s {
    int pipe1[2];
    int pipe2[2];
    int read_fd;
    int nbr_cmd;
    minishel_t **env;
} pipeline_t;

typedef struct s_pipe_ctx {
    int num_of_pipe;
    int (*pipefd)[2];
    pid_t *pid;
    minishel_t **env;
    char **argv;
    int read_pipe;
    int write_pipe;
} pipe_ctx_t;

typedef struct {
    int index;
    int start;
    int level;
    int i;
} parse_ctx_t;

typedef struct {
    int level_par;
    int level_signle;
    int level_double;
} level_ini_t;

typedef enum job_state {
    JOB_RUNNING,
    JOB_STOPPED,
    JOB_DONE
} job_state_t;

typedef struct job_s {
    int id;
    char *command;
    pid_t pid;
    job_state_t state;
    struct job_s *next;
} job_t;

char **clean_quote(char **array);
int is_level_0(level_ini_t *level);
void update_level(level_ini_t *level, char input);
job_t **get_job_list(void);
void safely_print_jobs_done(void);

int background(char **args);
void print_jobs_done(void);
job_t *find_job_by_id(int job_id);
void remove_job(int job_id);
int forground(char **args);
int print_jobs(void);
job_t *find_job_by_pid(pid_t pid);
job_t *add_job(pid_t pid, char *cmd);
int handle_background(char *cmd, minishel_t **llenv);
int execute_background(char *cmd, minishel_t **llenv);
void update_jobs_status(void);

int is_simple_sep(char c);
int is_double_sep(char *str, int i);
int is_pipe(char c);
int is_redirection(char c);
int search_pipe(char *input);
char **string_to_array_for_parentheses(char *input);
char *clean_parenthese_argv(char *cmd);
int is_red_or_operator(char *cmd);
int handle_redirection_in_parenthese(char **all_arg, minishel_t **llenv);
int check_error_parenthese(char **all_arg, char *input, int arraylen);
int handle_parenthese(minishel_t **llenv, char *input);
char **string_to_array_with_priority(char *input, int (*func)(char));

int handle_env(char **args, minishel_t **llenv);
int handle_setenv(char **args, minishel_t **llenv);
int handle_unsetenv(char **args, minishel_t **llenv);
int handle_exit(char **args, minishel_t **llenv);
int handle_cd(char **args, minishel_t **llenv);
int handle_variable(char **args, minishel_t **llenv);
int handle_unset(char **args, minishel_t **llenv);
void add_llist_env(char *pwd, minishel_t **llenv, const char *name);
void add_llist(minishel_t **head, const char *name, char *value);
char *my_getenv(minishel_t *head, const char *name);
char *build_path_cmd(char *cmd, minishel_t **env);
void env_array_to_env_ll(char **env, minishel_t **head);
char **ll_to_array_env(minishel_t *head);
int delete_llist(minishel_t **head, char *name);
int handle_builtin_cmd(char ***arguments,
    char *input, minishel_t **llenv);
int builtin_cd(char **args, minishel_t **llenv);
int my_setenv(char **args, minishel_t **llenv);
int handle_env_commands(char **args, minishel_t **llenv);
void print_env(minishel_t *head);
void get_input(char **input, int ret_status, minishel_t **llenv);
void initialize_shell(char **env, minishel_t **llenv);
int execute_command(char *path_cmd, char **args, minishel_t **llenv);
int main_loop(minishel_t **llenv);
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
int handle_alias(char **args, minishel_t **llenv);
void check_alias(char ***args);
char *extract_between_quotes(const char *str);
char *my_strchr(const char *str, int c);
int handle_unalias(char **args, minishel_t **llenv);
alias_ll_t **get_ll_alias(void);
char **globbing(char **command);

#endif
