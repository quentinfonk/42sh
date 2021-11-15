/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_execve
*/

#include "minishell.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static char **list_to_array(env_t *env)
{
    int i = 1;
    char **ret;

    if (env == NULL)
        return NULL;
    for (env_t *tmp = env; tmp; tmp = tmp->next)
        i++;
    ret = malloc(sizeof(char *) * (i + 1));
    i = 0;
    for (env_t *tmp = env; tmp; tmp = tmp->next) {
        if (tmp->name[0] == '.')
            continue;
        ret[i++] = tmp->name;
    }
    ret[i] = NULL;
    return ret;
}

static char *find_filename(char *cmd, char *pathh)
{
    char **path = my_str_to_array(pathh, ':');
    char *ret;
    char *buf;

    if (access(cmd, F_OK | X_OK) == 0)
        return cmd;
    for (int i = 0; path[i] != NULL; i++) {
        buf = my_strcat(path[i], "/");
        ret = my_strcat(buf, cmd);
        if (access(ret, F_OK | X_OK) == 0)
            return ret;
        free(ret);
        free(buf);
    }
    return NULL;
}

static void segfault(char *str)
{
    int status = 0;
    int value;

    if (job_tab[BACKGROUND] == false) {
        if (wait(&status) == -1) {
            seg_fault(str);
            exit(1);
        }
    }
    if (WIFSIGNALED(status)) {
        value = WTERMSIG(status);
        if (value == 11)
            my_putstr("Segmentation fault");
        else if (value == 6)
            my_putstr("Abort");
        if (value == 8)
            my_putstr("Floating exception");
        if (WCOREDUMP(status))
            my_putstr(" (core dumped)");
        my_putstr("\n");
    }
}

static void parent_process(pid_t pid, int pipe, int pd[2], char *str)
{
    if (job_tab[BACKGROUND] == true)
        job_write(pid);
    if (pipe != 0) {
        if (pipe == 1)
            dup2(pd[0], 0);
        close(pd[1]);
        close(pd[0]);
    }
    segfault(str);
}

void my_exec(char **args, env_t *env, int pd[2], int pipe)
{
    char **envp = list_to_array(env);
    char *filename;
    pid_t pid;

    if ((filename = find_filename(args[0], env_search(env, "PATH"))) == NULL
        || envp == NULL) {
        write(2, args[0], my_strlen(args[0]));
        write(2, ": Command not found.\n", 21);
        return;
    }
    if ((pid = fork()) == 0) {
        if (pipe == 1)
            dup2(pd[1], 1);
        args = check_for_redir(args);
        args = check_quote(args, '"');
        args = check_quote(args, '\'');
        if (execve(filename, args, envp) == -1)
            bin_not_compatible(args);
    }
    parent_process(pid, pipe, pd, filename);
}
