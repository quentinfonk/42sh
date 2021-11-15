##
## EPITECH PROJECT, 2020
## CPE_duostumper_1_2019
## File description:
## Makefile for creating the binary
##

########## FILES #########
SRC 		=	src/function.c		\
			src/init_list_env.c	\
			src/minishell.c		\
			src/my_exec.c		\
			src/my_str_to_array.c	\
			src/str_func.c		\
			src/my_setenv.c		\
			src/my_unsetenv.c	\
			src/check_quote.c	\
			src/get_quote.c		\
			src/check_error_quote.c	\
			src/var_interpreter.c	\
			src/var_interpreter_2.c	\
			src/my_cat.c		\
			src/globbing.c		\
			src/my_cd.c		\
			src/job_control.c	\
			src/job_print.c		\
			src/error_handling.c	\
			src/get_line.c		\
			src/ptr_func.c		\
			src/get_history.c
MAIN		= 	main.c
OBJ		=	$(SRC:.c=.o) $(MAIN:.c=.o)
##########################

########## FLAGS #########
UTFLAGS		=	-lcriterion --coverage
CFLAGS		=	-Wall -Wextra -g3
CPPFLAGS	=	-I include
LIB		=	lib/libgnl
##########################

########## BINARY ########
CC		=	gcc
NAME		=	42sh
TEST_NAME	=	unit_test
DEL		=	rm -rf
##########################

.PHONY: all
all: $(NAME)
$(NAME): $(OBJ)
	cp lib/libgnl libgnl.a
	$(CC) -o $(NAME) $(OBJ) libgnl.a

.PHONY: tests_run
tests_run:
	$(CC) -o $(TEST_NAME) $(SRC) $(TESTS) $(UTFLAGS) $(CPPFLAGS)
	./$(TEST_NAME)
	gcovr -b --exclude tests/
	gcovr -r . --exclude tests/

.PHONY: debug
debug: CFLAGS += -g3
debug: $(NAME)

.PHONY: clean
clean:
	$(DEL) $(OBJ) libgnl.a

.PHONY: fclean
fclean: clean
	$(DEL) $(NAME)
	$(DEL) $(TEST_NAME)

.PHONY: re
re:	fclean all
