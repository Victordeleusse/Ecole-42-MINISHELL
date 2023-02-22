SRCS = Main.c Signal.c Environment/Environment.c Environment/Utils_Environment.c 
 
OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

EXEC = minishell

LIBFT_PATH = -I Libft_vde-leus -L Libft_vde-leus -lft -lreadline

CC = cc
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra

%.o: %.c 
			${CC} -I. ${LIBFT_PATH} -MMD -c $< -o ${<:.c=.o}

all: run

run: ${OBJS}
		$(MAKE) -C Libft_vde-leus/ all
		clear
		@ $(CC) -o ${EXEC} $(CFLAGS) ${OBJS} ${LIBFT_PATH}

clean:	
		rm -f ${OBJS} ${DEPS}
		$(MAKE) -C Libft_vde-leus/ clean
		clear

fclean:	clean
		$(MAKE) -C Libft_vde-leus/ fclean
		rm -f ${EXEC}
		clear


-include $(DEPS) $(DEPS_BONUS)

re:	fclean all

.PHONY: clean fclean re bonus run