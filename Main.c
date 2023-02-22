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

#include "minishell.h"

int	RETURNVAL;

int	main(int argc, char **argv, char **envp)
{
	t_env_elem	*my_envp;
	t_env_elem	*begin;
	int		i;

	(void)argc;
	(void)argv;
	my_envp = ft_generate_envp_list(envp);
	ft_export_variable_in_env("VICTOR=", &my_envp);
	fprintf(stderr, "OK\n");
	begin = my_envp;
	while (begin)
	{
		printf("key : %s ->", begin->name);
		printf("value : %s\n", begin->value);
		begin = begin->next;
	}
	// ft_get_data();
	return (0);
}