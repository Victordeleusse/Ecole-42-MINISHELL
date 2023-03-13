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

	i = 2;
	len = 0;
	if (parser_elem->string[i] == ' ')
		i = 3;
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

// // The temporary file is randomly generated 

static void ft_generate_rnd_file_fd(int *recep_fd, unsigned char **rnd_file_name)
{
	int				rnd_fd;
	int				i;

	rnd_fd = open("/dev/urandom", O_RDONLY);
	read(rnd_fd, *rnd_file_name, 16);
	close (rnd_fd);
	(*rnd_file_name)[16] = '\0';
	i = 0;
	while ((*rnd_file_name)[i])
	{
		while (('a' > (*rnd_file_name)[i] || 'z' < (*rnd_file_name)[i]) && ('A' > (*rnd_file_name)[i] || 'Z' < (*rnd_file_name)[i]) && ('0' > (*rnd_file_name)[i] || '9' < (*rnd_file_name)[i]))
			(*rnd_file_name)[i] = (*rnd_file_name)[i] + 35;
		i++;
	}
	*recep_fd = open((char *)(*rnd_file_name), O_CREAT | O_WRONLY | O_TRUNC, 0000664);
}

// // Let s read on STDIN thanks to get_next_line(0)
// // Pay attention to the behaviour of the here_doc if ther is quote around the delimiter

static int ft_read_and_write_tmp(t_parser *parser_elem, char *delimiter, int *recep_fd)
{
	char	*temp;
	char	*temp_substitute;
	int		len;

	while (1)
	{
		write(1, "> ", 2);
		temp = get_next_line(0);
		if (!temp)
		{
			write(1, "\n", 1);
			ft_message_err(ERR_STOP_HERE_DOC);
			S_GLOBAL.GLOBAL_RETURN = 0;
			return (0);
		}
		len = ft_strlen(temp);
		temp[len - 1] = '\0';
		if (!ft_strcmp(temp, delimiter))
		{
			free(temp);
			break ;
		}
		if (parser_elem->is_a_quote_delimiter == 0 && temp[0] == '$')
		{
			temp_substitute = ft_is_a_env_var_name(parser_elem->envp_list, temp + 1);
			if (temp_substitute)
			{	
				free(temp);
				temp = temp_substitute;
			}
		}
		write(*recep_fd, temp, ft_strlen(temp));
		write(*recep_fd, "\n", 1);
		free(temp);
	}
	return (1);
}

static int	ft_get_infile_from_heredoc(t_parser *parser_elem, int *recep_fd, char *rnd_file_name)
{
	if (*recep_fd >= 0)
		close(*recep_fd);
	parser_elem->file_name = ft_strdup(rnd_file_name);
	parser_elem->fd = open(rnd_file_name, O_RDONLY, 0000664);
	if (parser_elem->fd < 0)
	{
		ft_message_p_err(ERR_HERE_DOC);
		return (0);
	}
	return (1);
}

int	ft_get_here_doc_traitement(t_parser *parser_elem)
{
	int				recep_fd;
	unsigned char	*rnd_file_name;

	rnd_file_name = ft_calloc(sizeof(unsigned char), 17);
	ft_get_delimiter_here_doc(parser_elem);
	ft_generate_rnd_file_fd(&recep_fd, &rnd_file_name);
	if (recep_fd < 0)
		return (0);
	if (!ft_read_and_write_tmp(parser_elem, parser_elem->delimiter, &recep_fd))
		return (0);
	if (!ft_get_infile_from_heredoc(parser_elem, &recep_fd, (char *)rnd_file_name))
	{	
		free(rnd_file_name);
		return (0);
	}
	if (!parser_elem->is_infile_exec)
	{
		close(recep_fd);
		unlink((char *)rnd_file_name);
	}
	free(rnd_file_name);
	return (1);
}
