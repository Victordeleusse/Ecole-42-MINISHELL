/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get_simple_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // To clean quotes when 

void	ft_clean_quote_before_getting_fd(char *file_name)
{
	int	i;

	if (file_name[0] == '\"' || file_name[0] == '\'')
		ft_memmove(file_name, file_name + 1, ft_strlen(file_name));
	i = 0;
	while (file_name[i])
		i++;
	i = i - 1;
	if (file_name[i] == '\"' || file_name[i] == '\'')
		file_name[i] = '\0';
	i = i - 1;
	while (file_name[i] == ' ' && file_name[i])
	{
		file_name[i] = '\0';
		i = i - 1;
	}
}

// // When the parser is an INFILE PARSER TYPE -> '<' en 0 puis arg[1] en 2

int	ft_get_fd_infile(t_parser *parser_elem)
{
	if (!parser_elem->file_name)
		return (0);
	ft_clean_quote_before_getting_fd(parser_elem->file_name);
	parser_elem->fd = open(parser_elem->file_name, O_RDONLY);
	if (parser_elem->fd < 0)
	{
		ft_message_p_err(parser_elem->file_name);
		return (0);
	}
	return (1);
}

// // When the parser is an OUTFILE_TRUNC PARSER TYPE -> '>' en 0 puis arg[1] en 2

int	ft_get_fd_outfile_trunc(t_parser *parser_elem)
{
	if (!parser_elem->file_name)
		return (0);
	ft_clean_quote_before_getting_fd(parser_elem->file_name);
	parser_elem->fd = open(parser_elem->file_name, O_CREAT | O_RDWR | O_TRUNC, 0000664);
	if (parser_elem->fd < 0)
	{
		ft_message_p_err(parser_elem->file_name);
		return (0);
	}
	return (1);
}

// // When the parser is an OUTFILE_APPEND PARSER TYPE -> '>' en 0 et en 1 puis arg[1] en 3

int	ft_get_fd_outfile_append(t_parser *parser_elem)
{
	if (!parser_elem->file_name)
		return (0);
	ft_clean_quote_before_getting_fd(parser_elem->file_name);
	parser_elem->fd = open(parser_elem->file_name, O_WRONLY | O_CREAT | O_APPEND, 0000664);
	if (parser_elem->fd < 0)
	{
		ft_message_p_err(parser_elem->file_name);
		return (0);
	}
	return (1);
}
