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
		;
	else
	{	
		dup2(exec_elem->fd_infile, STDIN_FILENO);
		ft_close(&exec_elem->fd_infile);
	}
	if (!ft_get_outfile(exec_elem))
		;
	else
	{	
		dup2(exec_elem->fd_outfile, STDOUT_FILENO);
		ft_close(&exec_elem->fd_outfile);
	}
	dprintf(2, "cmd ==[%s]\n", ft_get_command_for_the_pipe(exec_elem));
	execve(ft_get_command_for_the_pipe(exec_elem), exec_elem->tab_cmd_args + 1, exec_elem->env);
	perror(exec_elem->tab_cmd_args[0]);
	exit(1);
}

void	ft_exec(t_exec *exec_elem, t_pipe *pipes)
{
	ft_dup(exec_elem, pipes);
	ft_close(&exec_elem->fd_infile);
	ft_close(&exec_elem->fd_outfile);
	ft_close(&pipes[0].fds[0]);
	ft_close(&pipes[0].fds[1]);
	// dprintf(2, "cmd ==[%s]\n", ft_get_command_for_the_pipe(exec_elem));
	execve(ft_get_command_for_the_pipe(exec_elem), exec_elem->tab_cmd_args + 1, exec_elem->env);
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
	{
		dprintf(2, "cmd ==[%d]\n", exec_elem->index);
		if (!ft_get_infile(exec_elem))
			;
		if (!ft_get_outfile(exec_elem))
			;
		// if (!exec_elem->is_valid)
		// {
		// 	ft_clean_one_pipe(&pipes[0]);
		// 	ft_clean_one_pipe(&pipes[1]);
		// 	if (exec_elem->fd_infile > 0)
		// 		ft_close(&exec_elem->fd_infile);
		// 	if (exec_elem->fd_outfile > 0)
		// 		ft_close(&exec_elem->fd_outfile);
		// 	// exit (1);
		// }
		ft_exec(exec_elem, pipes);
	}
}

static void	ft_only_one_exec(t_exec *exec_list)
{
	t_exec	*exec_begin;
	
	exec_begin = exec_list;
	if (!ft_get_infile(exec_begin))
		return ;
	if (!ft_get_outfile(exec_begin))
		return ;
	if (!exec_begin->tab_cmd_args[0])
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
	while (wait(NULL) != -1)
		;
}

// static void	ft_generate_multi_exec(t_exec *exec_list, t_pipe *pipes)
// {
// 	t_exec *exec_elem;

// 	exec_elem = exec_list;
// 	while (exec_elem)
// 	{
// 		if (exec_elem->next)
// 		{
// 			pipe(pipes[0].fds);
// 			pipes[0].is_open = true;
// 		}
// 		ft_swap_pipes(pipes);
// 		ft_make_children(exec_elem, pipes);
// 		dprintf(2, "cmd theorique ==[%s]\n", ft_get_command_for_the_pipe(exec_elem));
// 		ft_clean_one_pipe(&pipes[0]);
// 		exec_elem = exec_elem->next;
// 	}
// }

void	ft_launch_exec(t_exec *exec_list, int *nb_cmd)
{
	t_pipe	pipes[2];
	pid_t	*tab_pid;
	t_exec	*exec_begin;

	tab_pid = ft_calloc(sizeof(pid_t), *nb_cmd + 1);
	ft_init_pipes(pipes);
	exec_begin = exec_list;
	// while (exec_begin)
	// {
	// 	dprintf(2, "is valid ? %d / commande : %s / infile : %s fd_infile : %d || outfile : %s fd_outfile : %d / delimiter : %s \n", exec_begin->is_valid, exec_begin->tab_cmd_args[0], exec_begin->infile, exec_begin->fd_infile, exec_begin->outfile, exec_begin->fd_outfile, exec_begin->delimiter);
	// 	exec_begin = exec_begin->next;
	// }
	if (!exec_begin->next)
	 	ft_only_one_exec(exec_list);
	// else
	// 	ft_generate_multi_exec(exec_list, pipes);
	// while (wait(NULL) != -1)
	// 	;
	// printf("EXECUTIONS FAITES\n\n");
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