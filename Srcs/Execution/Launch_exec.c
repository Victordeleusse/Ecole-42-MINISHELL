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

static void	ft_exec_alone(t_exec *exec_elem)
{
	if (!ft_get_infile(exec_elem))
		return ;
	if (exec_elem->fd_here_doc > 0)
	{
		dup2(exec_elem->fd_here_doc, STDIN_FILENO);
		ft_close(&exec_elem->fd_here_doc);
	}
	else
	{	
		dup2(exec_elem->fd_infile, STDIN_FILENO);
		ft_close(&exec_elem->fd_infile);
	}
	if (!ft_get_outfile(exec_elem))
		return ;
	else
	{	
		dup2(exec_elem->fd_outfile, STDOUT_FILENO);
		ft_close(&exec_elem->fd_outfile);
	}
	// dprintf(2, "cmd ==[%s]\n\n", ft_get_command_for_the_pipe(exec_elem));
	execve(ft_get_command_for_the_pipe(exec_elem), exec_elem->tab_cmd_args, exec_elem->env);
	perror(exec_elem->tab_cmd_args[0]);
	exit(1);
}

void	ft_exec(t_exec *exec_elem, t_pipe *pipes)
{
	ft_dup(exec_elem, pipes);
	if (exec_elem->infile_here_doc && exec_elem->fd_here_doc)
		ft_close(&exec_elem->fd_here_doc);
	else if (exec_elem->fd_infile)
		ft_close(&exec_elem->fd_infile);
	ft_close(&exec_elem->fd_outfile);
	ft_close(&pipes[0].fds[0]);
	ft_close(&pipes[0].fds[1]);
	ft_close(&pipes[1].fds[0]);
	ft_close(&pipes[1].fds[1]);
	execve(ft_get_command_for_the_pipe(exec_elem), exec_elem->tab_cmd_args, exec_elem->env);
	perror(exec_elem->tab_cmd_args[0]);
	exit(1);
}

void	ft_make_children(t_exec *exec_elem, t_pipe *pipes)
{
	exec_elem->pid = fork();
	if (exec_elem->pid < 0)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	else if (exec_elem->pid == 0)
		ft_exec(exec_elem, pipes);
}

static void	ft_only_one_exec(t_exec *exec_list)
{
	t_exec	*exec_begin;
	
	exec_begin = exec_list;
	if (!exec_begin->tab_cmd_args[0])
		return ;
	if (ft_is_builtin_func(exec_begin))
		return ;
	// --- JE NE FORK PAS SI 1 CMD BUILTIN ---
	// if (ft_is_builtin(exec_begin->tab_cmd_args[0]))
	// {
	// 	if (!ft_get_infile(exec_begin))
	// 		return ;
	// 	else
	// 		dup2(exec_begin->fd_infile, STDIN_FILENO);
	// 	if (!ft_get_outfile(exec_begin))
	// 		return ;
	// 	else
	// 		dup2(exec_begin->fd_outfile, STDOUT_FILENO);
	// 	ft_exec(exec_begin);
	// 	close(exec_begin->fd_outfile);
	// 	close(exec_begin->fd_infile);
	// 	return
	// }
	exec_begin->pid = fork();
	if (exec_begin->pid < 0)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	if (exec_begin->pid == 0)
		ft_exec_alone(exec_begin);
	if (exec_begin->fd_here_doc)
	{	
		ft_close(&exec_begin->fd_here_doc);
		unlink(exec_begin->infile_here_doc);
	}
	else if (exec_begin->fd_infile)
		ft_close(&exec_begin->fd_infile);
	if (exec_begin->fd_outfile)
		ft_close(&exec_begin->fd_outfile);
	while (wait(NULL) != -1)
		;
}

static void	ft_generate_multi_exec(t_exec *exec_list, t_pipe *pipes)
{
	t_exec *exec_elem;

	exec_elem = exec_list;
	while (exec_elem)
	{
		if (!exec_elem->is_valid || !ft_get_infile(exec_elem) || !ft_get_outfile(exec_elem) || !exec_elem->tab_cmd_args[0])
			exec_elem = exec_elem->next;
		else
		{
			if (exec_elem->next)
			{
				pipe(pipes[1].fds);
				pipes[1].is_open = true;
			}
			ft_make_children(exec_elem, pipes);
			ft_clean_one_pipe(&pipes[1]);
			ft_swap_pipes(pipes);
			if (exec_elem->delimiter && exec_elem->fd_here_doc)
			{	
				ft_close(&exec_elem->fd_here_doc);
				unlink(exec_elem->infile_here_doc);
			}
			else 
				ft_close(&exec_elem->fd_infile);
			ft_close(&exec_elem->fd_outfile);
			exec_elem = exec_elem->next;
		}
	}
	ft_clean_one_pipe(&pipes[0]);
	ft_clean_one_pipe(&pipes[1]);
	while (wait(NULL) != -1)
		;
}

void	ft_launch_exec(t_exec *exec_list, int *nb_cmd)
{
	t_pipe	pipes[2];
	pid_t	*tab_pid;
	t_exec	*exec_begin;

	tab_pid = ft_calloc(sizeof(pid_t), *nb_cmd + 1);
	ft_init_pipes(pipes);
	exec_begin = exec_list;
	if (!exec_begin->next && exec_begin->is_valid)
		ft_only_one_exec(exec_list);
	else if (exec_begin->next)
	  	ft_generate_multi_exec(exec_list, pipes);
}

