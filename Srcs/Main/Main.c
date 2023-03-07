/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct S_GLOBAL_MINISHELL S_GLOBAL;

static int ft_read_data(char **command_buff)
{
	*command_buff = readline("minishell-TitouVictor$ ");
	if (!*command_buff)
	{	
		write(2, "exit\n", 5);
		return (1);
	}
	if (ft_strlen(*command_buff) >= 0)
		add_history(*command_buff);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command_buff;
	// char		**args_tab;
	// // char		args_exit[] = "exit 52d";
	t_env_elem	*envp_list;
	t_token	*token_list;
	// t_token	*token_begin;
	t_parser	*parser_list;
	t_parser	*parser_begin;
	int		is_open_simple = 0;
	int		is_open_double = 0;
	(void)envp;
	(void)argc;
	(void)argv;

	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, (__sighandler_t)1);
	while (1)
	{
		if (ft_read_data(&command_buff))
			break ;	
		envp_list = ft_generate_envp_list(envp);
		token_list = ft_generate_token_list(command_buff, &is_open_simple, &is_open_double);
		token_list = ft_clean_quote_token_list(token_list, &is_open_simple, &is_open_double);
		ft_handle_dollar(envp_list, token_list);
		// token_begin = token_list;
		// while (token_begin)
		// {
		// 	printf("Symbol : %d -> ", (int)token_begin->symbol);
		// 	printf("String : %s\n", token_begin->string);
		// 	token_begin = token_begin->next;
		// }
		if (!ft_manage_list_for_redirection(token_list))
			exit(S_GLOBAL.GLOBAL_RETURN);
		parser_list = ft_generate_list_parser(token_list, envp_list);
		parser_begin = parser_list;
		while (parser_begin)
		{
			if (!ft_handle_files(parser_begin))
				return(S_GLOBAL.GLOBAL_RETURN);
			if (parser_begin->parser_type == INFILE || parser_begin->parser_type == OUTFILE_APPEND || parser_begin->parser_type == OUTFILE_TRUNC)
				printf("%s -> fd : %d |", parser_begin->file_name, parser_begin->fd);
			printf("%d | %s\n", (int)parser_begin->parser_type, parser_begin->string);
			parser_begin = parser_begin->next;
		}
		// ft_get_here_doc_traitement(parser_list);
		// printf("fd infile : %d\n", parser_list->fd);
		// args_tab = ft_split(command_buff, ' ');
		// ft_builtin_get_current_directory();
		// ft_builtin_change_directory(&envp_list, args_tab);
		// // ft_builtin_echo_function(args_tab);
	}
	// token_begin = token_list;
	// while (token_begin)
	// {
	// 	printf("Symbol : %d -> ", (int)token_begin->symbol);
	// 	printf("String : %s\n", token_begin->string);
	// 	token_begin = token_begin->next;
	// }
	////////
	// ft_builtin_exit_function(&envp_list, args_tab);
	return (0);
}
