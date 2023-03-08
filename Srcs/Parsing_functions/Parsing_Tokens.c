/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_token *token_list)
{
	t_token	*token_next;
	t_token	*token_begin;

	token_begin = token_list;
	while (token_begin)
	{
		free(token_begin->string);
		token_next = token_begin->next;
		free(token_begin);
		token_begin = token_next;
	}
}

t_token	*ft_generate_token_list(char *command_buff, int *is_open_simple, int *is_open_double)
{
	int		i;
	t_token	*token_list;
	t_token	*token_begin;
	t_token	*token_next;

	i = 0;
	token_list = ft_calloc(sizeof(t_token), 1);
	while (command_buff[i] && ft_is_separator(command_buff[i]))
		i++;
	if (command_buff[i] && (ft_is_a_string(command_buff[i])  && !ft_is_separator(command_buff[i])))
	{
		token_list = ft_generate_token_from_string(command_buff + i);
		token_begin = token_list;
		while (command_buff[i] && ft_is_a_string(command_buff[i]))
			i++;
	}
	else if (command_buff[i] && ft_is_special_character(command_buff[i]))
	{
		token_list = ft_generate_token_from_symbol(command_buff[i], command_buff[i+1], is_open_simple, is_open_double);
		token_begin = token_list;
		if (token_begin->symbol == DOUBLE_DIR_LEFT || token_begin->symbol == DOUBLE_DIR_RIGHT)
			i++;
		i++;
	}
	while (command_buff[i])
	{
		if (command_buff[i] && ft_is_a_string(command_buff[i]))
		{
			token_next = ft_generate_token_from_string(command_buff + i);
			token_begin->next = token_next;
			token_begin = token_begin->next;
			while (command_buff[i] && ft_is_a_string(command_buff[i]))
				i++;
		}
		if (command_buff[i] && ft_is_special_character(command_buff[i]))
		{
			token_next = ft_generate_token_from_symbol(command_buff[i], command_buff[i+1], is_open_simple, is_open_double);
			token_begin->next = token_next;
			if (token_next->symbol == DOUBLE_DIR_LEFT || token_next->symbol == DOUBLE_DIR_RIGHT)
				i++;
			token_begin = token_begin->next;
			i++;
		}
	}
	return (token_list);
}



