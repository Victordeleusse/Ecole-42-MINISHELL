/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/23 15:32:59 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	char	*line;
	t_env	*environment;

	environment = opening(argc, argv, envp);
	if (!environment)
		return (42);
	while (1)
	{
		line = readline(BLUE PROMPT ENDCL " ");
		if (line && *line)
			add_history(line);
		if (!line)
			break ;
		parsing(environment, &line);
		if (line)
			free(line);
	}
	closing_the_program(environment);
	return (g_returnval);
}
