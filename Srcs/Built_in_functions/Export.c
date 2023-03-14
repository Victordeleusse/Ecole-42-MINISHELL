/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_configure_env_value(char *envp_str)
{
	int		i;
	int		len;
	char	*new_str;

	len = ft_strlen(envp_str);
	new_str = ft_calloc(sizeof(char), len + 3);
	i = 0;
	while (envp_str[i] && envp_str[i] != '=')
	{
		new_str[i] = envp_str[i];
		i++;
	}
	if (envp_str[i] == '=')
	{
		new_str[i] = envp_str[i];
		i++;
	}
	new_str[i] = '\"';
	while (envp_str[i])
	{
		new_str[i + 1] = envp_str[i];
		i++;
	}
	new_str[i + 1] = '\"';
	return (new_str);
}

// bash$ export -> Affiche l ensemble de mes variables d'environnement avec "export name=value"

static void	ft_export_empty_arg(char **envp_in_tab)
{
	int		i;
	char	*value_modified;
	
	i = 0;
	while(envp_in_tab[i])
	{
		write(1, "export ", 7);
		value_modified = ft_configure_env_value(envp_in_tab[i]);
		write(1, value_modified, ft_strlen(value_modified));
		free(value_modified);
		write(1, "\n", 1);
		i++;
	}
}

void	ft_builtin_export_function(t_env_elem **envp_list, char **tab_args)
{
	int			i;
	char		**envp_in_tab;

	if (!envp_list || !tab_args)
		return ;
	envp_in_tab = ft_envp_in_tab(envp_list); 
	if (!envp_in_tab)
		return ;
	if (!tab_args[1])
		ft_export_empty_arg(envp_in_tab);
	else 
	{	
		i = 1;
		while (tab_args[i])
		{
			if (!ft_is_a_variable(tab_args[i]))
				i++;
			else
			{
				if (!ft_check_variable_name_is_valid(tab_args[i]))
					;
				else if (ft_check_variable_is_already_present(envp_list, tab_args[i]))
					ft_add_or_replace_value(envp_list, tab_args[i]);
				else
					ft_export_new_variable(envp_list, tab_args[i], 1);
				i++;
			}
		}
	}
	S_GLOBAL.GLOBAL_RETURN = 0;
}
