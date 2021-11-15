/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_setenv
*/

#include "minishell.h"

static int is_only_alphanum(char *str)
{
    if (str == NULL)
        return 0;
    for (int i = 0; str[i]; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')
            || (str[i] >= 'A' && str[i] <= 'Z'))
            continue;
        else
            return 84;
    }
    return 0;
}

static int set_env(char *s1, char *s2, env_t *env)
{
    if (s2 == NULL) {
        if (change_env(env, s1, "") == 84)
            create_node(my_strcat(s1, "=") , &env);
    }
    else {
        if (change_env(env, s1, s2) == 84)
            create_node(my_strcat(my_strcat(s1, "="), s2), &env);
    }
    return 0;
}

static int setenv_error(char *str)
{
    if ((*str >= 'a' && *str <= 'z') || (*str >= '0' && *str <= '9')
        || (*str >= 'A' && *str <= 'Z'))
        write(2, "setenv: Variable name must contain alphanumeric "
            "characters.\n", 60);
    else
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
    return 0;
}

int my_setenv(char *str, env_t *env)
{
    char **cmd = my_str_to_array(str, ' ');

    if (cmd[1] == NULL)
        return my_env("env", env);
    if (cmd[2] == NULL || cmd[3] == NULL) {
        if (is_only_alphanum(cmd[1]) == 0)
            return set_env(cmd[1], cmd[2], env);
        else
            return setenv_error(cmd[1]);
    }
    return write(2, "setenv: Too many arguments.\n", 28);
}
