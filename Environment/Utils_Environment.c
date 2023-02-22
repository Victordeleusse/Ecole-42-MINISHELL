/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Environment.h"
#include <stddef.h>
#include <stdio.h>
#include "libft.h"

char	*ft_extract_name(char *envp_index)
{
	int		i;
	int		len;
	char	*env_name;

	if (!envp_index)
		return (NULL);
	i = 0;
	len = 0;
	while (envp_index[i] && envp_index[i] != '=')
	{
		i++;
		len++;
	}
	if (envp_index[i] != '=')
		return (NULL);
	env_name = ft_calloc(sizeof(char), len);
	i = 0;
	while (i < len)
	{
		env_name[i] = envp_index[i];
		i++;
	}
	return (env_name);
}

char	*ft_extract_value(char *envp_index)
{
	int		i;
	int		j;
	int		len;
	char	*env_value;

	if (!envp_index)
		return (NULL);
	i = 0;
	len = 0;
	while (envp_index[i] && envp_index[i] != '=')
		i++;
	if (envp_index[i] != '=')
		return (NULL);
	i++;
	while (envp_index[i + len])
		len++;
	env_value = ft_calloc(sizeof(char), len);
	j = 0;
	while (j < len)
	{
		env_value[j] = envp_index[i + j];
		j++;
	}
	return (env_value);
}

void	ft_lst_envp_add_back(t_env_elem **envp_elem_list, t_env_elem *elem)
{
	t_env_elem	*last;

	if (!*envp_elem_list)
	{
		*envp_elem_list = elem;
		return ;
	}
	last = *envp_elem_list;
	while (last->next)
		last = last->next;
	last->next = elem;
}

int	ft_check_is_already_present_and_exported(t_env_elem **envp_elem_list, char *str_entry)
{
	t_env_elem	*begin;
	char		*key;

	key = ft_extract_name(str_entry);
	if (!*envp_elem_list || !envp_elem_list || !key)
		return (0);
	begin = *envp_elem_list;
	while(begin)
	{
		fprintf(stderr, "name : %s\n", begin->name);
		if (!ft_strcmp(begin->name, key))
			return (1);
		begin = begin->next;
	}
	return (0);
}

