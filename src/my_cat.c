/*
** EPITECH PROJECT, 2020
** test
** File description:
** m_strcat
*/

#include "minishell.h"
#include <string.h>

char *m_strcat(char *dest, char *src)
{
    int k = 0, v = 0;
    int i = my_strlen(dest);
    int j = my_strlen(src);
    char *strfinal = malloc(sizeof(char) * (i + j + 1));
    char *str_new = malloc(sizeof(char) * (i + j + 1));
    int a = (i + j - 1);

    j = 0;
    for (; k != i; k++)
        strfinal[k] = dest[k];
    for (; src[j] != '\0'; k++, j++)
        strfinal[k] = src[j];
    strfinal[k] = '\0';
    for (v = 0; v <= a; v++)
        str_new[v] = strfinal[v];
    str_new[v] = '\0';
    return (str_new);
}
