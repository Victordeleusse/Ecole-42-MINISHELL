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

static int	ft_is_not_empty_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->string[i])
	{
		if (token->string[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_follow_is_not_empty(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_not_an_unexpected_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->string[i] && !ft_is_separator(token->string[i]))
		i++;
	if (ft_follow_is_not_empty(token->string + i))
		i++;
	else 
	{
		ft_message_unexpected_token(MSG_UNEXPECTED_TOKEN, "newline");
		return (0);
	}
	if (ft_str_detect(&token->string[i], UNEXPECTED_TOKENS))
	{
		if (token->string[i + 1] && token->string[i + 1] == DOUBLE_DIR_RIGHT && token->string[i] == token->string[i + 1])
			ft_message_unexpected_token(MSG_UNEXPECTED_TOKEN, ">>");
		else if (token->string[i + 1] && token->string[i + 1] == DOUBLE_DIR_LEFT && token->string[i] == token->string[i + 1])
			ft_message_unexpected_token(MSG_UNEXPECTED_TOKEN, "<<");
		else if (token->string[i + 1] && token->string[i + 1] == '?')
			ft_message_unexpected_token(MSG_INTERROGATION_SYMBOL, "");
		else
		{	
			token->string[i + 1] = '\0';
			ft_message_unexpected_token(MSG_UNEXPECTED_TOKEN, &token->string[i]);
		}
		return (0);
	}
	return (1);
}

void	ft_remove_empty_token_from_list(t_token *token_list)
{
	t_token	*begin;
	t_token	*next;

	begin = token_list;
	while (!ft_is_not_empty_token(begin))
	{
		token_list = token_list->next;
		free(begin->string);
		free(begin);
		begin = token_list;
	}
	while (begin)
	{
		if (begin->next && !ft_is_not_empty_token(begin->next) && begin->next->next)
		{
			next = begin->next->next;
			free(begin->next->string);
			free(begin->next);
			begin->next = next;
		}
		else 
			begin = begin->next;
	}
}

char	*ft_get_filename_or_delimiter_from_token(char *string)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (string[i] && !ft_is_separator(string[i]))
		i++;
	if (string[i] && ft_is_separator(string[i]))
		i++;
	result = ft_strdup(string + i);
	return (result);
}
