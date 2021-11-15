/*
** EPITECH PROJECT, 2020
** job_print
** File description:
** yes
*/

#include "minishell.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putnbr(int nbr)
{
    int nbr2;
    if (nbr < 0) {
        my_putchar('-');
        nbr = nbr * (-1);
    }
    if (nbr >= 10) {
        nbr2 = nbr % 10;
        nbr = nbr / 10;
        my_putnbr(nbr);
        my_putchar(nbr2 + 48);
    } else {
        my_putchar(nbr + 48);
    }
    return;
}

pid_t job_write(pid_t pid)
{
    write(1, "[1] ", 4);
    my_putnbr(pid);
    write(1, "\n", 1);
    return pid;
}
