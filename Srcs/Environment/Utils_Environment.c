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

#include "Environment.h"
#include <stddef.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"

int	ft_str_detect(char *str, char *set)
{
	int	i;
	int	j;

	if (!str || !set)
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[j])
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_is_a_variable(char *ligne)
{
	int	i;

	i = 0;
	while (ligne[i])
	{
		if (ft_str_detect(ligne, "="))
			return (1);
		i++;
	}
	return (0);
}

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
	env_name = ft_calloc(sizeof(char), len + 1);
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
	env_value = ft_calloc(sizeof(char), len + 1);
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

// check si la variable est deja presente dans l environnement_list

int	ft_check_variable_is_already_present(t_env_elem **envp_elem_list, char *ligne)
{
	t_env_elem	*begin;
	char		*key;
	int			len;

	key = ft_extract_name(ligne);
	if (!envp_elem_list || !key)
		return (0);
	begin = *envp_elem_list;
	len = ft_strlen(key);
	if (key[len - 1] == '+')
		key[len - 1] = '\0';
	while(begin)
	{
		if (!ft_strcmp(begin->name, key))
			return (1);
		begin = begin->next;
	}
	free(key);
	return (0);
}

// bash$ export VARIABLE(+-*/=.<>?!@#$%^&()) -> Invalid name : not a valid identifier

int	ft_check_variable_name_is_valid(char *ligne)
{
	char	*name;
	int		i;
	int		len_name;

	i = 0;
	name = ft_extract_name(ligne);
	len_name = ft_strlen(name);
	if (name[len_name - 1] == '+')
		name[len_name - 1] = '\0';
	if (ft_str_detect(name, ENVIRONMENT_EXCLUDED_SET))
	{
		write(1, "export: ", ft_strlen("export: "));
		write(1, name, ft_strlen(name));
		write(1, " Invalid name : not a valid identifier", ft_strlen(" Invalid name : not a valid identifier"));
		GLOBAL_RETURNVAL = 1;
		free(name);
		return (0);
	}
	free (name);
	return (1);
}
