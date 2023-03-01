/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_Quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_dollar(t_env_elem *envp_list, t_token *token_list)
{
	t_token	*token_begin;

	token_begin = token_list;


}

t_token	*ft_clean_quote_token_list(t_env_elem *envp_list, t_token *token_list, int *is_open_simple, int *is_open_double)
{
	t_token	*token_begin;

	token_begin = token_list;	
	if ((*is_open_simple) && (*is_open_double))
	{
		ft_free_token_list(token_list);
		S_GLOBAL.GLOBAL_RETURN = 1;
		return (NULL);
	}
	while (token_begin)
	{
		while (token_begin && token_begin->symbol != SINGLE_LEFT && token_begin->symbol != DOUBLE_LEFT)
			token_begin = token_begin->next;
		if (token_begin && token_begin->symbol == SINGLE_LEFT)
		{	
			if (!ft_handle_single(token_begin))
			{
				ft_free_token_list(token_list);
				S_GLOBAL.GLOBAL_RETURN = 1;
				return (NULL);
			}
		}
		else if (token_begin && token_begin->symbol == DOUBLE_LEFT)
		{
			if (!ft_handle_double(token_begin))
			{
				ft_free_token_list(token_list);
				S_GLOBAL.GLOBAL_RETURN = 1;
				return (NULL);
			}
		}
		if (token_begin)
			token_begin = token_begin->next;
	}
	ft_handle_dollar()
	return (token_list);
}
