/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // When the parser is an HERE_DOC PARSER TYPE -> '<' en 0 et en 1 puis arg[1] en 3
// // Pay attention to the delimiter -> the behaviour will be different if there is quotes or note !!!

void	ft_get_delimiter_here_doc(t_parser *parser_elem)
{
	int		i;
	int		len;

	i = 3;
	len = 0;
	if (parser_elem->string[i + len] == '\'' || parser_elem->string[i + len] == '\"')
	{
		parser_elem->is_a_quote_delimiter = 1;
		while (parser_elem->string[i + len])
			len++;
		len = len - 3;
	}
	else 	
	{
		while (parser_elem->string[i + len] && !ft_is_separator(parser_elem->string[i + len]))
			len++;
	}
	parser_elem->delimiter = ft_calloc(sizeof(char), len + 1);
	if (parser_elem->is_a_quote_delimiter)
		i = i + 1;
	parser_elem->delimiter = ft_memmove(parser_elem->delimiter, parser_elem->string + i, len);
}

// int	ft_initialize_recep_tmp_file_heredoc(int *recep_file, char *rnd_name)
// {
// 	*recep_file = open("rnd_name", O_CREAT | O_WRONLY | O_TRUNC, 0000664);
// 	if (*recep_file < 0)
// 	{	
// 		perror(ERR_HERE_DOC);
// 		return (0);
// 	}
// }

int	ft_get_here_doc_traitement(t_parser *parser_elem)
{
	// int		recep_file;
	unsigned char	rnd_char[17];
	// int		len;
	// char	*temp;
	int		rnd_fd;

	ft_get_delimiter_here_doc(parser_elem);
	rnd_fd = open("/dev/urandom", O_RDONLY);
	read(rnd_fd, rnd_char,16);
	close(rnd_fd);
	rnd_char[16] = '\0';
	printf("fd : %d - buffer : |%s|\n", rnd_fd, rnd_char);
	return (0);
}
