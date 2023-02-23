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

static int	parsing_builtin(t_env *environment, char *line)
{
	char	*arg;

	arg = line;
	while (*arg && !ft_iswhitespace(*arg))
		arg++;
	while (*arg && ft_iswhitespace(*arg))
		arg++;
	if (ft_strncmp(line, "pwd", 3) == 0 \
	&& (ft_iswhitespace(line[3]) || line[3] == '\0'))
		ftbuiltin_pwd(environment);
	else if (ft_strncmp(line, "export", 6) == 0 \
	&& (ft_iswhitespace(line[6]) || line[6] == '\0'))
		ftbuiltin_export(environment, arg);
	else if (ft_strncmp(line, "unset", 5) == 0 \
	&& (ft_iswhitespace(line[5]) || line[5] == '\0'))
		ftbuiltin_unset(environment, arg);
	else if (ft_strncmp(line, "env", 3) == 0 \
	&& (ft_iswhitespace(line[3]) || line[3] == '\0'))
		ftbuiltin_env(environment);
	else if (ft_strncmp(line, "exit", 4) == 0 \
	&& (ft_iswhitespace(line[4]) || line[4] == '\0'))
		ftbuiltin_exit(environment, line);
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
	g_returnval = 127;
}

void	parsing(t_env *environment, char **line)
{
	if (!line_formatting(environment, line))
		return ;
	if (**line == '\0')
		return ;
	ft_printf("|%s|\n", *line);
	return ;
	if (parsing_builtin(environment, *line))
		return ;
	else
		command_not_found(*line);
}
