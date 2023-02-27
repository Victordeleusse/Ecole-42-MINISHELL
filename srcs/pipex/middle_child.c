/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:33:35 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/27 18:01:26 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	middle_child(t_env *environment, int pipefd[2], char **cmds, size_t cmdnbr)
{
	pid_t	pid;
	int		new_pipefd[2];
	char	**args;

	close(pipefd[1]);
	args = parse_cmd(environment, cmds + cmdnbr);
	if (!args)
		return ;
	if (pipe(new_pipefd) == -1)
		return (perror("minishell: pipe"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), \
		close(pipefd[0]), close(pipefd[1]), 0);
	else if (pid == 0)
	{
		close(new_pipefd[0]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(new_pipefd[1], STDOUT_FILENO);
		parse_cmd(environment, cmds + cmdnbr);
		close(pipefd[0]);
		close(new_pipefd[1]);
		exit(1);
	}
	else
	{
		close(pipefd[0]);
		pipefd[0] = new_pipefd[0];
		pipefd[1] = new_pipefd[1];
	}
	return (1);
}
