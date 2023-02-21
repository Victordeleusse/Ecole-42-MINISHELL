/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/21 19:22:35 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	char	*line;

	(void) argc;
	(void) argv;
	(void) envp;
	signal_behavior();
	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		if (!line)
			break ;
		free(line);
	}
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
}
