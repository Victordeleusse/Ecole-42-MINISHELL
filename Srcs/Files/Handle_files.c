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

int	ft_handle_files(t_parser *parser_elem)
{
	// if (parser_elem->parser_type == HERE_DOC)
	// {
	// 	if (!ft_get_here_doc_traitement(parser_elem))
	// 		return (0);
	// }
	if (parser_elem->parser_type == INFILE)
	{
		if (!ft_get_fd_infile(parser_elem))
			return (0); 
	}
	if (parser_elem->parser_type == OUTFILE_APPEND)
	{
		if (!ft_get_fd_outfile_append(parser_elem))
			return (0);
	}
	if (parser_elem->parser_type == OUTFILE_TRUNC)
	{
		if (!ft_get_fd_outfile_trunc(parser_elem))
			return (0);
	}
	return (1);
}
