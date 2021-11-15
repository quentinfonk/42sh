/*
** EPITECH PROJECT, 2020
** PSU_mnishell2_2019
** File description:
** my_cd
*/

#include "minishell.h"

static char *cd_check_args_and_dir(env_t *env, char *arg, char *oldpwd)
{
    char *ret = env_search(env, "HOME");

    if (arg == NULL)
        return ret;
    if (arg[0] == '-' && arg[1] == 0) {
        if (oldpwd != NULL)
            return oldpwd;
        else
            return NULL;
    }
    else if (arg[0] == '~' && arg[1] == 0)
        return ret;
    return arg;
}

char *my_strcat(char *s1, char *s2)
{
    char *ret = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
    int i = 0;

    for (; s1[i]; i++)
        ret[i] = s1[i];
    for (int j = 0; s2[j]; j++)
        ret[i++] = s2[j];
    ret[i] = 0;
    return ret;
}

int change_env(env_t *env, char *pwd, char *value)
{
    int j = 0;
    char *buf;

    for (env_t *tmp = env; tmp != NULL; tmp = tmp->next) {
        for (j = 0; tmp->name[j] == pwd[j]; j++);
        if (tmp->name[j] == '=' && pwd[j] == 0) {
            free(tmp->name);
            buf = my_strcat(pwd, "=");
            tmp->name = my_strcat(buf, value);
            free(buf);
            return 0;
        }
    }
    return 84;
}

static int built_in_cd(char **cd, env_t *env)
{
    static char *oldpwd;
    char *dir = cd_check_args_and_dir(env, cd[1], oldpwd);

    if (dir == NULL)
        return 0;
    if (access(dir, F_OK) == -1) {
        write(2, dir, my_strlen(dir));
        write(2, ": No such file or directory.", 28);
        return write(2, "\n", 1);
    }
    if (access(dir, R_OK) == -1) {
        write(2, dir, my_strlen(dir));
        return write(2, ": Permission denied.\n", 22);
    }
    oldpwd = getcwd(NULL, 0);
    if (chdir(dir) == -1) {
        write(2, dir, my_strlen(dir));
        return write(2, ": Not a directory.\n", 19);
    }
    change_env(env, "PWD", getcwd(NULL, 0));
    return 0;
}

int my_cd(char *str, env_t *env)
{
    char **cd = my_str_to_array(str, ' ');
    int i = 0;

    for (; cd[i] != NULL; i++);
    if (i == 3) {
        write(2, "cd: string not in pwd: ", 23);
        write(2, cd[1], my_strlen(cd[1]));
        return write(2, "\n", 1);
    }
    else if (i >= 4)
        return write(2, "cd: too many arguments\n", 23);
    built_in_cd(cd, env);
    return 0;
}
