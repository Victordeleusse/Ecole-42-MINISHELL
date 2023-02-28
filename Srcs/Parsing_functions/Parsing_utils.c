/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_utils.c                                    :+:      :+:    :+:   */
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



void	ft_generate_token(t_token *begin, char *str, int *is_open_simple, int *is_open_double)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (ft_is_special_character(*str))
	{
		new_token->is_symbol = 1;
		if (*str == '|')
			new_token->is_symbol = SIMPLE_PIPE;
		if (*str == '\'' && !(*is_open_simple))
		{	
			new_token->symbol = SINGLE_LEFT;
			*is_open_simple = 1;
		}
		if (*str == '\'' && (*is_open_simple))
		{
			new_token->symbol = SINGLE_RIGHT;
			*is_open_simple = 0;
		}
		if (*str == '\"' && !(*is_open_double))
		{	
			new_token->symbol = DOUBLE_LEFT;
			*is_open_double = 1;
		}
		if (*str == '\"' && (*is_open_double))
		{
			new_token->symbol = DOUBLE_RIGHT;
			*is_open_double = 0;
		}
		new_token->string = NULL;
		new_token->next = NULL;
	}
	else 
	{
		new_token = ft_string_to_token(str, is_open_simple, is_open_double);
		// new_token.is_symbol = 0;
		// new_token.symbol = 42;
		// new_token.string = str;
	}
	if (!(begin))
		begin = new_token;
	else 
	{
		begin->next = new_token;
		begin = begin->next;
	} 
}

