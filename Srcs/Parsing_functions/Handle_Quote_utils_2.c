/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_Quote_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_in_str(char *source, char *token_string, int i, int len_target)
{
	int		len_source;
	int		len_old_token_string;
	int		len_new_token_string;
	char	*new_token_string;
	int		k;
	int		j;

	len_source = (int)ft_strlen(source);
	len_old_token_string = (int)ft_strlen(token_string);
	len_new_token_string = len_source + len_old_token_string - len_target;
	new_token_string = ft_calloc(sizeof(char), len_new_token_string + 1);
	if (!new_token_string)
		return (NULL);
	k = 0;
	while (k < i)
	{
		new_token_string[k] = token_string[k];
		k++;
	}
	j = 0;
	while (source[j])
	{
		new_token_string[k] = source[j];
		k++;
		j++;
	}
	j = i + len_target;
	while (token_string[j])
	{
		new_token_string[k] = token_string[j];
		k++;
		j++;
	}
	return (new_token_string);
}


int	ft_substitute_dollar_env_var(t_env_elem *envp_list, t_token *token_begin, int i)
{
	char 		*target;
	int			j;

	j = 0;
	while ((token_begin->string + i + 1)[j] && (token_begin->string + i + 1)[j] != ' ')
		j++;
	target = ft_calloc(sizeof(char), j + 1);
	j = 0;
	while ((token_begin->string + i + 1)[j] && (token_begin->string + i + 1)[j] != ' ')
	{
		target[j] = (token_begin->string + i + 1)[j];
		j++;
	}
	if (!ft_is_a_env_var_name(envp_list, target))
		token_begin->string = ft_str_in_str("", token_begin->string, i, j + 1);
	else
		token_begin->string = ft_str_in_str(ft_is_a_env_var_name(envp_list, target), token_begin->string, i, j + 1);
	if (!token_begin->string)
		return (0);
	return (1);
}