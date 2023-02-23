/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:29:12 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/23 09:15:54 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environnement(t_env *environnement)
{
	t_env	*tmp;

	if (environnement && environnement->pwd)
		free(environnement->pwd);
	while (environnement)
	{
		tmp = environnement;
		environnement = environnement->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

char	*get_value_by_key(t_env *environnement, char *key)
{
	t_env	*current;

	current = environnement;
	if (!current)
		return (NULL);
	current = current->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int		env_lstaddback(t_env *env, char *key, char *value, int exported)
{
	if (!env)
		return (0);
	while (env->next)
		env = env->next;
	env->next = malloc(sizeof(t_env));
	if (!(env->next))
		return (ft_putstr_fd(ERRALLOC, 2), 0);
	env = env->next;
	env->key = key;
	env->value = value;
	env->exported = exported;
	env->next = NULL;
	return (1);
}
