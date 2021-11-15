/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_unsetenv
*/

#include "minishell.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    for (; s1[i] && s2[i]; i++)
        if (s1[i] != s2[i])
            return 84;
    if (s1[i] == 0 && s2[i] == '=')
        return 0;
    return 84;
}

static void del_node(char *str, env_t **head)
{
    env_t *tmp = *head;
    env_t *tmp_2 = *head;

    for (; tmp; tmp = tmp->next) {
        if (my_strcmp(str, tmp->name) == 0) {
            tmp_2->next = tmp->next;
            free(tmp);
            return;
        }
        if (tmp != tmp_2)
            tmp_2 = tmp_2->next;
    }
}

int my_unsetenv(char *str, env_t *env)
{
    char **args = my_str_to_array(str, ' ');

    if (env == NULL)
        return 0;
    for (int i = 1; args[i] != NULL; i++)
        del_node(args[i], &env);
    return 0;
}
