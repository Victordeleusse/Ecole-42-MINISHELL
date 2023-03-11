NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -MMD
LFLAGS = -LLibft_vde-leus -lft -lreadline

define SRCS :=
	Main/Main.c
	
	Built_in_functions/Env.c
	Built_in_functions/Environment_utils_1.c
	Built_in_functions/Environment_utils_2.c
	Built_in_functions/Export.c
	Built_in_functions/Unset.c
	Built_in_functions/Directory_PWD_CD.c
	Built_in_functions/Exit_and_Free.c
	Built_in_functions/Echo.c

	Parsing_functions/Parsing_Tokens.c
	Parsing_functions/Parsing_Tokens_utils.c
	Parsing_functions/Parsing_Tokens_utils_2.c
	Parsing_functions/Parsing_Tokens_utils_3.c
	Parsing_functions/Handle_Quote.c
	Parsing_functions/Handle_Quote_utils.c
	Parsing_functions/Handle_Quote_utils_2.c
	Parsing_functions/Parsing_Parser.c
	Parsing_functions/Parsing_Parser_utils.c

	Files/Get_simple_files.c
	Files/Here_doc_handler.c
	Files/Handle_files.c

	Execution/Generate_exec_list.c
	Execution/Pipex_utils.c
	Execution/Launch_exec.c
	Execution/Pipe.c

	Signal_Message/Signal.c
	Signal_Message/Message.c
endef

SRCS_PATH = Srcs
OBJS_PATH = Objs

INCLUDES = -I Includes -I Libft_vde-leus

OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
DEPS = $(OBJS:.o=.d)

all: ${NAME}

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
		mkdir -p ${dir $@}
		${CC} ${CFLAGS} -c $< -o $@ $(INCLUDES)

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









### A GERER

# cat >test1 >test2 >test3   | ecrase test1 et test2 - doit les ouvrir en trunc