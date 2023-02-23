/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftbuiltin_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:26:08 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/23 12:10:36 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ftbuiltin_export_noarg(t_env *environment)
{
	while (environment)
	{
		if (environment->key)
		{
			write(1, "export ", 7);
			write(1, environment->key, ft_strlen(environment->key));
			write(1, "=", 1);
			write(1, environment->value, ft_strlen(environment->value));
			write(1, "\n", 1);
		}
		environment = environment->next;
	}
}

static void	ftbuiltin_export_element(t_env *environment, \
	char *key, char *value)
{
	t_env	*elem;
	
	elem = environment;
	if (!key || !elem)
		return ;
	elem = elem->next;
	while (elem)
	{
		if (ft_strcmp(elem->key, key) == 0)
		{
			elem->exported = 1;
			if (value)
			{
				free(elem->value);
				elem->value = value;
			}
			return ;
		}
		elem = elem->next;
	}
	if (value)
		env_lstaddback(environment, key, value, 1);
}

static int	ftbuiltin_export_key(char *arg, char *key, size_t i)
{
	(void) i;
	if (!key)
	{
		g_returnval = 1;
		return (0);
	}
	if (!ft_strinset(key, VARNAMESET, ft_strlen(key) - 1))
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
		free(key);
		g_returnval = 1;
		return (0);
	}
	return (1);
}

static char	*ftbuiltin_export_value(t_env *environment, char *arg, char **key)
{
	char	*value;

	value = NULL;
	if (arg[0] == '\0')
		ftbuiltin_export_element(environment, *key, NULL);
	else
	{
		value = ft_substr(arg, 1, ft_strlen(arg + 1));
		if (!value)
		{
			free(*key);
			*key = NULL;
			g_returnval = 1;
			return (NULL);
		}
		ftbuiltin_export_element(environment, *key, value);
	}
	return (value);
}

void	ftbuiltin_export(t_env *environment, char *arg)
{
	char	*key;
	char	*value;
	size_t	i;
	
	if (!arg)
		ftbuiltin_export_noarg(environment);
	if (*arg == '\0')
		ftbuiltin_export_noarg(environment);
	else
	{
		i = 0;
		while (arg[i] && arg[i] != '=')
			i++;
		key = ft_substr(arg, 0, i);
		if (!ftbuiltin_export_key(arg, key, i))
			return ;
		arg = arg + i;
		value = ftbuiltin_export_value(environment, arg, &key);
	}
	g_returnval = 0;
}
