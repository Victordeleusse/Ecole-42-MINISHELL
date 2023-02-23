/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/23 09:53:51 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_builtin(t_env *environnement, char *line)
{
	if (ft_strncmp(line, "pwd", 3) == 0 \
	&& (ft_strchr(SEPARATORS, line[3]) || line[3] == '\0'))	
		ftbuiltin_pwd(environnement);
	else if (ft_strncmp(line, "export", 6) == 0 \
	&& (ft_strchr(SEPARATORS, line[6]) || line[6] == '\0'))	
		ftbuiltin_export(environnement, line + 6);
	else if (ft_strncmp(line, "unset", 5) == 0 \
	&& (ft_strchr(SEPARATORS, line[5]) || line[5] == '\0'))	
		ftbuiltin_unset(environnement, line + 5);
	else if (ft_strncmp(line, "env", 3) == 0 \
	&& (ft_strchr(SEPARATORS, line[3]) || line[3] == '\0'))	
		ftbuiltin_env(environnement);
	else if (ft_strncmp(line, "exit", 4) == 0 \
	&& (ft_strchr(SEPARATORS, line[4]) || line[4] == '\0'))	
		ftbuiltin_exit(environnement, line);
	else
		return (0);
	return (1);
}

void	command_not_found(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && ft_strchr(SEPARATORS, line[i]) == NULL)
		i++;
	if (line[i])
		line[i] = '\0';
	ft_printf("minishell: %s: command not found\n", line);
	RETURNVAL = 127;
}

void	parsing(t_env *environnement, char *line)
{
	ft_strip(line);
	if (*line == '\0')
		return ;
	if (parsing_builtin(environnement, line))
		return ;
	else
		command_not_found(line);
}
