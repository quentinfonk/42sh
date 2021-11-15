/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** suicide is good
*/

#include "minishell.h"
#include <string.h>
#include <sys/ioctl.h>

int ctrl_l(line_t *line)
{
    struct winsize window;

    if (line->ch == 12) {
        printf("\e[1;1H\e[2J");
        fflush(stdout);
        write(1, "\r", 1);
        ioctl(1, TIOCGWINSZ, &window);
        for (int i = 0; i < window.ws_col; i++)
            write(1, " ", 1);
        prompt(NULL);
        return 0;
    }
    return 1;
}

int backspace(line_t *line)
{
    if (line->ch == 127 && line->str[0] != 0) {
        for (int i = line->cursor - 1; line->str[i] != 0; i++)
            line->str[i] = line->str[i + 1];
        line->cursor -= 1;
        if (line->cursor < 0)
            line->cursor = 0;
        return 0;
    }
    return 84;
}

int up_arrow(line_t *line)
{
    if (line->last_chars[0] == 27 && line->last_chars[1] == '['
        && line->last_chars[2] == 'A') {
        free(line->str);
        line->str = strdup(line->current->cmd);
        if (line->current->prev != NULL)
            line->current = line->current->prev;
        line->cursor = strlen(line->str);
        return 0;
    }
    return 84;
}

int down_arrow(line_t *line)
{
    if (line->last_chars[0] == 27 && line->last_chars[1] == '['
        && line->last_chars[2] == 'B') {
        free(line->str);
        line->str = strdup(line->current->cmd);
        if (line->current->next != NULL)
            line->current = line->current->next;
        line->cursor = strlen(line->str);
        return 0;
    }
    return 84;
}

int left_arrow(line_t *line)
{
    if (line->last_chars[0] == 27 && line->last_chars[1] == '['
        && line->last_chars[2] == 'D') {
        line->str[strlen(line->str) - 1] = 0;
        line->cursor -= 2;
        if (line->cursor < 0)
            line->cursor = 0;
        return 0;
    }
    return 84;
}

int right_arrow(line_t *line)
{
    if (line->last_chars[0] == 27 && line->last_chars[1] == '['
        && line->last_chars[2] == 'C') {
        line->str[strlen(line->str) - 1] = 0;
        return 0;
    }
    return 84;
}
