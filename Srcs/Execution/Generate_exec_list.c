/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generate_exec_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*ft_generate_executable(t_env_elem *envp_list, t_parser *parser_list)
{
	t_exec		*exec_elem;
	t_parser	*parser_begin;
	int			size_tab;
	int			i;

	exec_elem = ft_calloc(sizeof(t_exec), 1);
	exec_elem->index = 0;
	exec_elem->fd_here_doc = -1;
	exec_elem->delimiter = NULL;
	exec_elem->is_a_quote_delimiter = -1;
	exec_elem->is_valid = 1;
	exec_elem->previous_valid = 1;
	exec_elem->infile = NULL;
	exec_elem->fd_infile = -1;
	exec_elem->outfile = NULL;
	exec_elem->fd_outfile = -1;
	exec_elem->env = ft_envp_in_tab(&envp_list);
	exec_elem->env_path = ft_get_env_path(envp_list);
	exec_elem->command_paths = ft_split(exec_elem->env_path, ':');
	parser_begin = parser_list;
	size_tab = 0;
	while (parser_begin && parser_begin->parser_type != PIPE)
	{
		if (parser_begin && parser_begin->parser_type == 0)
			size_tab++;
		if (!ft_handle_files(parser_begin))
			exec_elem->is_valid = 0;
		parser_begin = parser_begin->next;
	}
	exec_elem->tab_cmd_args = ft_calloc(sizeof(char *), size_tab + 1);
	exec_elem->tab_cmd_args[size_tab] = 0;
	parser_begin = parser_list;
	i = 0;
	while (parser_begin && parser_begin->parser_type != PIPE)
	{
		if (parser_begin && parser_begin->parser_type == 0)
		{	
			exec_elem->tab_cmd_args[i] = ft_strdup(parser_begin->string);
			i++;
		}
		parser_begin = parser_begin->next;
	}
	parser_begin = parser_list;
	while (parser_begin && parser_begin->parser_type != PIPE)
	{
		if (parser_begin && parser_begin->is_infile_exec == 1)
		{	
			if (parser_begin->parser_type == INFILE)
				exec_elem->infile = ft_strdup(parser_begin->file_name);
			if (parser_begin->parser_type == HERE_DOC)
			{
				exec_elem->fd_here_doc = parser_begin->fd;
				exec_elem->delimiter = ft_strdup(parser_begin->delimiter);
				exec_elem->is_a_quote_delimiter = parser_begin->is_a_quote_delimiter;
			}
		}
		if (parser_begin && parser_begin->is_outfile_exec == 1)
		{	
			exec_elem->outfile = ft_strdup(parser_begin->file_name);
			if (parser_begin->parser_type == OUTFILE_APPEND)
				exec_elem->outfile_type = OUT_APPEND;
			if (parser_begin->parser_type == OUTFILE_TRUNC)
				exec_elem->outfile_type = OUT_TRUNC;
		}
		parser_begin = parser_begin->next;
	}
	exec_elem->next = NULL;
	return (exec_elem);
}


t_exec	*ft_generate_exec_list(t_env_elem *envp_list, t_parser *parser_list, int *nb_cmd)
{
	t_parser	*parser_begin;
	t_exec		*exec_list;
	t_exec		*exec_begin;
	t_exec		*exec_next;
	int			indx;

	indx = 1;
	parser_begin = parser_list;
	if (parser_begin && parser_begin->parser_type != PIPE)
	{	
		exec_begin = ft_generate_executable(envp_list, parser_begin);
		exec_begin->index = indx;
		indx++;
	}
	else
		return (NULL);
	exec_list = exec_begin;
	while (parser_begin && parser_begin->parser_type != PIPE)
		parser_begin = parser_begin->next;
	if (parser_begin && parser_begin->parser_type == PIPE)
		parser_begin = parser_begin->next;
	else
		return (exec_list);
	while(parser_begin)
	{
		if (parser_begin && parser_begin->parser_type != PIPE)
		{	
			exec_next = ft_generate_executable(envp_list, parser_begin);
			exec_next->index = indx;
			indx++;
		}
		exec_begin->next = exec_next;
		while (parser_begin && parser_begin->parser_type != PIPE)
			parser_begin = parser_begin->next;
		if (parser_begin && parser_begin->parser_type == PIPE)
			parser_begin = parser_begin->next;
		exec_begin = exec_begin->next;
	}
	(*nb_cmd) = indx - 1;
	return (exec_list);
}
