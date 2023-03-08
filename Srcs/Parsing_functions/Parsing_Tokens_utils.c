/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Tokens_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_special_character(char c)
{
	if (!c)
		return (0);
	if (ft_str_detect(&c, SPECIAL_ARGS) || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_is_separator(char c)
{
	if (!c)
		return (0);
	if (c == ' ')
		return (1);
	return (0);
}

int	ft_is_a_string(char c)
{
	if (c && !ft_is_special_character(c))
		return (1);
	return (0);
}

char	*ft_generate_str_for_token(char	*command_buff)
{
	int		i;
	char	*str;

	i = 0;
	while (command_buff[i] && !ft_is_special_character(command_buff[i]))
		i++;
	str = ft_calloc(sizeof(char), i + 1);
	i = 0;
	while (command_buff[i] && !ft_is_special_character(command_buff[i]))
	{
		str[i] = command_buff[i];
		i++;
	}
	return (str);
}

static char	*ft_generate_string_from_symbol(char c)
{
	char	*string;

	string = ft_calloc(sizeof(char), 2);
	string[0] = c;
	return (string);
}

static char	*ft_generate_string_from_symbol_double(char c)
{
	char	*string;

	string = ft_calloc(sizeof(char), 3);
	string[0] = c;
	string[1] = c;
	return (string);
}

t_token	*ft_generate_token_from_string(char *command_buff)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	new_token->is_symbol = 0;
	new_token->symbol = 0;
	new_token->next = NULL;
	new_token->str_tab = NULL;
	new_token->string = ft_generate_str_for_token(command_buff);
	return (new_token);
}

t_token	*ft_generate_token_from_tab(t_token	*token, int *i)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	new_token->is_symbol = 0;
	new_token->symbol = 0;
	new_token->next = NULL;
	new_token->str_tab = token->str_tab;
	new_token->string = token->str_tab[*i];
	return (new_token);
}

t_token	*ft_generate_token_from_symbol(char c, char d, int *is_open_simple, int *is_open_double)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	new_token->is_symbol = 1;
	if (c == '|')
	{	
		new_token->symbol = SIMPLE_PIPE;
		new_token->string = ft_generate_string_from_symbol(c);
	}
	if (c == '>' && d != '>' )
	{	
		new_token->symbol = DIR_RIGHT;
		new_token->string = ft_generate_string_from_symbol(c);
	}
	if (c == '>' && d == '>' )
	{	
		new_token->symbol = DOUBLE_DIR_RIGHT;
		new_token->string = ft_generate_string_from_symbol_double(c);
	}
	if (c == '<' && d != '<')
	{
		new_token->symbol = DIR_LEFT;
		new_token->string = ft_generate_string_from_symbol(c);
	}
	if (c == '<' && d == '<' )
	{	
		new_token->symbol = DOUBLE_DIR_LEFT;
		new_token->string = ft_generate_string_from_symbol_double(c);
	}
	if (c == '\'' && (*is_open_simple) == 0)
	{	
		new_token->symbol = SINGLE_LEFT;
		*is_open_simple = 1;
		new_token->string = ft_generate_string_from_symbol(c);
	}
	else if (c == '\'' && (*is_open_simple) == 1)
	{
		new_token->symbol = SINGLE_RIGHT;
		*is_open_simple = 0;
		new_token->string = ft_generate_string_from_symbol(c);
	}
	if (c == '"' && (*is_open_double)  == 0)
	{	
		new_token->symbol = DOUBLE_LEFT;
		*is_open_double = 1;
		new_token->string = ft_generate_string_from_symbol(c);
	}
	else if (c == '"' && (*is_open_double) == 1)
	{
		new_token->symbol = DOUBLE_RIGHT;
		*is_open_double = 0;
		new_token->string = ft_generate_string_from_symbol(c);
	}
	new_token->next = NULL;
	return (new_token);
}

void	ft_clean_whitespace(t_token *envp_list)
{
	t_token	*begin;
	int		i;
	int		k;

	begin = envp_list;
	while (begin)
	{
		if (begin->string[0] != '"')
		{
			i = 0;
			while (begin->string[i])
			{	
				k = 0;
				while (begin->string[i] && !ft_is_separator(begin->string[i]))
					i++;
				if (begin->string[i] && ft_is_separator(begin->string[i]))
					i++;
				while (begin->string[i + k] && ft_is_separator(begin->string[i + k]))
					k++;
				ft_memmove(begin->string + i, begin->string + i + k, ft_strlen(begin->string + i + k) + 1);
			}
		}
		begin = begin->next;
	}
}

