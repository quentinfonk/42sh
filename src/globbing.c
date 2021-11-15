/*
** EPITECH PROJECT, 2020
** est
** File description:
** *
*/

#include <glob.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"

char *set_blog(char *str)
{
    char *res = NULL;
    size_t count = 0;
    size_t size = 0;
    glob_t glob_results;
    char **tab = NULL;
    int i = 0;
    char **j = NULL;;

    glob(str, GLOB_NOCHECK, 0, &glob_results);
    count = glob_results.gl_pathc;
    tab = glob_results.gl_pathv;
    for (j = tab, i = count; i != 0; j++, i--)
        size += strlen(*j) + 1;
    res = (char *)calloc(size, sizeof(char));
    for (j = tab, i = count; i != 0; j++, i--) {
        res = m_strcat(res, *j);
        if (i > 1)
            res = m_strcat(res, " ");
    }
    globfree(&glob_results);
    return res;
}

char *get_blog(char *str)
{
    char **tab = my_str_to_array(str, ' ');

    for (int i = 0; tab[i] != NULL; i++)
        for(int j = 0; tab[i][j] != 0; j++)
            if (tab[i][j] == '?' || tab[i][j] == '*' ||
                tab[i][j] == '[' || tab[i][j] == ']')
                tab[i] = set_blog(tab[i]);
    for (int i = 0; tab[i + 1] != NULL; i++) {
        tab[0] = m_strcat(tab[0], " ");
        tab[0] = m_strcat(tab[0], tab[i + 1]);
    }
    str = tab[0];
    return str;
}
