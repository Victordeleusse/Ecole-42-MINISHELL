/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Directory.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>  

void	ft_builtin_get_current_directory(char **tab_args)
{
	char	path[1024];
	char	*tmp;

	if (!ft_strcmp(tab_args[0], "pwd")) 
	{
		if (getcwd(path, 1024) == NULL)
		{	
			tmp = ft_strjoin(ERR_IN_SHELL, "pwd");
			perror(tmp);
			free(tmp);
			S_GLOBAL.GLOBAL_RETURN = 1;
		}
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
}

void	ft_change_directory_no_arg(void)
{
	if (chdir(S_GLOBAL.))
}

// void	ft_builtin_change_directory(char **tab_args)
// {
// 	if (chdir(tab_args[1]) != 0)
// 	{	
// 		perror(ERR_CHANGE_DIRECTORY);
// 		GLOBAL_STRUCTURE.GLOBAL_RETURN = 1;
// 	}
// 	return ;
// }
