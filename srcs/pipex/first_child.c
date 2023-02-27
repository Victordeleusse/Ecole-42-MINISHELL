/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:33:35 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/27 16:34:07 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_child(t_env *environment, int pipefd[2], char **cmds)
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("minishell: pipe"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), 0);
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		parse_cmd(environment, cmds, cmds, 0);
		close(pipefd[1]);
		exit(1);
	}
	return (1);
}
