/*
** EPITECH PROJECT, 2020
** job_control.c
** File description:
** yes
*/

#include "minishell.h"

int my_strcmp_job(char const *empty, char const *wanted)
{
    int i = 0;

    if (my_strlen(empty) != my_strlen(wanted))
        return 1;
    for (i = 0; empty[i] != '\0'; ++i)
        if (wanted[i] != empty[i])
            return 1;
    return 0;
}

char *fire_arg(char *command)
{
    for (int i = 0; command[i] != '\0'; ++i)
        if (command[i] == '&')
            command[i] = ' ';
    return command;
}

char **job_control(char **command)
{
    char **str = my_str_to_array(command[0], ' ');

    job_tab[BACKGROUND] = false;
    for (int i = 0; str[i] != NULL; ++i) {
        if (my_strcmp_job(str[i], "&") == 0) {
            job_tab[BACKGROUND] = true;
            command[0] = fire_arg(command[0]);
        }
    }
    return command;
}
