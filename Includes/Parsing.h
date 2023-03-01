/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define SPECIAL_ARGS	">|<"

typedef enum s_symbol
{
	SINGLE_LEFT = 1,
	DOUBLE_LEFT,
	SINGLE_RIGHT,
	DOUBLE_RIGHT,
	SIMPLE_PIPE,
	DIR_RIGHT,
	DOUBLE_DIR_RIGHT,
	DIR_LEFT,
	DOUBLE_DIR_LEFT
} t_symbol;

typedef enum s_folder_parser
{
	HERE_DOC = 1,
	OUTFILE_TRUNC,
	OUTFILE_APPEND,
	INFILE
}t_folder_parser;


typedef struct s_token
{
	int				is_symbol;
	t_symbol		symbol;
	char			*string;
	struct s_token	*next;
} t_token;

typedef struct s_parser
{
	int				is_symbol;
	t_symbol		symbol;
	int				is_folder;
	t_folder_parser	folder_type;
	char			*delimiter;
	int				fd_folder;
	char			*string;
	struct s_parser	*next;
	struct s_parser	*previous;
} t_parser;

//////////////////////// Parsing_Tokens_utils.c /////////////////////////

int		ft_is_special_character(char c);
int		ft_is_separator(char c);
int		ft_is_a_string(char c);
char	*ft_generate_str_for_token(char	*command_buff);
t_token	*ft_generate_token_from_string(char *command_buff);
t_token	*ft_generate_token_from_symbol(char c, char d, int *is_open_simple, int *is_open_double);

//////////////////////// Handle_Quote.c /////////////////////////

void	ft_merge_tokens(t_token *token_list, t_token *token_begin);
int		ft_handle_single(t_token *token_list);
int		ft_handle_double(t_token *token_list);
t_token	*ft_clean_quote_token_list(t_token *token_list, int *is_open_simple, int *is_open_double);

//////////////////////// Parsing.c /////////////////////////

void	ft_free_token_list(t_token	*token_list);
t_token	*ft_generate_token_list(char *command_buff, int *is_open_simple, int *is_open_double);

#endif