/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Tokens_utils_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // 

static void	ft_generate_tab_cmd_args(t_token *token_list)
{
	t_token	*token_begin;

	token_begin = token_list;
	while (token_begin)
	{
		if (token_begin->symbol == 0)
			token_begin->str_tab = ft_split(token_begin->string, ' ');
		token_begin = token_begin->next;
	}
}

static void	ft_split_token_list(t_token *token_list)
{
	t_token	*token_begin;
	t_token	*token_next;
	t_token	*token_new;
	int		i;
	
	ft_generate_tab_cmd_args(token_list);
	token_begin = token_list;
	while (token_begin)
	{
		if (token_begin->symbol == 0)
		{
			i = 1;
			token_next = token_begin->next;
			while (token_begin->str_tab[i])
			{
				token_new = ft_generate_token_from_tab(token_begin, &i);
				token_begin->next = token_new;
				token_begin = token_begin->next;
				i++;
			}
			token_begin->next = token_next;
		}
		token_begin = token_begin->next;
	}
}

static void ft_clean_first_str(char *string)
{
	int	i;

	i = 0;
	if (string[i] == ' ')
		i++;
	while (string[i] && string[i] != ' ')
		i++;
	if (string[i] && string[i] == ' ')
	{	
		while (string[i])
		{
			string[i] = '\0';
			i++;
		}	
	}
}

void	ft_get_cmd_and_args_token(t_token *token_list)
{
	t_token *token_begin;
	
	ft_split_token_list(token_list);
	token_begin = token_list;
	while (token_begin)
	{
		if (token_begin->symbol == 0)
			ft_clean_first_str(token_begin->string);
		token_begin = token_begin->next;
	}
}

