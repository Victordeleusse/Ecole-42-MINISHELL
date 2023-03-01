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

// static int ft_read_data(char **command_buff)
// {
// 	*command_buff = readline("minishell-TitouVictor$ ");
// 	if (!*command_buff)
// 	{	
// 		write(2, "exit\n", 5);
// 		return (1);
// 	}
// 	if (ft_strlen(*command_buff) >= 0)
// 		add_history(*command_buff);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	// char		*command_buff;
	// char		**args_tab;
	// char		args_exit[] = "exit 52d";
	// t_env_elem	*envp_list;
	t_token	*token_list;
	t_token	*token_begin;
	int		is_open_simple = 0;
	int		is_open_double = 0;
	char	str_pars[] = "< Makefile cat | \" wc -l > out ls -la a << b | c \" > d";
	(void)envp;
	(void)argc;
	(void)argv;

	token_list = ft_generate_token_list(str_pars, &is_open_simple, &is_open_double);
	token_list = ft_clean_quote_token_list(token_list, &is_open_simple, &is_open_double);
	if (!token_list)
	{
		fprintf(stderr, "PROBLEME PARCING DETECTE\n");
		return (S_GLOBAL.GLOBAL_RETURN);
	}
	token_begin = token_list;
	while (token_begin)
	{
		if (token_begin->is_symbol)
			printf("Symbol : %d -> ", token_begin->symbol);
		// if (!token_begin->is_symbol)
		printf("String : %s\n", token_begin->string);
		token_begin = token_begin->next;
	}
	// envp_list = ft_generate_envp_list(envp);
	// args_tab = ft_split(args_exit, ' ');
	// ft_builtin_exit_function(&envp_list, args_tab);
	// signal(SIGINT, ft_signal_ctrl_c);
	// signal(SIGQUIT, (__sighandler_t)1);
	// while (1)
	// {
	// 	if (ft_read_data(&command_buff))
	// 		break ;
		
	// }
	return (0);
}
