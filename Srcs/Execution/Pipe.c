/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_pipes(t_pipe *pipes)
{
	pipes[0].is_open = false;
	pipes[0].fds[0] = -1;
	pipes[0].fds[1] = -1;
	pipes[1].is_open = false;
	pipes[1].fds[0] = -1;
	pipes[1].fds[1] = -1;
}

void	ft_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	ft_swap_pipes(t_pipe *pipes)
{
	t_pipe	tmp;

	tmp = pipes[0];
	pipes[0] = pipes[1];
	pipes[1] = tmp;
}

void	ft_clean_one_pipe(t_pipe *pipe)
{
	if (pipe->fds[0] != -1)
		ft_close(&pipe->fds[0]);
	if (pipe->fds[1] != -1)
		ft_close(&pipe->fds[1]);
	pipe->is_open = false;
}

void	ft_dup(t_exec *exec_elem, t_pipe *pipes)
{
	if (exec_elem->fd_here_doc > 0)
		dup2(exec_elem->fd_here_doc, STDIN_FILENO);
	else if (exec_elem->fd_infile > 0)
		dup2(exec_elem->fd_infile, STDIN_FILENO);
	else if (pipes[0].is_open)
		dup2(pipes[0].fds[0], STDIN_FILENO);
	if (exec_elem->fd_outfile > 0)
		dup2(exec_elem->fd_outfile, STDOUT_FILENO);
	else if (pipes[1].is_open)
		dup2(pipes[1].fds[1], STDOUT_FILENO);
}
