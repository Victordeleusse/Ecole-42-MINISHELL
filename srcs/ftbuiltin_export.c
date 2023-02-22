/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftbuiltin_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:26:08 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 18:15:26 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ftbuiltin_export_noarg(t_env *environnement)
{
	while (environnement)
	{
		if (environnement->key)
		{
			write(1, "export ", 7);
			write(1, environnement->key, ft_strlen(environnement->key));
			write(1, "=", 1);
			write(1, environnement->value, ft_strlen(environnement->value));
			write(1, "\n", 1);
		}
		environnement = environnement->next;
	}
}

static void	ftbuiltin_export_element(t_env *environnement, \
	char *key, char *value)
{
	t_env	*elem;
	
	elem = environnement;
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
		env_lstaddback(environnement, key, value, 1);
}

static int	ftbuiltin_export_key(t_env *environnement, char *arg, char *key, size_t i)
{
	if (!key)
	{
		RETURNVAL = 1;
		return (0);
	}
	if (ft_strchrset(key, "-+/*=") != NULL)
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
		free(key);
		RETURNVAL = 1;
		return (0);
	}
	return (1);
}

static void	ftbuiltin_export_value(t_env *environnement, char *arg, char *key, char *value)
{
	if (!arg)
		ftbuiltin_export_element(environnement, key, NULL);
	else
	{
		value = ft_substr(arg, 1, ft_strlen(arg + 1));
		if (!value)
		{
			free(key);
			RETURNVAL = 1;
			return ;
		}
		ftbuiltin_export_element(environnement, key, value);
	}
}

void	ftbuiltin_export(t_env *environnement, char *arg)
{
	char	*key;
	char	*value;
	size_t	i;
	
	if (!arg)
		ftbuiltin_export_noarg(environnement);
	else
	{
		i = 0;
		while (arg[i] && arg[i] != '=')
			i++;
		key = ft_substr(arg, 0, i);
		if (!ftbuiltin_export_key(environnement, arg, key, i))
			return ;
		arg = arg + i;
		ftbuiltin_export_value(environnement, arg, key, value);
	}
	RETURNVAL = 0;
}
