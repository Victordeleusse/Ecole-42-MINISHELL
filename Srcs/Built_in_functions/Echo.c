/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_echo_function(char **tab_args)
{
	int	is_n;
	int	i;

	is_n = 0;
	i = 1;
	if (!tab_args[1])
	{
		write(1, "\n", 1);
		S_GLOBAL.GLOBAL_RETURN = 1;
		return ;
	}
	if (!ft_strcmp(tab_args[1], "-n"))
	{
		is_n = 1;
		i = 2;
	}
	while(tab_args[i])
	{
		write(1, tab_args[i], ft_strlen(tab_args[i]));
		i++;
	}
	if (!is_n)
		write(1, "\n", 1);
	S_GLOBAL.GLOBAL_RETURN = 1;
	return ;
}
