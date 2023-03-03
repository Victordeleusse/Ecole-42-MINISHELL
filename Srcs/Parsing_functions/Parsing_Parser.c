/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Parsers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_manage_list_for_redirection(t_token *token_list)
{
	t_token	*begin;

	ft_remove_empty_token_from_list(token_list);
	if (!token_list)
		return (0);
	begin = token_list;
	while (begin)
	{
		if (begin->symbol == DIR_RIGHT || begin->symbol == DIR_LEFT || begin->symbol == DOUBLE_DIR_RIGHT || begin->symbol == DOUBLE_DIR_LEFT)
		{
			if(begin->next)
				ft_merge_tokens(begin, begin->next);
		}
		begin = begin->next;
	}
	begin = token_list;
	while (begin)
	{
		if (begin->symbol == DIR_RIGHT || begin->symbol == DIR_LEFT || begin->symbol == DOUBLE_DIR_RIGHT || begin->symbol == DOUBLE_DIR_LEFT)
		{	
			if (!ft_is_not_an_unexpected_token(begin))
			{	
				ft_free_token_list(token_list);
				return (0);	
			}
		}
		begin = begin->next;
	}
	ft_clean_whitespace(token_list);
	return (1);
}

// To generate a PARSER ELEMENT

// Making a dup on token->string to free the token_list after having generate the parser_list

// t_parser *ft_generate_parser(t_token *token)
// {
// 	t_parser	*parser;

// 	parser = ft_calloc(sizeof(t_parser), 1);
// 	parser->string = ft_strdup(token->string);
// 	parser->next = NULL;
// 	parser->previous = NULL;
// 	parser->parser_type = NULL;
// 	parser->delimiter = NULL;
// 	parser->file_name = NULL;
// 	parser->fd = -1;
// 	if (token->symbol == DIR_LEFT)
// 	{	
// 		parser->parser_type = INFILE;
// 		parser->file_name = ft_get_filename_or_delimiter_from_token(token);
// 	}
// 	else if (token->symbol == DOUBLE_DIR_LEFT)
// 	{	
// 		parser->parser_type = HERE_DOC;
// 		parser->delimiter = ft_get_filename_or_delimiter_from_token(token);
// 	}
// 	else if (token->symbol == DIR_RIGHT)
// 	{
// 		parser->parser_type = OUTFILE_TRUNC;
// 		parser->file_name = ft_get_filename_or_delimiter_from_token(token);
// 	}
// 	else if (token->symbol == DOUBLE_DIR_RIGHT)
// 	{
// 		parser->parser_type = OUTFILE_APPEND;
// 		parser->file_name = ft_get_filename_or_delimiter_from_token(token);
// 	}
// 	else if (token->symbol == SIMPLE_PIPE)
// 		parser->parser_type = PIPE;
// 	else
// 		parser->parser_type = ARG_CMD;
// }
