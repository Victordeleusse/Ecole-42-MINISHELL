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

void	ft_builtin_current_directory(char **tab_args)
{
	char	path[1024];

	if (!ft_strcmp(tab_args[0], "pwd")) 
	{
		if (getcwd(path, 1024) == NULL)
		{	
			perror("CWD");
			GLOBAL_RETURNVAL = 1;
		}
		write(1, path, ft_strlen(path));
	}
}

// void	ft_builtin_change_directory(t_env_elem **envp_list, char **tab_args)
// {
// 	char	path[1024];

// 	if (getcwd(path, 1024) == NULL)
// 	{	
// 		perror(errno);
// 		GLOBAL_RETURNVAL = 1;
// 	}
// 	write(1, path, ft_strlen(path));
// 	return ;
// }
