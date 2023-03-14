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

static int	ft_cleaning_arg(char **tab_args, int *i)
{	
	int	len;

	if (tab_args[(*i)][0] == '$')
	{
		if (tab_args[(*i) + 1])
		{
			len = ft_strlen(tab_args[(*i) + 1]) - 2;
			tab_args[(*i)] = tab_args[(*i) + 1];
			// dprintf(2, "NOUVEL arg: %s -> len : %d\n", tab_args[*i], len);
			ft_memmove(tab_args[(*i)], tab_args[(*i)] + 1, len - 1);
			tab_args[(*i)][len - 1] = '\0';
			// dprintf(2, "MODIF arg: %s\n", tab_args[*i]);
		}
		return (1);
	}
	return (0);
}

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
		// dprintf(2, "arg : %s\n", tab_args[i]);
		if (ft_cleaning_arg(tab_args, &i))
		{
			write(1, tab_args[i], ft_strlen(tab_args[i]));	
		 	i = i + 1;
		}
		else 
			write(1, tab_args[i], ft_strlen(tab_args[i]));
		if (tab_args[i + 1])
		write(1, " ", 1);
		i++;
	}
	if (!is_n)
		write(1, "\n", 1);
	S_GLOBAL.GLOBAL_RETURN = 1;
	return ;
}
