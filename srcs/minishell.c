/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 17:04:44 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	char	*line;
	t_env	*environnement;

	environnement = opening(argc, argv, envp);
	if (!environnement)
		return (42);
	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		if (!line)
			break ;
		free(line);
	}
	ftbuiltin_export(environnement, "FORTNITE=1234");
	ftbuiltin_env(environnement);
	closing_the_program(environnement);
	return (RETURNVAL);
}
