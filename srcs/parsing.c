/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/24 16:04:02 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_builtin(t_env *environment, char **args, char *line)
{
	if (ft_strcmp(args[0], "echo") == 0)
		ftbuiltin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
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

void	parsing(t_env *environment, char **line)
{
	char	**args;
	pid_t	pid;

	args = parse_args(environment, line);
	if (!args)
		return ;
	else if (!args[0])
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		free_tabstr(args);
		g_returnval = 127;
		return ;
	}
	else if (parsing_builtin(environment, args, *line))
		return ;
	pid = fork();
	if (pid == 0)
	{
		execute_cmd(environment, args);
		free(*line);
		closing_the_program(environment);
		ft_printf("Dans le fils g_returnval = %d\n", g_returnval);
		exit(g_returnval);	
	}
	else
		wait(&g_returnval);
	g_returnval = WEXITSTATUS(g_returnval);
	free_tabstr(args);
}
