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
	t_env_elem	*envp_list;
	t_token		*token_list;
	t_token		*token_begin;
	// t_parser	*parser_list;
	// t_parser	*parser_begin;
	int		is_open_simple = 0;
	int		is_open_double = 0;
	int		no_step_1 = 0;
	int		no_step_2 = 0;
	(void)envp;
	(void)argc;
	(void)argv;

	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, (__sighandler_t)1);
	while (1)
	{
		no_step_1 = 0;
		no_step_2 = 0;
		is_open_simple = 0;
		is_open_double = 0;
		if (ft_read_data(&command_buff))
			break ;	
		envp_list = ft_generate_envp_list(envp);
		token_list = ft_generate_token_list(command_buff, &is_open_simple, &is_open_double);
		if (!ft_handle_dollar(envp_list, token_list) || !ft_manage_unexpected_tokens(token_list))
			no_step_1 = 1;
		if (!ft_clean_quote_token_list(token_list, &is_open_simple, &is_open_double))
			no_step_2 = 1;
		token_begin = token_list;
		if (token_list && !no_step_1 && !no_step_2)
		{	
			token_begin = token_list;
			while (token_begin)
			{
				printf("type : %d | string : %s\n", token_begin->symbol, token_begin->string);			
				token_begin = token_begin->next;
			}
		}
		printf("\n\n\n\n\n");
		ft_get_cmd_and_args_token(token_list);
		token_begin = token_list;
		if (token_list && !no_step_1 && !no_step_2)
		{	
			token_begin = token_list;
			while (token_begin)
			{
				printf("type : %d | string : %s\n", token_begin->symbol, token_begin->string);			
				token_begin = token_begin->next;
			}
		}
		// parser_list = ft_generate_list_parser(token_list, envp_list);
		// parser_begin = parser_list;
		// while (parser_begin)
		// {
		// 	if (!ft_handle_files(parser_begin))
		// 		break ;
		// 	printf("type : %d | string : %s\n", (int)parser_begin->parser_type, parser_begin->string);			
		// 	parser_begin = parser_begin->next;
		// }
		
		/*
		IMPLEMENTERft_split_parser(parser_begin);
		*/


	}
	return (0);
}




