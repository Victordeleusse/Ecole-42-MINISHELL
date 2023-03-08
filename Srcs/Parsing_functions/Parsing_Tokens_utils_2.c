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

static void	ft_remove_empty_token_from_list(t_token *token_list)
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

int	ft_manage_unexpected_tokens(t_token *token_list)
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
			if (begin->next && (begin->next->symbol == DIR_RIGHT || begin->next->symbol == DIR_LEFT || begin->next->symbol == DOUBLE_DIR_RIGHT || begin->next->symbol == DOUBLE_DIR_LEFT || begin->next->symbol == SIMPLE_PIPE))
			{	
				ft_message_unexpected_token(MSG_UNEXPECTED_TOKEN, begin->next->string);
				ft_free_token_list(token_list);
				return (0);
			}
			if (!begin->next || (begin->next && !ft_follow_is_not_empty(begin->next->string)))
			{	
				ft_message_unexpected_token(MSG_UNEXPECTED_TOKEN, "newline");
				ft_free_token_list(token_list);
				return (0);
			}
		}
		begin = begin->next;
	}
	ft_clean_whitespace(token_list);
	return (1);
}

// // 

void	ft_token_split_cmd_args(t_token *token_elem)
{
	t_token	*token_next;
	int		i;
	char	**str_tab;

	i = 0;
	if (token_elem->next)
		token_next = token_elem->next;
	else 
		token_next = NULL;
	str_tab = ft_split(token_elem->string, ' ');
	while (str_tab[i])
	{
		printf("string new token : %s\n", str_tab[i]);
		i++;
	}
}
