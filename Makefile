NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -MMD
LFLAGS = -LLibft_vde-leus -lft -lreadline

# define SRCS :=
# 	Environment/Environment.c
# 	Environment/Export.c
# 	Environment/Utils_Environment.c
# 
# 	Signal_Message/Signal.c
# 	Signal_Message/Message.c
# 
# 	Main/Main.c
# endef
SRCS := $(shell find Environment Signal_Message Main -name '*.c' -type f)

OBJS_PATH = objs

INCLUDES = Includes Libft_vde-leus

#vpath %.c ${SRCS_PATH}
#vpath %.h ${HEADER_PATH} 
# *.h -> 
OBJS = ${patsubst %.c,${OBJS_PATH}/%.o, ${SRCS}}
DEPS = $(OBJS:.o=.d)

all: ${NAME}

$(OBJS_PATH)/%.o: %.c
		mkdir -p ${dir $@}
		${CC} ${CFLAGS} -c $< -o $@ ${addprefix -I ,$(INCLUDES)}

${NAME}: ${OBJS}
		$(MAKE) -C Libft_vde-leus/ all
		$(CC) -o $(NAME) ${OBJS} $(LFLAGS)

clean:	
		rm -rf $(OBJS_PATH)
		$(MAKE) -C Libft_vde-leus/ clean
		clear

fclean:	clean
		$(MAKE) -C Libft_vde-leus/ fclean
		rm -f ${NAME}
		clear

re:	fclean all

.PHONY: clean fclean re 

-include $(DEPS)