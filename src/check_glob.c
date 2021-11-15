/*
** EPITECH PROJECT, 2020
** check_glob
** File description:
** check_glob
*/

#include "minishell.h"
#include <dirent.h>

char *next_str(char *str)
{
    char *stack = malloc(sizeof(char) * (my_strlen(str)));;
    int i = 0;
    int o = 0;

    for (int i = 0; str[i] != '\0'; i++)
        stack[i] = str[i];
    for (i = 0; str[i] != '?' && str[i] != '\0'; i++);
    for (; str[i] != ' ' && i != 0; i--);
    if (str[i] == ' ')
        i++;
    for (; str[i] != ' ' && str[i] != '\0'; i++, o++)
        stack[o] = str[i];
    stack[o] = '\0';
    return (stack);
}

char *check_l(char *stack, char *op)
{
    int i = 0;

    printf("stack = %s\n", stack);
    op = malloc(sizeof(char) * (my_strlen(stack) + 1));
    for (i = 0; stack[i] != '?'; i++)
        op[i] = stack[i];
    for (; stack[i] != '/'; i--);
    op[i] = '\0';
    return (op);
}

char *check_sla(char *stack)
{
    for (int i = 0; stack[i] != '\0'; i++)
        if (stack[i] == '/')
            return (1);
    return (0);
}

char *check_file(char *file, char *stack)
{
    int i = 0;
    int o = 0;

    for (i = 0; file[i] != '\0'; i++)
        if (file[i] == stack[i] || stack[i] == '?')
            o++;
    if (i == o)
        printf("dza %s\n", file);
    return (stack);
}

char *chec_ls(char *stack, DIR *rep)
{
    struct dirent *fichier = readdir(rep);
    int i = my_strlen(stack);
    int a = 0;

    while (fichier != NULL) {
        check_file(fichier->d_name, stack);
        printf("a = %s\n", fichier->d_name);
        fichier = readdir(rep);
    }
    return (stack);
}

char *cha_st(char *stack)
{
    char *str = stack;
    int i = 0;

    for (i = 0; stack[i] != '?'; i++);
    for (; stack[i] != '/'; i--);
    for (;stack[i] != '\0'; i++);
}

char *check_all(char *str, char *stack)
{
    char *op = NULL;
    DIR *rep;

    if (check_sla(stack) == 1) {
        op = check_l(stack, op);
        stack = cha_st(stack);
    }
    if (op != NULL) {
        if (rep = opendir(op))
            return (NULL);
    }
    else
        rep = opendir(".");
    return (chec_ls(stack, rep));
}

char *change_int(char *str)
{
    char *stack = next_str(str);
    char *stock = malloc(sizeof(char) * (my_strlen(str)));
    int i = 0;

    for (i = 0; str[i] != '\0'; i++)
        stock[i] = str[i];
    stock[i] = '\0';
    str = check_all(str, stack);
    printf("str = %s\n", str);
    if (str == NULL) {
        printf("ERREUR\n");
        return (stock);
    }
    return (stack);
}

char *change_star(char *str)
{
    return str;
}

char *check_glob(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*')
            str = change_star(str);
        if (str[i] == '?')
            str = change_int(str);
    }
    return (str);
}
