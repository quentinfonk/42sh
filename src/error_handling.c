/*
** EPITECH PROJECT, 2020
** error_handling.c
** File description:
** yes
*/

#include "minishell.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void bin_not_compatible(char **args)
{
    if (errno == ENOEXEC) {
        my_putstr(args[0]);
        write(1, ": Exec format error. Wrong Architecture.\n", 41);
    }
    exit(1);
}
