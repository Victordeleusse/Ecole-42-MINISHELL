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

static void	ft_only_one_exec(t_exec *exec_list)
{
	t_exec	*exec_begin;
	
	exec_begin = exec_list;
	if (exec_list->tab_cmd_args[0] == NULL)
		return ;
	if (!ft_get_infile(exec_begin))
		exec_begin->fd_infile = STDIN_FILENO;
	else
		dup2(exec_begin->fd_infile, STDIN_FILENO);
	if (!ft_get_outfile(exec_begin))
		exec_begin->fd_outfile = STDOUT_FILENO;
	else
		dup2(exec_begin->fd_outfile, STDOUT_FILENO);
	exec_begin->pid = fork();
	if (exec_begin->pid == 0)
		execve(ft_get_command_for_the_pipe(exec_begin), exec_begin->tab_cmd_args + 1, exec_begin->env);
	else 
		exec_begin->tab_pid[0] = exec_begin->pid;
}

void	ft_launch_exec(t_exec *exec_list)
{
	if (!exec_list->next)
		ft_only_one_exec(exec_list);
	while (wait(NULL) != -1)
		;
}

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	// 	if (!ft_get_infile(exec_begin))
	// 		exec_begin->fd_infile = STDIN_FILENO;
	// 	else
	// 		dup2(exec_begin->fd_infile, STDIN_FILENO);
	// 	if (!ft_get_outfile(exec_begin))
	// 		exec_begin->fd_outfile = STDOUT_FILENO;
	// 	else
	// 		dup2(exec_begin->fd_outfile, STDOUT_FILENO);
	// }
	// execve(ft_get_command_for_the_pipe(exec_begin), exec_begin->tab_cmd_args + 1, env);