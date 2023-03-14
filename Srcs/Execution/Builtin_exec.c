/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin_func(t_exec *exec_elem)
{
	if ((!ft_strcmp(exec_elem->tab_cmd_args[0], "pwd")))
	{	
		if (exec_elem->tab_cmd_args[1] && exec_elem->tab_cmd_args[1][0] == '-')
		{	
			ft_message_err(ERR_PWD);
			return (0);
		}
		ft_builtin_get_current_directory();
		return (1);
	}
	else if ((!ft_strcmp(exec_elem->tab_cmd_args[0], "cd")))
	{	
		ft_builtin_change_directory(&exec_elem->envp_list, exec_elem->tab_cmd_args);
		return (1);
	}
	else if ((!ft_strcmp(exec_elem->tab_cmd_args[0], "echo")))
	{	
		ft_builtin_echo_function(exec_elem->tab_cmd_args);
		return (1);
	}
	else if ((!ft_strcmp(exec_elem->tab_cmd_args[0], "export")))
	{
		ft_builtin_export_function(&exec_elem->envp_list, exec_elem->tab_cmd_args);
		return (1);
	}
	else if ((!ft_strcmp(exec_elem->tab_cmd_args[0], "unset")))
	{
		ft_builtin_unset_function(&exec_elem->envp_list, exec_elem->tab_cmd_args);
		return (1);
	}
	return (0);
}
