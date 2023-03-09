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
	if (*command_buff)
		add_history(*command_buff);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command_buff;
	t_env_elem	*envp_list;
	t_token		*token_list;
	t_parser	*parser_list;
	// t_parser	*parser_begin;
	t_exec		*exec_list;
	t_exec		*exec_begin;
	int		is_open_simple = 0;
	int		is_open_double = 0;
	int		i;
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
		if (!ft_strlen(command_buff))
			;
		else
		{
			envp_list = ft_generate_envp_list(envp);
			token_list = ft_generate_token_list(command_buff, &is_open_simple, &is_open_double);
			if (!ft_handle_dollar(envp_list, token_list) || !ft_manage_unexpected_tokens(token_list))
				;
			else if (!ft_clean_quote_token_list(token_list, &is_open_simple, &is_open_double))
				;
			else 
			{
				if (token_list)
				{
					ft_get_cmd_and_args_token(token_list);
					printf("\n\nPARSER\n");
					parser_list = ft_generate_list_parser(token_list, envp_list);
					if (!ft_ordonate_parser_list(parser_list))
						;
					// parser_begin = parser_list;
					// while (parser_begin)
					// {
					// 	if (parser_begin->parser_type == INFILE || parser_begin->parser_type == OUTFILE_APPEND || parser_begin->parser_type == OUTFILE_TRUNC)
					// 		printf("file name : %s -- is for exec ? : IN %d | OUT %d ", parser_begin->file_name, parser_begin->is_infile_exec, parser_begin->is_outfile_exec);			
					// 	if (parser_begin->parser_type ==  HERE_DOC)
					// 		printf("DELIMITER : %s -- ", parser_begin->delimiter);		
					// 	if (parser_begin->parser_type ==  0)
					// 		printf("CMD ? %d vs. ARG ? %d  ", parser_begin->is_cmd, parser_begin->is_arg);		
					// 	printf("type : %d | string : %s\n", (int)parser_begin->parser_type, parser_begin->string);			
					// 	parser_begin = parser_begin->next;
					// }
					exec_list = ft_generate_exec_list(envp_list, parser_list);
					exec_begin = exec_list;
					while (exec_begin)
					{
						i = 0;
						while (exec_begin->tab_cmd_args[i])
						{
							printf("command ou arg : %s\n", exec_begin->tab_cmd_args[i]);
							printf("infile %s & outfile %s\n", exec_begin->infile, exec_begin->outfile);
							i++;
						}
						printf("is a valid bloc : %d\n", exec_begin->is_valid);
						exec_begin = exec_begin->next;
						printf("\nNEW BLOC\n");
					}
				}
			}
		}
		
		/*
		IMPLEMENTERft_split_parser(parser_begin);
		*/


	}
	return (0);
}




