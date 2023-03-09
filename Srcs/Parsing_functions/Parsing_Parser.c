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

// // To generate a PARSER ELEMENT
// // Making a dup on token->string to free the token_list after having generate the parser_list

t_parser *ft_generate_parser(t_token *token, t_env_elem *envp_list)
{
 	t_parser	*parser;

	parser = ft_calloc(sizeof(t_parser), 1);
	parser->string = ft_strdup(token->string);
	if (parser->string[0] == ' ')
			ft_memmove(parser->string, parser->string + 1, ft_strlen(parser->string));
	parser->next = NULL;
	parser->delimiter = NULL;
	parser->is_a_quote_delimiter = 0;
	parser->file_name = NULL;
	parser->fd = DEFAULT_FD_PARSER;
	parser->index = 0;
	parser->envp_list = envp_list;
	if (token->symbol == DIR_LEFT)
		parser->parser_type = INFILE;
	else if (token->symbol == DOUBLE_DIR_LEFT)
		parser->parser_type = HERE_DOC;
	else if (token->symbol == DIR_RIGHT)
		parser->parser_type = OUTFILE_TRUNC;
	else if (token->symbol == DOUBLE_DIR_RIGHT)
		parser->parser_type = OUTFILE_APPEND;
	else if (token->symbol == SIMPLE_PIPE)
		parser->parser_type = PIPE;
	else
		parser->parser_type = 0;
	return (parser);
}

t_parser *ft_generate_list_parser(t_token *token_list, t_env_elem *envp_list)
{
	t_token		*token_begin;
	t_parser	*parser_list;
	t_parser	*parser_begin;
	t_parser	*parser_next;

	token_begin = token_list;
	if (!token_begin)
		return (NULL);
	parser_begin = ft_generate_parser(token_begin, envp_list);
	parser_list = parser_begin;
	token_begin = token_begin->next;
	while (token_begin)
	{
		parser_next = ft_generate_parser(token_begin, envp_list);
		parser_next->index = 0;
		parser_begin->next = parser_next;
		parser_begin = parser_begin->next;
		token_begin = token_begin->next;
	}
	return (parser_list);
}