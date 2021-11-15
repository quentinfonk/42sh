/*
** EPITECH PROJECT, 2020
** var
** File description:
** *
*/

#include "minishell.h"
#include <string.h>

int get_inter(char **args)
{
    int var = 0;

    for (int i = 0; args[i] != NULL; i++)
        for (int j = 0; args[i][j] != 0; j++)
            if (args[i][j] == '$')
                var += 1;
    return var;
}

char *set_new_arg(char *var, int doll, char *str, char **env)
{
    char *part_1 = NULL;
    char *part_2 = NULL;
    int i = 0;
    int size = 0;

    for (i = 0; i < doll; i++, size++);
    part_1 = malloc(sizeof(char) * (size + 1));
    for (i = 0; i < doll; i++)
        part_1[i] = str[i];
    part_1[i] = 0;
    for (i = (strlen(env[0]) + 1), size = 0; var[i] != 0; i++, size++);
    part_2 = malloc(sizeof(char) * (size + 1));
    for (i = (strlen(env[0]) + 1), size = 0; var[i] != 0; i++, size++)
        part_2[size] = var[i];
    part_2[size] = 0;
    part_1 = m_strcat(part_1, env[1]);
    part_1 = m_strcat(part_1, part_2);
    return part_1;
}

char *get_var(char *str, int i, char *env, char **all_env)
{
    int size = 0;
    int j = 0;
    char *temp = NULL;

    for (j = i, size = 0; str[j] != 0; size++, j++);
    temp = malloc(sizeof(char) * (size + 1));
    for (j = i, size = 0; str[j] != 0; size++, j++)
        temp[size] = str[j];
    temp[size] = 0;
    if (strncmp(temp, env, strlen(env)) == 0)
        str = set_new_arg(temp, i, str, all_env);
    return str;
}
