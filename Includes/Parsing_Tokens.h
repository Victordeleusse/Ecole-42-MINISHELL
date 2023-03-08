/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Tokens.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOKENS_H
# define PARSING_TOKENS_H

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

typedef struct s_token
{
	int				is_symbol;
	t_symbol		symbol;
	char			*string;
	char			**str_tab;
	struct s_token	*next;
} t_token;

//////////////////////// Parsing_Tokens_utils_2_3.c /////////////////////////

int		ft_is_special_character(char c);
int		ft_is_separator(char c);
int		ft_is_a_string(char c);
int		ft_is_simple_quote(char c);
int		ft_is_double_quote(char c);
char	*ft_generate_str_for_token(char	*command_buff);
t_token	*ft_generate_token_from_string(char *command_buff);
t_token	*ft_generate_token_from_tab(t_token	*token, int *i);
t_token	*ft_generate_token_from_symbol(char c, char d, int *is_open_simple, int *is_open_double);
void	ft_clean_whitespace(t_token *envp_list);
int		ft_is_no_open_quote(t_token *token_list, int *is_open_simple, int *is_open_double);


int		ft_manage_unexpected_tokens(t_token *token_list);
int		ft_is_not_an_unexpected_token(t_token *token);
void	ft_get_cmd_and_args_token(t_token *token_list);

//////////////////////// Handle_Quote_utils_2.c /////////////////////////

void	ft_merge_tokens(t_token *token_list, t_token *token_begin);
int		ft_handle_single(t_token *token_list, int *is_open_double);
int		ft_handle_double(t_token *token_list, int *is_open_single);
int		ft_detect_dollar_out_of_simple_quote(t_token *token_begin);
char	*ft_str_in_str(char *source, char *token_string, int i, int len_target);
int		ft_substitute_dollar_env_var(t_env_elem *envp_list, t_token *token_list, int i);

//////////////////////// Handle_Quote.c /////////////////////////

int		ft_handle_dollar(t_env_elem *envp_list, t_token *token_list);
int		ft_clean_quote_token_list(t_token *token_list, int *is_open_simple, int *is_open_double);

//////////////////////// Parsing.c /////////////////////////

void	ft_free_token_list(t_token	*token_list);
t_token	*ft_generate_token_list(char *command_buff, int *is_open_simple, int *is_open_double);

#endif