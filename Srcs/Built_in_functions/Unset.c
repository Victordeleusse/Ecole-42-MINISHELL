/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Unset.h"
#include "libft.h"
#include "minishell.h"

void	ft_builtin_unset_function(t_env_elem **envp_list, char **tab_args)
{
	int			i;
	char		*name;

	if (!envp_list || !tab_args || !tab_args[1])
		return ;
	i = 0;
	while (tab_args[i])
	{
		if (ft_str_detect(tab_args[i], ENVIRONMENT_EXCLUDED_SET))
			;
		else
		{	
			name = ft_strjoin(tab_args[i], "=");
			if (ft_check_variable_is_already_present(envp_list, name))
				ft_lst_envp_remove_elem(envp_list, tab_args[i]);
			free(name);
		}
		i++;
	}
	S_GLOBAL.GLOBAL_RETURN = 0;
}
