/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** parse commands
*/

#include "minishell.h"
#include <string.h>
#include <sys/ioctl.h>

static int *(*fn[6])(line_t *line) = {
    ctrl_l,
    backspace,
    left_arrow,
    right_arrow,
    up_arrow,
    down_arrow
};

static void init_line_l(line_t *line, history_t **hist)
{
    line->str = malloc(2);
    line->str[0] = 0;
    line->str[1] = 0;
    line->current = *hist;
    line->last_chars[0] = 0;
    line->last_chars[1] = 0;
    line->last_chars[2] = 0;
    line->cursor = 0;
    line->ch = 0;
}

static void my_realloc(line_t *line, int len)
{
    char *ret = malloc(sizeof(char) * (len));
    int i = 0;

    if (ret == NULL)
        exit(84);
    for (; line->str[i]; i++)
        ret[i] = line->str[i];
    ret[i++] = 0;
    ret[i] = 0;
    free(line->str);
    line->str = ret;
}

static void print_line(line_t *line)
{
    struct winsize window;

    write(1, "\r", 1);
    ioctl(1, TIOCGWINSZ, &window);
    for (int i = 0; i < window.ws_col; i++)
        write(1, " ", 1);
    printf("\r↪ %s", line->str);
    fflush(stdout);
    for (int i = strlen(line->str); i > line->cursor; --i)
        write(1, "\b", 1);
}

static void last_chars(char chars[3], char ch)
{
    chars[0] = chars[1];
    chars[1] = chars[2];
    chars[2] = ch;
}

static void add_in_string(char *str, int place, char ch)
{
    for (int i = strlen(str); i > place; i--)
        str[i] = str[i - 1];
    str[place] = ch;
}

static void checking_char(line_t *line)
{
    if (line->last_chars[2] != 91 && line->last_chars[1] != 27
        && line->ch != '\t')
        add_in_string(line->str, line->cursor, line->ch);
    else if (line->ch != '\t')
        line->str[strlen(line->str)] = line->ch;
    line->cursor += 1;
    if ((size_t)line->cursor > strlen(line->str))
        line->cursor = strlen(line->str);
}

static char *get_line(history_t **history)
{
    line_t line;

    init_line_l(&line, history);
    for (int j; line.ch != 10; read(0, &line.ch, 1)) {
        last_chars(line.last_chars, line.ch);
        my_realloc(&line, strlen(line.str) + 2);
        for (j = 0; j < 6 && fn[j](&line) != 0; j++);
        if (j == 6 && line.ch != 127 && line.ch != 12 && line.ch != 27
            && line.ch != 11 && line.ch != 3 && line.ch != 4 && line.ch != 10
            && line.ch != 12)
            checking_char(&line);
        print_line(&line);
    }
    create_file_node(history, strdup(line.str));
    write(1, "\n", 1);
    return line.str;
}

char *get_command(history_t **hist)
{
    if (isatty(0) == 1)
        return get_line(hist);
    else
        return get_next_line(0);
}
