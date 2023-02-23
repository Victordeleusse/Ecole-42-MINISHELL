# SRCS =	minishell.c opening.c closing.c signal.c parsing.c
# SRCS +=	environment.c env_lstaddback.c
# SRCS +=	ftbuiltin_export.c ftbuiltin_unset.c ftbuiltin_env.c ftbuiltin_exit.c

# SRCS_PATH = srcs/
# OBJS_PATH = objs/
# OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}

INC = -I inc/ -I libft/
LIBS = -L libft -lft -lreadline

CFLAGS =  -Wall -Wextra -Werror 
# CFLAGS =  -g
# NAME = minishell
# CC = cc

# vpath %.c ${SRCS_PATH}

# ${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile ./inc/minishell.h 
# 		mkdir -p ${OBJS_PATH}
# 		${CC} ${CFLAGS} ${INC} -c $< -o $@ 

# ${NAME}:	${SRCS} ${OBJS}
# 		+$(MAKE) -C libft
# 		cc -o ${NAME} ${CFLAGS} ${OBJS} ${LIBS} ${INC}

# all:	${NAME}

all:	
		+$(MAKE) -C libft
		cc -o minishell -g ${CFLAGS} srcs/*.c ${INC} ${LIBS}

run:	all
		clear
	@	./minishell

valgrind:	all
			clear
			valgrind --suppressions=ignore_readline_leaks.supp --leak-check=full --show-leak-kinds=all ./minishell
#			valgrind --suppressions=ignore_readline_leaks.supp --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

# clean:	
# 	@	+$(MAKE) -C libft clean
# 	@	rm -f ${OBJS}

# fclean:	clean;
# 	@	+$(MAKE) -C libft fclean
# 	@	rm -f ${NAME}

# re:	fclean all
