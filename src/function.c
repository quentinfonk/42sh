/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** function lil lib
*/

#include "minishell.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    for (; str[i]; i++);
    return i;
}

void my_putstr(char *str)
{
    if (str == NULL)
        return;
    write(1, str, my_strlen(str));
}

char *env_search(env_t *env, char *str)
{
    int j;
    env_t *tmp = env;

    if (env == NULL)
        return NULL;
    for (; tmp != NULL; tmp = tmp->next) {
        for (j = 0; str[j] == tmp->name[j]; j++);
        if (tmp->name[j] == '=' && (my_strlen(str) == j))
            return (tmp->name + j + 1);
    }
    return NULL;
}
