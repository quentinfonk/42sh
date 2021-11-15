/*
** EPITECH PROJECT, 2020
** PSU_minishell2
** File description:
** header
*/

#ifndef __MY_H__
#define __MY_H__

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include "gnl.h"

typedef struct history_s {
    char *cmd;
    struct history_s *next;
    struct history_s *prev;
} history_t;

typedef struct {
    char ch;
    int cursor;
    char *str;
    char last_chars[3];
    history_t *current;
} line_t;

typedef struct redirection_t {
    char **red;
    int redirection_two_right;
    int redirection_two_left;
    int redirection_left;
    int redirection_right;
} redirection_t;

typedef struct command_t {
    char **cmd;
    int fd;
    int input;
    int output;
    int nb_redirections;
    redirection_t **redirection;
    struct command_t *next;
    struct command_t *prev;
} command_t;

typedef struct list_t {
    command_t *first;
    command_t *last;
} list_t;

typedef struct env {
    char *name;
    struct env *next;
} env_t;

enum sep_state {
    SEP_ON,
    SEP_SKIP,
    END1
};

bool tab[END1];

enum job_state {
    BACKGROUND,
    FORGROUND,
    END2
};

bool job_tab[END2];

int my_strlen(char const *str);
env_t *init_list_env(char **env);
char *env_search(env_t *env, char *str);
char **my_str_to_array(char *str, char c);
void my_putstr(char *str);
char *execute_commands(char *str, env_t *env);
env_t *init_env(char **env);
char *clean_str(char *str);
void create_node(char *str, env_t **head);
void my_exec(char **args, env_t *env, int pd[2], int pipe);
char *my_strcat(char *s1, char *s2);
int my_cd(char *str, env_t *env);
int my_setenv(char *str, env_t *env);
char **my_str_to_array(char *str, char c);
int my_unsetenv(char *str, env_t *env);
int my_env(char *str, env_t *env);
int change_env(env_t *env, char *pwd, char *value);
void seg_fault(char *str);
char **check_for_redir(char **args);
int my_strcmp(char *s1, char *s2);
char **check_quote(char **args, char c);
char **set_quote_2(char *str, char **args, char c);
int check_error_quote(int d_q, char c);
char **var_interpreter(char **args, env_t *env);
char *get_var(char *str, int i, char *env, char **all_env);
int get_inter(char **args);
char *m_strcat(char *dest, char *src);
char *get_blog(char *str);
char **job_control(char **command);
pid_t job_write(pid_t pid);
void bin_not_compatible(char **args);
int left_arrow(line_t *line);
int right_arrow(line_t *line);
int down_arrow(line_t *line);
int up_arrow(line_t *line);
int backspace(line_t *line);
int ctrl_l(line_t *line);

#endif /* __MY_H__ */
