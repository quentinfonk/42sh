/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** main
*/

#include "minishell.h"
#include "string.h"
#include <sys/ioctl.h>
#include <termios.h>

static char *last_path(char *str)
{
    if (str == NULL)
        return NULL;
    for (int j = my_strlen(str); j != 0; j--)
        if (str[j] == '/')
            return str + j + 1;
    return str;
}

void prompt(env_t *env)
{
    static char *user = NULL;
    char *path = getcwd(NULL, 0);

    if (user == NULL)
        user = env_search(env, "USER");
    if (isatty(0) != 1) {
        free(path);
        return;
    }
    if (user)
        printf("\e[0;32m%s", user);
    if (path) {
        printf("\e[0;37m in \e[0;35m%s", last_path(path));
    }
    printf("\033[1m\033[37m > \033[0m\n↪ ");
    fflush(stdout);
    free(path);
}

static int minishell(env_t *env, char *cmd)
{
    char **commands = my_str_to_array(cmd, ';');
    char *error = NULL;

    for (int i = 0; commands[i]; i++) {
        commands[i] = clean_str(commands[i]);
        if (strcmp(commands[i], "exit") == 0) {
            my_putstr("exit\n");
            return 84;
        }
    }
    commands = var_interpreter(commands, env);
    for (int i = 0; commands[i] != NULL; i++) {
        commands[i] = get_blog(commands[i]);
        error = execute_commands(commands[i], env);
        if (error != NULL)
            write(2, error, my_strlen(error));
    }
    for (int i = 0; commands[i] != NULL; i++)
        free(commands[i]);
    return 0;
}

static void ctrl_c(int signo)
{
    if (signo == SIGINT) {
        printf("\n");
        prompt(NULL);
    }
}

static void handle_signal_and_term(struct termios *old_term)
{
    struct termios raw_term;

    if (isatty(0) == 1) {
        signal(SIGINT, ctrl_c);
        ioctl(0, TCGETS, old_term);
        ioctl(0, TCGETS, &raw_term);
        raw_term.c_lflag &= ~(ICANON | ECHO);
        ioctl(0, TCSETS, &raw_term);
    }
}

static void write_history(history_t *history)
{
    FILE *fp = fopen (".history","w");

    if (fp == NULL)
        return;
    for (; history->prev != NULL; history = history->prev);
    for (; history != NULL; history = history->next)
        fprintf (fp, "%s\n", history->cmd);
    fclose (fp);

}

int main(int ac, char **av, char **envp)
{
    env_t *env = NULL;
    char *cmd;
    struct termios old_term;
    history_t *history = get_history();

    env = init_env(envp);
    handle_signal_and_term(&old_term);
    if (isatty(0) == 1)
        prompt(env);
    while ((cmd = get_command(&history))) {
        cmd = clean_str(cmd);
        if (minishell(env, cmd) == 84)
            break;
        if (isatty(0) == 1)
            prompt(env);
        free(cmd);
    }
    ioctl(0, TCSETS, &old_term);
    write_history(history);
    return 0;
}
