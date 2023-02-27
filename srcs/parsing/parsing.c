/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/27 14:45:05 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_env *environment, char **line)
{
	char	**cmds;
	size_t	i;
	int		r;
	size_t	size;

	cmds = split_cmds(line);
	if (!cmds)
		return ;
	size = 0;
	while (cmds[size])
		size++;
	i = 0;
	while (cmds[i])
	{
		while (1)
		{
			r = change_local_variables(environment, cmds[i], size);
			if (r == -1)
				break ;
			else if (r != 1)
				break ;
		}
		if (r != -1)
		{
			ft_strip(cmds[i]);
			if (cmds[i] && cmds[i][0])
				parse_cmd(environment, cmds, cmds + i, i);
			else
				g_returnval = 0;
		}
		i++;
	}
	free_tabstr(cmds);
}
