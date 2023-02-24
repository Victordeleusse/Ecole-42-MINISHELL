/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftbuiltin_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:34:21 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/24 12:06:37 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_noarg(t_env *environment)
{
	char	*err_str;
	char	*home;
	int		r;
	
	home = get_value_by_key(environment, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_returnval = 1;
		return ;
	}
	r = chdir(home);
	if (r == -1)
	{
		err_str = ft_strjoin("minishell: cd: ", home);
		if (!err_str)
			ft_putstr_fd(ERRALLOC, 2);
		perror(err_str);
		free(err_str);
		g_returnval = 1;
	}
	else
		g_returnval = 0;
}

void	ftbuiltin_cd(t_env *environment, char **args)
{
	char	*err_str;
	char	*home;
	int		r;

	if (args && args[0] && !args[1])
		_noarg(environment);
	else if (args && args[0] && args[1])
	{
		r = chdir(args[1]);
		if (r == 1)
		{
			err_str = ft_strjoin("minishell: cd: ", args[1]);
			if (!err_str)
				ft_putstr_fd(ERRALLOC, 2);
			perror(err_str);
			free(err_str);
			g_returnval = 1;
		}
		else
			g_returnval = 0;
	}
	else
		g_returnval = 1;
}
