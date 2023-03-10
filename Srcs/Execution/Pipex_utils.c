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
	// else if (exec_elem->delimiter)
		// ft_here_doc_treat;
	// else
		// Comportement sans entree specifique ... quel fd definir ? 
}