##
## EPITECH PROJECT, 2024
## Task01 Makefile
## File description:
## First makefile
##

NAME	 	=		42sh

SRCS		=		$(wildcard src/*.c) \
					$(wildcard ./lib/my/*.c) $(wildcard ./lib/my_malloc/*.c) \
					$(wildcard src/jobs_control/*.c) \
					$(wildcard src/parentese_sys/*.c)

SRCS_BONUS	=		$(wildcard bonus/*.c)

OBJS        =               $(SRCS:.c=.o)

OBJS_BONUS        =               $(SRCS_BONUS:.c=.o)

CFLAGS  	=	-Wall -Wextra -Wno-unused -I ./include

$(NAME)         :               $(OBJS)
				 	gcc -Wall -Wextra -o $(NAME) main.c $(OBJS) $(CFLAGS)

all             :               $(NAME)

clean           :
				rm -f $(OBJS)

fclean          :               clean
				rm -f $(NAME)

unit_tests      :               fclean all
				gcc -o unit_tests $(SRCS) tests/*.c \
				--coverage -lcriterion -I./include

tests_run       :		unit_tests
				./unit_tests
				make clean_test

clean_test		:
				rm -rf unit_tests
				rm -rf *.gcda
				rm -rf *.gcno

re              :               fclean all

val		:
			gcc -o $(NAME) $(SRCS) $(CFLAGS) -g3

run 	:		re
				./$(NAME)

runval	:		val
				valgrind ./$(NAME)

echorun : all
		echo "$(ARG)" | ./$(NAME)

runvalcheck		:	val
				valgrind --leak-check=full ./$(NAME)

tester	:	re
		cp $(NAME) ./tester
		cd tester

bonus		:			$(OBJS) $(OBJS_BONUS)
				gcc -Wall -Wextra -o $(NAME) $(OBJS_BONUS) $(OBJS) $(CFLAGS)
