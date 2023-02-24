/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "libft.h"


int	GLOBAL_RETURNVAL;

int	main(int argc, char **argv, char **envp)
{
	t_env_elem	*my_envp;
	t_env_elem	*begin;
	char		**args_tab_export;
	char		export_instruction[] = "export PIERRE==10 NICO TITOU=32";
	char		**args_tab_unset;
	char		unset_instruction[] = "unset ";
	char		**args_tab_pwd;
	char		pwd_instruction[] = "pwd";

	(void)argc;
	(void)argv;
	my_envp = ft_generate_envp_list(envp);
	args_tab_export = ft_split(export_instruction, ' ');
	args_tab_unset = ft_split(unset_instruction, ' ');
	args_tab_pwd = ft_split(pwd_instruction, ' ');
	// // ft_get_data();
	ft_builtin_export_function(&my_envp, args_tab_export);
	ft_builtin_unset_function(&my_envp, args_tab_unset);
	printf("\n\n");
	begin = my_envp;
	while (begin)
	{
		printf("%s ->", begin->name);
		printf("%s\n", begin->value);
		begin = begin->next;
	}
	ft_builtin_current_directory(args_tab_pwd);
	return (0);
}