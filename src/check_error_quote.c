/*
** EPITECH PROJECT, 2020
** quote
** File description:
** *
*/

#include <string.h>
#include "minishell.h"
#include "errno.h"

int check_error_quote(int d_q, char c)
{
    if (c == '\'') {
        if ((d_q % 2) != 0) {
            write(2, "Unmatched '''.\n", 15);
            return -1;
        }
    }
    if (c == '"') {
        if ((d_q % 2) != 0) {
            write(2, "Unmatched '\"'.\n", 15);
            return -1;
        }
    }
    return 0;
}
