/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:36:51 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/27 15:43:39 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	parsing_builtin(t_env *environment, char **args, \
// 	char **cmds, size_t cmdnbr)
// {
// 	size_t	size;

// 	size = 0;
// 	while (cmds[size])
// 		size++;
// 	if (ft_strcmp(args[0], "echo") == 0)
// 		ftbuiltin_echo(args);
// 	else if (ft_strcmp(args[0], "cd") == 0)
// 	{
// 		if (cmdnbr == size - 1)
// 			ftbuiltin_cd(environment, args);
// 	}
// 	else if (ft_strcmp(args[0], "pwd") == 0)
// 		ftbuiltin_pwd(environment);
// 	else if (ft_strcmp(args[0], "export") == 0)
// 	{
// 		if (size == 1)
// 			ftbuiltin_export(environment, args);
// 		else
// 			g_returnval = 0;
// 	}
// 	else if (ft_strcmp(args[0], "unset") == 0)
// 	{
// 		if (size == 1)
// 			ftbuiltin_unset(environment, args);
// 		else
// 			g_returnval = 0;
// 	}
// 	else if (ft_strcmp(args[0], "env") == 0)
// 		ftbuiltin_env(environment);
// 	else if (ft_strcmp(args[0], "exit") == 0)
// 		ftbuiltin_exit(environment, args, cmds);
// 	else
// 		return (0);
// 	free_tabstr(args);
// 	return (1);
// }

void	parse_cmd(t_env *environment, char **cmds, char **line, size_t cmdnbr)
{
	char	**args;
	// pid_t	pid;
	
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
	(void) cmdnbr;
	// else if (parsing_builtin(environment, args, cmds, cmdnbr))
	// 	return ;
	// pid = fork();
	// if (pid == 0)
	// {
	execute_cmd(environment, args);
	free_tabstr(cmds);
	closing_the_program(environment);
	exit(g_returnval);	
	// }
	// else
		// wait(&g_returnval);
	free_tabstr(args);
}
