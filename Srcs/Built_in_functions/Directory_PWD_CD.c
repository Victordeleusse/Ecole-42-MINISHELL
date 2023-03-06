/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directory_PWD_CD.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//// PWD command ////

void	ft_builtin_get_current_directory(void)
{
	S_GLOBAL.PWD = getcwd(NULL, 0);
	if (!S_GLOBAL.PWD)
	{	
		perror(ERR_IN_SHELL_PWD);
		S_GLOBAL.GLOBAL_RETURN = 1;
		return ;
	}
	write(1, S_GLOBAL.PWD, ft_strlen(S_GLOBAL.PWD));
	write(1, "\n", 1);
	S_GLOBAL.GLOBAL_RETURN = 0;
}

//// CD command ////

static void	ft_set_home_value(t_env_elem **envp_list)
{
	t_env_elem	*begin;
	
	if (!envp_list || !(*envp_list))
	{	
		S_GLOBAL.IS_HOME = 0;
		S_GLOBAL.HOME_PATH = NULL;
		return ;
	}
	begin = *envp_list;
	while (begin)
	{
		if (!ft_strcmp(begin->name, "HOME"))
		{	
			S_GLOBAL.IS_HOME = 1;
			S_GLOBAL.HOME_PATH = begin->value;	
			return ;
		}
		begin = begin->next;
	}
	S_GLOBAL.IS_HOME = 0;
	S_GLOBAL.HOME_PATH = NULL;
}

static void ft_change_directory_no_arg(t_env_elem **envp_list)
{
	ft_set_home_value(envp_list);
	if (!S_GLOBAL.IS_HOME)
	{
		ft_message_err(ERR_CD_NO_HOME);
		return ;
	}
	if (chdir(S_GLOBAL.HOME_PATH) != 0)
	{	
		perror(ERR_IN_SHELL_CD);
		S_GLOBAL.GLOBAL_RETURN = 1;
		return ;
	}
	S_GLOBAL.GLOBAL_RETURN = 0;
}

void	ft_builtin_change_directory(t_env_elem **envp_list, char **tab_args)
{
	if (!tab_args[1])
	{
		ft_change_directory_no_arg(envp_list);
		ft_builtin_get_current_directory();
		fprintf(stderr, "PWD : %s\n", S_GLOBAL.PWD);
		return ;	
	}
	if (tab_args[2])
	{
		ft_message_err(ERR_CD_TOO_MANY_ARGS);
		return ;
	}

	if (chdir(tab_args[1]) != 0)
	{
		perror(ERR_CD);
		S_GLOBAL.GLOBAL_RETURN = 1;
		return ;
	}
	ft_builtin_get_current_directory();
	fprintf(stderr, "PWD : %s\n", S_GLOBAL.PWD);
}
