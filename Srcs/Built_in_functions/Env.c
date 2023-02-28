/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_env_function(t_env_elem **envp_list, char **tab_args)
{
	char	**tab_env;
	int		i;

	if (!envp_list || !tab_args)
	{	
		S_GLOBAL.GLOBAL_RETURN = 1;
		return ;
	}
	if (tab_args[1])
	{
		ft_message_err(ERR_ENV_TOO_MANY_ARGS);
		return ;
	}
	tab_env = ft_envp_in_tab(envp_list);
	if (!tab_env)
		return ;
	i = 0;
	while (tab_env[i])
	{
		write(1, tab_env[i], ft_strlen(tab_env[i]));
		write(1, "\n", 1);
		i++;
	}
	S_GLOBAL.GLOBAL_RETURN = 1;
}
