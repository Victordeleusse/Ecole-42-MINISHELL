/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/24 11:39:23 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_builtin(t_env *environment, char **args, char *line)
{
	if (ft_strcmp(args[0], "echo") == 0)
		ftbuiltin_echo(environment, args);
	if (ft_strcmp(args[0], "cd") == 0)
		ftbuiltin_cd(environment, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ftbuiltin_pwd(environment);
	else if (ft_strcmp(args[0], "export") == 0)
		ftbuiltin_export(environment, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		ftbuiltin_unset(environment, args);
	else if (ft_strcmp(args[0], "env") == 0)
		ftbuiltin_env(environment);
	else if (ft_strcmp(args[0], "exit") == 0)
		ftbuiltin_exit(environment, args, line);
	else
		return (0);
	free_tabstr(args);
	return (1);
}

void	command_not_found(char **args)
{
	ft_printf("minishell: %s: command not found\n", args[0]);
	free_tabstr(args);
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
		command_not_found(args);
}
