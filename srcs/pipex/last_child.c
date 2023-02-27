/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:33:35 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/27 16:34:29 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_child(t_env *environment, int pipefd[2], char **cmds, size_t size)
{
	pid_t	pid;

	if (size > 1)
		close(pipefd[1]);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		if (size > 1)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
	}
	else if (pid == 0)
	{
		if (size > 1)
			dup2(pipefd[0], STDIN_FILENO);
		parse_cmd(environment, cmds, cmds + size - 1, size - 1);
		if (size > 1)
			close(pipefd[0]);
		exit(1);
	}
	else
	{
		waitpid(pid, &g_returnval, 0);
		g_returnval = WEXITSTATUS(g_returnval);
		if (size > 1)
			close(pipefd[0]);
	}
}
