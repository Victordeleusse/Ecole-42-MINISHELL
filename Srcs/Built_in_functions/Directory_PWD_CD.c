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

static void	ft_get_pwd(void)
{
	int	i;
	
	i = 0;
	while (i < 1024)
	{
		S_GLOBAL.PWD[i] = '\0';
		i++;
	}
	if (getcwd(S_GLOBAL.PWD, 1024) == NULL)
	{	
		perror(ERR_IN_SHELL_PWD);
		S_GLOBAL.GLOBAL_RETURN = 1;
	}
}

void	ft_builtin_get_current_directory(void)
{
	ft_get_pwd();
	write(1, S_GLOBAL.PWD, ft_strlen(S_GLOBAL.PWD));
	write(1, "\n", 1);
	S_GLOBAL.GLOBAL_RETURN = 0;
}

static void ft_change_directory_no_arg(void)
{
	if (S_GLOBAL.IS_HOME == 0)
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

void	ft_builtin_change_directory(char **tab_args)
{
	char	*tmp;
	
	if (*tab_args && !tab_args[1])
	{
		ft_change_directory_no_arg();
		return ;	
	}
	if (tab_args[2])
	{
		ft_message_err(ERR_CD_TOO_MANY_ARGS);
		return ;
	}

	if (chdir(tab_args[1]) != 0)
	{
		ft_get_pwd();
		tmp = ft_strjoin(S_GLOBAL.PWD, "/");
		tmp = ft_strjoin(tmp, tab_args[1]);
		if (chdir(tmp) != 0)
		{
			perror(ERR_CD);
			S_GLOBAL.GLOBAL_RETURN = 1;
			free(tmp);
			return ;
		}
		free(tmp);
	}
}
