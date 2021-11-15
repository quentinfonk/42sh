/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** str functions (strcmp, strcat etc.)
*/

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *clean_str(char *str)
{
    int buf = my_strlen(str);
    char *ret = malloc(sizeof(char) * (buf + 1));
    int i = 0;
    int c = 0;

    for (; str[i] && (str[i] == ' ' || str[i] == '\t'); i++);
    for (; str[i]; i++) {
        if (str[i] != '\t')
            ret[c++] = str[i];
        else
            ret[c++] = ' ';
        if ((str[i] && (str[i] == ' ' || str[i] == '\t'))) {
            for (; str[i] && (str[i] == ' ' || str[i] == '\t'); i++);
            i -= 1;
        }
    }
    if (ret[c - 1] == ' ' || ret[c - 1] == '\t')
        ret[c - 1] = 0;
    ret[c] = 0;
    free(str);
    return ret;
}

static int create_redir(char *file, int opt, int std)
{
    int fd = 0;

    if ((fd = open(file, opt, 0644)) == -1) {
        if (std == 0) {
            my_putstr(file);
            my_putstr(": No such file or directory.\n");
	}
        exit(0);
    }
    if (dup2(fd, std) == -1)
        return 84;
    return 0;
}

static char **modify_args(char **args, int red)
{
    int count = 0;
    char **ret;

    for (int i = 0; args[i] != NULL; i++)
        if (i != red && i != red + 1)
            count += 1;
    ret = malloc(sizeof(char *) * (count + 1));
    ret[count] = NULL;
    count = 0;
    for (int i = 0; args[i]; i++)
        if (i != red && i != red + 1)
            ret[count++] = args[i];
    for (int i = 0; args[i] != NULL; i++)
        if (i == red && i == red + 1)
            free(args[i]);
    return ret;
}

char **check_for_redir(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (args[i][0] == '<') {
            if (create_redir(args[i + 1], O_RDONLY, 0) == 0) {
                args = modify_args(args, i);
                i = 0;
            }
        }
        else if (args[i][0] == '>' && args[i][1] == 0) {
            if (create_redir(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 1) == 0) {
                args = modify_args(args, i);
                i = 0;
            }
        }
        if (my_strlen(args[i]) == 2 && my_strcmp(args[i], ">>=") == 0) {
            if (create_redir(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 1) == 0){
                args = modify_args(args, i);
                i = 0;
            }
        }
    }
    return args;
}
