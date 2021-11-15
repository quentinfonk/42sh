/*
** EPITECH PROJECT, 2020
** test
** File description:
** var_interpret
*/

#include "minishell.h"
#include <string.h>

int c(char *str, char *cmp)
{
    int a = strlen(str);
    int b = strlen(cmp);

    if (a < b)
        return 0;
    else if (a > b)
        return 1;
    else
        return 1;
}

char **check_var_env(char **temp, char **args)
{
    char *str = malloc(sizeof(char) * 2);
    char *final = NULL;
    int size = 0;

    str[0] = '$';
    str[1] = '\0';
    size = (strlen(str) - 1);
    str = m_strcat(str, temp[0]);
    for (int i = 0; args[i] != NULL; i++)
        for (int j = 0; (c(args[i], str) == 1) && args[i][j + size] != 0; j++)
            if (args[i][j] == '$') {
                final = get_var(args[i], j, str, temp);
                args[i] = final;
            }
    free(str);
    return args;
}

char **var_interpreter(char **args, env_t *env)
{
    char **temp = NULL;
    int var = 0;
    env_t *save_env = env;

    if ((var = get_inter(args) == 0))
        return args;
    while (save_env->next != NULL) {
        temp = my_str_to_array(save_env->name, '=');
        if ((args = check_var_env(temp, args)))
            var -= 1;
        save_env = save_env->next;
    }
    return args;
}
