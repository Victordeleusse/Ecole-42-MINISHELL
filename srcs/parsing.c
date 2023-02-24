/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:18:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/24 17:45:21 by tchevrie         ###   ########.fr       */
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

void	_parse_cmd(t_env *environment, char **cmds, char **line)
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
		free_tabstr(cmds);
		closing_the_program(environment);
		exit(g_returnval);	
	}
	else
		wait(&g_returnval);
	g_returnval = WEXITSTATUS(g_returnval);
	free_tabstr(args);
}

// char	*change_local_variables(char *line)
// {
// 	char	*var;
// 	size_t	i;

// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (ft_iswhitespace(line[i]))
// 		i++;
// 	var = line + i;
// 	while (ft_inset(line[i], VARNAMESET))
// 		i++;
// 	if (var == line + i || line[i] != '=')
// 		return (line);
// 	return (line);
// }

/*
	On fait une variable avec la clef
	On donne a une fonction la key et la str a partir du '=' + 1
	Celle-ci trouve la valeur correspondante, et exporte le tout en var locale et renvoie un pointeur vers le caracter apres la fin de la value
	ce qui est renvoye est donc la nouvelle line, maintenant videe de key=value
	Et tant qu'on trouve une variable a export localement, on reproduit le tout a nouveau
*/

void	parsing(t_env *environment, char **line)
{
	char	**cmds;
	size_t	i;

	cmds = split_cmds(line);
	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		cmds[i] = ft_strip(cmds[i]);
		// cmds[i] = change_local_variables(cmds[i]);
		_parse_cmd(environment, cmds, cmds + i);
		i++;
	}
	free_tabstr(cmds);
}
