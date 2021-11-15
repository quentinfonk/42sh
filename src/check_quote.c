/*
** EPITECH PROJECT, 2020
** quote
** File description:
** get_quote
*/

#include <string.h>
#include "minishell.h"
#include "errno.h"

char *get_char_quote(char *str, int i)
{
    if (str[i] == '\\' && str[i + 1] == 'n')
        str[i + 1] = '1';
    if (str[i] == '\\' && str[i + 1] == 't')
        str[i + 1] = '2';
    if (str[i] == ' ')
        str[i] = 'K';
    return str;
}

char *set_first_str(char **args, char *str)
{
    int size = 0;
    char *test = malloc(sizeof(char) * 2);

    test[0] = ' ';
    test[1] = '\0';
    for (int i = 1; args[i] != NULL; i++)
        size += strlen(args[i]);
    for (int i = 1; args[i] != NULL; i++) {
        str = m_strcat(str, args[i]);
        str = m_strcat(str, test);
    }
    return str;
}

char **set_quote(int nb, char **args, char c)
{
    int v = 0, j = 0, i = 0;
    char *str = malloc(sizeof(char));
    int *quote = malloc(sizeof(int) * (nb + 1));

    quote[nb] = -1;
    str[0] = '\0';
    str = set_first_str(args, str);
    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == c) {
            quote[j] = i;
            j++;
        }
    for (j = 0, v = nb - 1; j < v ;j++, v--)
        for (i = quote[j]; i < quote[v]; i++)
            str = get_char_quote(str, i);
    args = set_quote_2(str, args, c);
    return args;
}

int get_quote(char **args, char c)
{
    int nb_d_quote = 0;
    int i = 0 , j = 0;

    for (i = 0; args[i] != NULL; i++)
        for (j = 0; args[i][j] != 0; j++)
            if (args[i][j] == c)
                nb_d_quote += 1;
    if (check_error_quote(nb_d_quote, c) == -1)
        return -1;
    if (nb_d_quote == 0)
        return 0;
    return nb_d_quote;
}

char **check_quote(char **args, char c)
{
    int error = 0;

    error = get_quote(args, c);
    if (error == -1)
        exit(0);
    else if (error == 0)
        return args;
    else if (error > 0)
        args = set_quote(error, args, c);
    return args;
}
