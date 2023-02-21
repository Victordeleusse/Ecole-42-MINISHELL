/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/21 19:37:21 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_signal_ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_get_data(void)
{
	char	*command_buff;
	
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, (__sighandler_t)1);
	while (1)
	{
		command_buff = readline("minishell-TitouVictor$ ");
		if (!command_buff)
			break;
		if (ft_strlen(command_buff) >= 0)
		{	
			add_history(command_buff);
			free(command_buff);
		}
	}
}

int	main(void)
{
	ft_get_data();
	return (0);
}