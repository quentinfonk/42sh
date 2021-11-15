/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_str_to_array
*/

#include "minishell.h"
#include <errno.h>

void seg_fault(char *str)
{
    if (errno == ENOEXEC) {
        my_putstr(str);
        my_putstr(": Exec format error. Wrong Architecture.\n");
    }
    else {
        write(1, str, my_strlen(str));
        my_putstr(": Permission denied.\n");
    }
}

static int count_char(char *str, char c)
{
    int	count = 1;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i]; i++) {
        for (; str[i] && str[i] != c; i++);
        count += 1;
        if (str[i] == 0)
            break;
    }
    return count;
}

static char *get_word(char *str, int *in, char c)
{
    int count = 0;
    char *ret;
    int i = 0;

    for (int j = 0; str[j] && str[j] != c; j++, count += 1, (*in) += 1);
    (*in)--;
    for (; str[count - 1] == ' ' || str[count - 1] == '\t'; count--);
    ret = malloc(sizeof(char) * (count + 1));
    if (ret == NULL)
        return NULL;
    for (; str[i] && i < count; i += 1)
        ret[i] = str[i];
    ret[i] = '\0';
    return ret;
}

char **my_str_to_array(char *str, char c)
{
    char **ret = malloc(sizeof(char *) * (count_char(str, c) + 1));
    int	i = 0;
    int	j = 0;

    if (ret == NULL) {
        write(2, "Problem with a memory allocation(2)\n", 36);
        return NULL;
    }
    for (; str[i]; i++) {
        for (; str[i] && (str[i] == c || str[i] == ' ' || str[i] == '\t'); i++);
        ret[j++] = get_word(&str[i], &i, c);
    }
    ret[j] = NULL;
    return ret;
}
