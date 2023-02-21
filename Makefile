SRCS =	${wildcard srcs/*.c}

OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

INC = -I inc/ -I libft/
LIBS = -L libft -lft -lreadline ${INC}

NAME = minishell
CC = cc
CFLAGS =  -Wall -Wextra -Werror 

.c.o:
		${CC} ${CFLAGS} ${INC} -g -MMD -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} 
		cc -o ${NAME} ${CFLAGS} ${OBJS} ${LIBS}

all:	${NAME}

valgrind:
		valgrind --suppressions=ignore_readline_leaks.supp ./minishell

clean:	
	@	rm -f ${OBJS} ${DEPS}

fclean:	clean;
	@	rm -f ${NAME}

re:	fclean all

-include ${DEPS}