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

# define UNEXPECTED_TOKENS "#&<>|?"
# define MSG_UNEXPECTED_TOKEN "minishell-TitouVictor$: syntax error near unexpected token "
# define MSG_INTERROGATION_SYMBOL "minishell-TitouVictor$: ambiguous redirect "

typedef enum s_parser_type
{
	INFILE = 1,
	HERE_DOC,
	OUTFILE_TRUNC,
	OUTFILE_APPEND,
	ARG_CMD,
	PIPE
} t_parser_type;

typedef struct s_parser
{
	t_parser_type	parser_type;
	char			*string;
	char			*delimiter;
	char			*file_name;
	int				fd;
	struct s_parser	*previous;
	struct s_parser	*next;
} t_parser;

///////////////// Parsing_Parser_utils.c //////////////

int		ft_is_not_an_unexpected_token(t_token *token);
void	ft_remove_empty_token_from_list(t_token *token_list);

///////////////// Parsing_Parser.c //////////////

int		ft_manage_list_for_redirection(t_token *token_list);


#endif