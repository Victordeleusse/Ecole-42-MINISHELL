/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_Quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_merge_tokens(t_token *token_list, t_token *token_begin)
{
	char	*new_str_1;
	char	*new_str;

	new_str_1 = ft_strjoin(token_list->string, " ");
	new_str = ft_strjoin(new_str_1, token_begin->string);
	free(new_str_1);
	free(token_list->string);
	free(token_begin->string);
	token_list->string = new_str;
	token_list->next = token_begin->next;
	free(token_begin);
}


int	ft_handle_single(t_token *token_list)
{
	t_token	*token_begin;
	t_token	*token_next;

	token_begin = token_list->next;
	while (token_begin && token_begin->symbol != SINGLE_RIGHT)
	{
		token_next = token_begin->next;
		ft_merge_tokens(token_list, token_begin);
		token_begin = token_next;
	}
	if (token_begin && token_begin->symbol == SINGLE_RIGHT)
	{
		ft_merge_tokens(token_list, token_begin);
		return (1);
	}
	return (0);
}

int	ft_handle_double(t_token *token_list)
{
	t_token	*token_begin;
	t_token	*token_next;

	token_begin = token_list->next;
	while (token_begin && token_begin->symbol != DOUBLE_RIGHT)
	{
		token_next = token_begin->next;
		ft_merge_tokens(token_list, token_begin);
		token_begin = token_next;
	}
	if (token_begin && token_begin->symbol == DOUBLE_RIGHT)
	{
		ft_merge_tokens(token_list, token_begin);
		return (1);
	}
	return (0);
}

int	ft_detect_dollar_in_double_quote(t_token *token_begin)
{
	int		i;

	if (token_begin->string[0] == '"')
	{
		i = 0;
		while (token_begin->string[i])
		{
			if (token_begin->string[i] == '$')
				return (1);
			i++;			
		}
	}
	return (0);
}
