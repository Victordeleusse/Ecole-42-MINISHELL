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
#include "Environment.h"

int	RETURNVAL;

int	main(int argc, char **argv, char **envp)
{
	t_env_elem	*my_envp;
	t_env_elem	*begin;
	// int		i;

	(void)argc;
	(void)argv;
	my_envp = ft_generate_envp_list(envp);
	ft_export_variable_in_env("VICTOR=", &my_envp, 1);
	begin = my_envp;
	while (begin)
	{
		printf("%s ->", begin->name);
		printf("%s\n", begin->value);
		begin = begin->next;
	}
	printf("\n\n%d\n",ft_check_is_already_present_and_exported(&my_envp, "VICTOR=bonjour"));
	// ft_get_data();
	return (0);
}