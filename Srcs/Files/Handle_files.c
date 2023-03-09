/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_infiles_for_exec(t_parser *parser_list)
{
	t_parser	*parser_begin;
	t_parser	*parser_target;

	parser_begin = parser_list;
	parser_target = NULL;
	while (parser_begin)
	{	
		while (parser_begin && parser_begin->parser_type != PIPE)
		{
			if (parser_begin->parser_type == INFILE || parser_begin->parser_type == HERE_DOC)
				parser_target = parser_begin;
			parser_begin = parser_begin->next;
		}
		if (parser_target)
			parser_target->is_infile_exec = 1;
		if (parser_begin && parser_begin->parser_type == PIPE)
		{	
			parser_begin = parser_begin->next;
			parser_target = NULL;
		}
	}
}


static void	ft_get_outfiles_for_exec(t_parser *parser_list)
{
	t_parser	*parser_begin;
	t_parser	*parser_target;

	parser_begin = parser_list;
	parser_target = NULL;
	while (parser_begin)
	{	
		while (parser_begin && parser_begin->parser_type != PIPE)
		{
			if (parser_begin->parser_type == OUTFILE_APPEND || parser_begin->parser_type == OUTFILE_TRUNC)
				parser_target = parser_begin;
			parser_begin = parser_begin->next;
		}
		if (parser_target)
			parser_target->is_outfile_exec = 1;
		if (parser_begin && parser_begin->parser_type == PIPE)
		{	
			parser_begin = parser_begin->next;
			parser_target = NULL;
		}
	}
}

void	ft_config_exec_files(t_parser *parser_list)
{
	ft_get_infiles_for_exec(parser_list);
	ft_get_outfiles_for_exec(parser_list);
}


int	ft_handle_files(t_parser *parser_elem)
{
	// if (parser_elem->parser_type == HERE_DOC)
	// {
	// 	if (!ft_get_here_doc_traitement(parser_elem))
	// 		return (0);
	// }
	if (parser_elem->parser_type == INFILE && !parser_elem->is_infile_exec && !parser_elem->is_outfile_exec)
	{
		if (!ft_get_fd_infile(parser_elem))
			return (0); 
	}
	if (parser_elem->parser_type == OUTFILE_APPEND && !parser_elem->is_infile_exec && !parser_elem->is_outfile_exec)
	{
		if (!ft_get_fd_outfile_append(parser_elem))
			return (0);
	}
	if (parser_elem->parser_type == OUTFILE_TRUNC && !parser_elem->is_infile_exec && !parser_elem->is_outfile_exec)
	{
		if (!ft_get_fd_outfile_trunc(parser_elem))
			return (0);
	}
	return (1);
}
