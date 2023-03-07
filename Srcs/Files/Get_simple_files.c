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

// // When the parser is an INFILE PARSER TYPE -> '<' en 0 puis arg[1] en 2

int	ft_get_fd_infile(t_parser *parser_elem)
{
	int		i;
	int		len;
	char	*file_path;

	i = 1;
	if (parser_elem->string[i] == ' ')
		i = 2;
	len = 0;
	while (parser_elem->string[i + len] && !ft_is_separator(parser_elem->string[i + len]))
		len++;
	file_path = ft_calloc(sizeof(char), len + 1);
	len = 0;
	while (parser_elem->string[i + len] && !ft_is_separator(parser_elem->string[i + len]))
	{
		file_path[len] = parser_elem->string[i + len];
		len++;
	}
	free(parser_elem->file_name);
	parser_elem->file_name = file_path;
	parser_elem->fd = open(file_path, O_RDONLY);
	if (parser_elem->fd < 0)
	{
		ft_message_p_err(file_path);
		return (0);
	}
	return (1);
}

// // When the parser is an OUTFILE_TRUNC PARSER TYPE -> '>' en 0 puis arg[1] en 2

int	ft_get_fd_outfile_trunc(t_parser *parser_elem)
{
	int		i;
	int		len;
	char	*file_path;

	i = 1;
	if (parser_elem->string[i] == ' ')
		i = 2;
	len = 0;
	while (parser_elem->string[i + len] && !ft_is_separator(parser_elem->string[i + len]))
		len++;
	file_path = ft_calloc(sizeof(char), len + 1);
	len = 0;
	while (parser_elem->string[i + len] && !ft_is_separator(parser_elem->string[i + len]))
	{
		file_path[len] = parser_elem->string[i + len];
		len++;
	}
	free(parser_elem->file_name);
	parser_elem->file_name = file_path;
	parser_elem->fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC, 0000664);
	if (parser_elem->fd < 0)
	{
		ft_message_p_err(file_path);
		return (0);
	}
	return (1);
}

// // When the parser is an OUTFILE_APPEND PARSER TYPE -> '>' en 0 et en 1 puis arg[1] en 3

int	ft_get_fd_outfile_append(t_parser *parser_elem)
{
	int		i;
	int		len;
	char	*file_path;

	i = 2;
	if (parser_elem->string[i] == ' ')
		i = 3;
	len = 0;
	while (parser_elem->string[i + len] && !ft_is_separator(parser_elem->string[i + len]))
		len++;
	file_path = ft_calloc(sizeof(char), len + 1);
	len = 0;
	while (parser_elem->string[i + len] && !ft_is_separator(parser_elem->string[i + len]))
	{
		file_path[len] = parser_elem->string[i + len];
		len++;
	}
	free(parser_elem->file_name);
	parser_elem->file_name = file_path;
	parser_elem->fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0000664);
	if (parser_elem->fd < 0)
	{
		ft_message_p_err(file_path);
		return (0);
	}
	return (1);
}
