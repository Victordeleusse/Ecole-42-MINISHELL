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

int	ft_manage_list_for_redirection(t_token *token_list)
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
			if(begin->next)
				ft_merge_tokens(begin, begin->next);
		}
		begin = begin->next;
	}
	begin = token_list;
	while (begin)
	{
		if (begin->symbol == DIR_RIGHT || begin->symbol == DIR_LEFT || begin->symbol == DOUBLE_DIR_RIGHT || begin->symbol == DOUBLE_DIR_LEFT)
		{	
			if (!ft_is_not_an_unexpected_token(begin))
			{	
				ft_free_token_list(token_list);
				return (0);	
			}
		}
		begin = begin->next;
	}
	return (1);
}
