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

int	ft_substitute_dollar_env_var(t_env_elem *envp_list, t_token *token_begin, int *i)
{
	int			k;
	int			len_init;
	int			len_value;
	char		*first_part;
	char		*last_part;
	char		*str_to_replace;
	t_env_elem	*envp_begin;

	first_part = ft_calloc(sizeof(char), (*i) + 1);
	if (!first_part)
		return (0);
	k = 0;
	while (k < *i)
	{
		
	}
	k = *i;
	len_init = 0;
	while (token_begin->string[*i] != ' ')
	{	
		len_init++;
		(*i) = (*i) + 1;
	}
	str_to_replace = ft_calloc(sizeof(char), len_init);
	if (!str_to_replace)
		return (0);
	k++;
	while (token_begin->string[k] != ' ')
	{
		str_to_replace[k - 1] = token_begin->string[k];
		k++;
	}
	envp_begin = envp_list;
	while (ft_strcmp(str_to_replace, envp_begin->name))
		envp_begin = envp_begin->next;
	if (!envp_begin)
		return (1);
	len_value = ft_strlen(envp_begin->value);


}