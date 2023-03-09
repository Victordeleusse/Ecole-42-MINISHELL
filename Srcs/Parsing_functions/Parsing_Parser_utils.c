/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Parsers_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_merge_parser(t_parser *parser_elem, t_parser *parser_to_join)
{
	char	*new_str_1;
	char	*new_str;

	if (parser_to_join->string[0] == ' ')
		new_str_1 = ft_strjoin(parser_elem->string, "");
	else
		new_str_1 = ft_strjoin(parser_elem->string, " ");
	new_str = ft_strjoin(new_str_1, parser_to_join->string);
	free(new_str_1);
	free(parser_elem->string);
	if (parser_elem->parser_type == INFILE || parser_elem->parser_type == OUTFILE_APPEND || parser_elem->parser_type == OUTFILE_TRUNC)
		parser_elem->file_name = ft_strdup(parser_to_join->string);
	if (parser_elem->parser_type == HERE_DOC)
	{	
		parser_elem->delimiter = ft_strdup(parser_to_join->string);
		if (parser_to_join->string[0] == '\'' || parser_to_join->string[0] == '\"')
			parser_elem->is_a_quote_delimiter = 1;
	}
	parser_elem->string = new_str;
	parser_elem->next = parser_to_join->next;
	free(parser_to_join->string);
	free(parser_to_join);
}

static void	ft_get_cmd_and_args_for_exec(t_parser *parser_list)
{
	t_parser	*parser_begin;

	parser_begin = parser_list;
	while (parser_begin)
	{	
		while (parser_begin && parser_begin->parser_type != PIPE)
		{
			while (parser_begin && parser_begin->parser_type != PIPE && parser_begin->parser_type != 0)
				parser_begin = parser_begin->next;
			if (parser_begin && parser_begin->parser_type != PIPE && parser_begin->parser_type == 0)
			{
				parser_begin->is_cmd = 1;
				parser_begin = parser_begin->next;
			}
			while (parser_begin && parser_begin->parser_type != PIPE)
			{
				if (parser_begin && parser_begin->parser_type != PIPE && parser_begin->parser_type == 0)
					parser_begin->is_arg = 1;
				parser_begin = parser_begin->next;
			}
		}
		if (parser_begin && parser_begin->parser_type == PIPE)
			parser_begin = parser_begin->next;
	}
}

int	ft_ordonate_parser_list(t_parser *parser_list)
{
	t_parser *parser_begin;

	parser_begin = parser_list;
	while (parser_begin)
	{
		if ((parser_begin->parser_type == INFILE || parser_begin->parser_type == HERE_DOC || parser_begin->parser_type == OUTFILE_APPEND || parser_begin->parser_type == OUTFILE_TRUNC) && parser_begin->next)
			ft_merge_parser(parser_begin, parser_begin->next);
		parser_begin = parser_begin->next;
	}
	ft_config_exec_files(parser_list);
	ft_get_cmd_and_args_for_exec(parser_list);
	parser_begin = parser_list;
	while (parser_begin)
	{
		if (!ft_handle_files(parser_begin))
			return (0);
		parser_begin = parser_begin->next;
	}
	return (1);
}

