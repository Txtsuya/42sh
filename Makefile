##
## EPITECH PROJECT, 2024
## Task01 Makefile
## File description:
## First makefile
##

NAME	 	=		mysh


SRCS		=		$(wildcard src/*.c) $(wildcard ./lib/my/*.c) $(wildcard ./lib/my_malloc/*.c)

OBJS            =               $(SRCS:.c=.o)

$(NAME)         :               $(OBJS)
				 	gcc -o $(NAME) $(OBJS) $(CFLAGS)

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

val		:		$(OBJS)
			gcc -o $(NAME) $(OBJS) $(CFLAGS) -g3

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
