/*
** EPITECH PROJECT, 2020
** quote
** File description:
** *
*/

#include <string.h>
#include "minishell.h"
#include "errno.h"

char *set_quote_4(char **temp, int i, char *str)
{
    int z = 0;

    for (int v = 0, x = 0;temp[i][v] != '\0'; v++, z++) {
        if (temp[i][v] == '\\' && temp[i][v + 1] == '1' && x == 0) {
            str[z] = '\n';
            v++;
            x = 1;
        }
        else if (temp[i][v] == '\\' && temp[i][v + 1] == '2' && x == 0) {
            str[z] = '\t';
            v++;
            x = 1;
        }
        else
            str[z] = temp[i][v];
    }
    str[z] = '\0';
    return str;
}

char **set_quote_3(char **temp, char **args)
{
    char *str = NULL;
    int i = 0, j = 0;

    for (i = 0; temp[i] != NULL; i++)
        for (j = 0; temp[i][j] != '\0'; j++)
            if (temp[i][j] == '\\') {
                str = malloc(sizeof(char) * (strlen(temp[i])));
                str = set_quote_4(temp, i, str);
                temp[i] = str;
            }
    for (i = 0; temp[i] != NULL; i++)
        for (j = 0; temp[i][j] != '\0'; j++)
            if (temp[i][j] == 'K')
                temp[i][j] = ' ' ;
    for (i = 0, j = 1; temp[i] != NULL; i++, j++)
        args[j] = temp[i];
    args[j] = NULL;
    return args;
}

char *set_q_str(char *str, char c)
{
    char **temp = NULL;
    char *new_str = malloc(sizeof(char));

    new_str[0] = 0;
    temp = my_str_to_array(str, c);
    for (int i = 0; temp[i] != NULL; i++)
        new_str = m_strcat(new_str, temp[i]);
    return new_str;
}

char **set_new_array(char **temp)
{
    char **new_array = NULL;
    int x = 0;

    for (x = 0; temp[x + 1] != NULL; x++);
    new_array = malloc(sizeof(char*) * (x + 1));
    for (x = 0; temp[x + 1] != NULL; x++)
        new_array[x] = temp[x];
    new_array[x] = NULL;
    return new_array;
}

char **set_quote_2(char *str, char **args, char c)
{
    char **temp = NULL;
    int i = 0;

    temp = my_str_to_array(str, ' ');
    temp = set_new_array(temp);
    for (i = 0; temp[i] != NULL; i++)
        temp[i] = set_q_str(temp[i], c);
    args = set_quote_3(temp, args);
    return args;
}
