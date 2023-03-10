/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_path(t_env_elem *envp_list)
{
	int			i;
	char		*env_path;
	t_env_elem	*t_begin;

	i = 0;
	t_begin = envp_list;
	if (!envp_list || !t_begin->name)
		return (NULL);
	while (t_begin && ft_strcmp(t_begin->name, "PATH"))
		t_begin = t_begin->next;
	if (t_begin && !ft_strcmp(t_begin->name, "PATH"))
	{
		env_path = ft_strdup(t_begin->value);
		return (env_path);
	}
	else 
		return (NULL);
}

char	*ft_get_command_for_the_pipe(t_exec *exec_elem)
{
	char	*temp;
	char	*command;
	int		i;

	if (!exec_elem || exec_elem->tab_cmd_args[0] == 0)
		return (NULL);
	if (access(exec_elem->tab_cmd_args[0], X_OK) == 0)
		return (exec_elem->tab_cmd_args[0]);
	i = 0;
	while (exec_elem->command_paths && exec_elem->command_paths[i])
	{
		temp = ft_strjoin(exec_elem->command_paths[i], "/");
		command = ft_strjoin(temp, exec_elem->tab_cmd_args[0]);
		free(temp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

int	ft_get_infile(t_exec *exec_elem)
{
	if (exec_elem->infile && exec_elem->infile[0])
	{	
		exec_elem->fd_infile = open(exec_elem->infile, O_RDONLY);
		if (exec_elem->fd_infile < 0)
		{
			ft_message_p_err(exec_elem->infile);
			return (0);
		}
	}
	return (1);
	// else if (exec_elem->delimiter)
		// ft_here_doc_treat;
	// else
		// Comportement sans entree specifique ... quel fd definir ? 
}

int	ft_get_outfile(t_exec *exec_elem)
{
	if (exec_elem->outfile && exec_elem->outfile[0])
	{	
		if (exec_elem->outfile_type == OUT_TRUNC)
			exec_elem->fd_outfile = open(exec_elem->outfile, O_CREAT | O_RDWR | O_TRUNC, 0000664);
		if (exec_elem->outfile_type == OUT_APPEND)
			exec_elem->fd_outfile = open(exec_elem->outfile, O_WRONLY | O_CREAT | O_APPEND, 0000664);
		if (exec_elem->fd_outfile < 0)
		{
			if (exec_elem->fd_infile >= 0)
				close (exec_elem->fd_infile);
			ft_message_p_err(exec_elem->outfile);
			return (0);
		}
	}
	return (1);
	// else
		// Comportement sans sortie specifique ... quel fd definir ? 
}


