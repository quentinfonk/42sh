/*
** EPITECH PROJECT, 2020
** get_file.c
** File description:
** function that takes a filepath and return a linked list of the file
*/

#include "minishell.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void create_file_node(history_t **start, char *str)
{
    history_t *node = malloc(sizeof(history_t));

    node->cmd = str;
    node->prev = *start;
    node->next = NULL;
    if (*start == NULL) {
        *start = node;
        return;
    }
    (*start)->next = node;
    *start = node;
}

static char *copy_string(char const *line)
{
    char *ret;
    int i = 0;

    for (; line[i] != '\n'; i++);
    ret = malloc(sizeof(char) * (i + 1));
    if (ret == NULL)
        return NULL;
    for (i = 0; line[i] != '\n'; i++)
        ret[i] = line[i];
    ret[i] = 0;
    return ret;
}

history_t *get_history(void)
{
    FILE *fd = fopen(".history", "r");
    history_t *ret = NULL;
    size_t buf = 0;
    char *line = malloc(1);

    if (fd == NULL)
        return NULL;
    while (getline(&line, &buf, fd) != -1) {
        create_file_node(&ret, copy_string(line));
    }
    free(line);
    fclose(fd);
    return ret;
}
