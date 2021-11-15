/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** init the linked list for the env
*/

#include "minishell.h"

void create_node(char *str, env_t **head)
{
    env_t *node = malloc(sizeof(env_t));
    env_t *tmp =*head;

    if (tmp == NULL) {
        node->name = str;
        node->next = NULL;
        *head = node;
        return;
    }
    for (; tmp->next != NULL; tmp = tmp->next);
    node->name = str;
    node->next = NULL;
    tmp->next = node;
}

static char *str_cpy(char const *str)
{
    int buf = my_strlen(str);
    char *ret = malloc(sizeof(char) * (buf + 1));

    for (int i = 0; str[i]; i++)
        ret[i] = str[i];
    ret[buf] = 0;
    return ret;
}

env_t *init_env(char **env)
{
    env_t *ret = NULL;

    create_node(".", &ret);
    if (env == NULL)
        return ret;
    for (int j = 0; env[j] != NULL; j++)
        create_node(str_cpy(env[j]), &ret);
    return ret;
}
