/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_generate_command_buffer_tab(char *command_buffer)
{
	char	**command_buffer_tab;

	command_buffer_tab = ft_split(command_buffer, ' ');
	free(command_buffer);
	return (command_buffer_tab);
}

t_token	*ft_parsing_function(char **command_buffer_tab)
{
	int		i;
	int		is_open_simple;
	int		is_open_double;
	t_token	*token_list;
	t_token	*token_begin;

	if (!command_buffer_tab || !*command_buffer_tab)
		return (NULL);
	is_open_double = 1;
	is_open_simple = 1;
	token_list = ft_calloc(sizeof(t_token), 1);
	token_begin = token_list;
	ft_generate_first_token(token_begin, command_buffer_tab[i], &is_open_simple, &is_open_double);
	i = 1;
	while (command_buffer_tab[i])
	{
		while (token_begin->next)
			token_begin = token_begin->next;
		i++;
	}
}
