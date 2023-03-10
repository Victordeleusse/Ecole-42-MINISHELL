/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_launch_exec(t_exec *exec_list)
{
	int		status;
	int		fds1[2];
	int		fds2[2];
	t_pipe	pipe1;
	t_pipe	pipe2;
	t_exec	*exec_begin;
	char	**env;

	status = -1;
	pipe1.fds = fds1;
	pipe2.fds = fds2;
	pipe(pipe1.fds);
	pipe(pipe2.fds);
	env = ft_envp_in_tab(&exec_list->envp_list);
	exec_begin = exec_list;
	while (exec_begin)
	{

	}
	if (!exec_begin->next)
	{
		if (!ft_get_infile(exec_begin))
			exec_begin->fd_infile = STDIN_FILENO;
		else
			dup2(exec_begin->fd_infile, STDIN_FILENO);
		if (!ft_get_outfile(exec_begin))
			exec_begin->fd_outfile = STDOUT_FILENO;
		else
			dup2(exec_begin->fd_outfile, STDOUT_FILENO);
	}
	execve(ft_get_command_for_the_pipe(exec_begin), exec_begin->tab_cmd_args + 1, env);
}
