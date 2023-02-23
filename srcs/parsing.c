/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/23 16:52:28 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_builtin(t_env *environment, char **args, char *line)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		ftbuiltin_pwd(environment);
	else if (ft_strcmp(args[0], "export") == 0)
		ftbuiltin_export(environment, args);
	// unset
	else if (ft_strcmp(args[0], "env") == 0)
		ftbuiltin_env(environment);
	else if (ft_strcmp(args[0], "exit") == 0)
		ftbuiltin_exit(environment, args, line);
	else
		return (0);
	free_tabstr(args);
	return (1);
}

void	command_not_found(char *line, char **args)
{
	size_t	i;

	free_tabstr(args);
	i = 0;
	while (line[i] && ft_strchr(SEPARATORS, line[i]) == NULL)
		i++;
	if (line[i])
		line[i] = '\0';
	ft_printf("minishell: %s: command not found\n", line);
	g_returnval = 127;
}

void	ft_printtab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

void	parsing(t_env *environment, char **line)
{
	char	**args;

	args = parse_args(environment, line);
	if (!args)
		return ;
	if (parsing_builtin(environment, args, *line))
		return ;
	else
		command_not_found(*line, args);
}
