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
# define MSG_UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define MSG_INTERROGATION_SYMBOL "minishell: ambiguous redirect "
# define DEFAULT_FD_PARSER 9999

typedef enum s_parser_type
{
	INFILE = 1,
	HERE_DOC,
	OUTFILE_TRUNC,
	OUTFILE_APPEND,
	CMD,
	ARG,
	PIPE
} t_parser_type;

typedef struct s_parser
{
	t_parser_type	parser_type;
	char			*string;
	char			*delimiter;
	int				is_a_quote_delimiter;
	char			*file_name;
	int				fd;
	int				index;
	t_env_elem		*envp_list;
	struct s_parser	*next;
} t_parser;

///////////////// Parsing_Parser_utils.c //////////////

void	ft_ordonate_parser_list(t_parser *parser_list);

///////////////// Parsing_Parser.c //////////////

t_parser	*ft_generate_parser(t_token *token, t_env_elem *envp_list);
t_parser 	*ft_generate_list_parser(t_token *token_list, t_env_elem *envp_list);

#endif