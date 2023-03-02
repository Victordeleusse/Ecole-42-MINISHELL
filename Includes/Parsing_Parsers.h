/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Parsers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_PARSERS_H
# define PARSING_PARSERS_H

# define UNEXPECTED_TOKENS "#&<>|"

// typedef enum s_parser_type
// {
// 	REDIR_INFILE = 1,
// 	INFILE,
// 	HERE_DOC,
// 	DELIMITER,
// 	REDIR_OUTFILE_TRUNC,
// 	OUTFILE_TRUNC,
// 	REDIR_OUTFILE_APPEND,
// 	OUTFILE_APPEND,
// 	ARGUMENT,
// 	PIPE
// } t_parser_type;

// typedef struct s_parser
// {
// 	t_parser_type	parser_type;
// 	char			*str;
// 	int				fd;
// 	t_parser		*next;
// }t_parser;

///////////////// Parsing_Parser_utils.c //////////////

void	ft_remove_empty_token_from_list(t_token *token_list);

///////////////// Parsing_Parser.c //////////////

int		ft_manage_list_for_redirection(t_token *token_list);


#endif