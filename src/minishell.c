/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** minishell parser
*/

#include "minishell.h"
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

static int find_string(char *s1, char *s2)
{
    int i = 0;

    for (; s1[i] && (s1[i] == ' ' || s1[i] == '\t'); i++);
    if (s1[i] == 0)
        return 84;
    for (; s2[i] && s1[i] == s2[i]; i++);
    if (s2[i] == 0)
        return 0;
    return 84;
}

int my_env(char *str, env_t *env)
{
    char **cmd_env = my_str_to_array(str, ' ');

    if (cmd_env[1] != NULL)
        return write(2, "Too many arguments.\n", 20);
    for (env_t *tmp = env; tmp != NULL; tmp = tmp->next) {
        if (tmp->name[0] == '.')
            continue;
        my_putstr(tmp->name);
        write(1, "\n", 1);
    }
    return 0;
}

static int is_bultin(char *str, env_t *env)
{
    if (find_string(str, "cd") == 0)
        return my_cd(str, env);
    if (find_string(str, "env") == 0)
        return my_env(str, env);
    if (find_string(str, "setenv") == 0)
        return my_setenv(str, env);
    if (find_string(str, "unsetenv") == 0)
        return my_unsetenv(str, env);
    return 84;
}

char *execute_commands(char *str, env_t *env)
{
    char **command = my_str_to_array(str, '|');
    int pd[2];
    int is_pipe = 0;
    struct termios buff;

    if (command[1] != NULL)
        is_pipe = 1;
    for (int i = 0; command[i] != NULL; i++) {
        if (is_pipe != 0)
            pipe(pd);
        command[i] = clean_str(command[i]);
        if (command[i][0] == '\0' || is_bultin(command[i], env) != 84)
            continue;
        else if (env != NULL) {
            command = job_control(command);
            if (command[i + 1] == NULL && i != 0)
                is_pipe = 2;
            my_exec(my_str_to_array(command[i], ' '), env, pd, is_pipe);
        }
    }
    for (int i = 0; command[i] != NULL; i++)
        free(command[i]);
    return NULL;
}
