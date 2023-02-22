/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:29:12 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 16:47:18 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environnement(t_env *environnement)
{
	t_env	*tmp;

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

static t_env	*env_initialisation(void)
{
	t_env	*environnement;

	environnement = malloc(sizeof(t_env));
	if (!environnement)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	environnement->key = NULL;
	environnement->value = NULL;
	environnement->exported = 1;
	environnement->next = NULL;
	return (environnement);
}

static t_env	*env_nextelement(char *envp[], size_t i, size_t j)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	element->key = ft_substr(envp[i], 0, j);
	element->value = ft_substr(envp[i], j + 1, ft_strlen(envp[i] + j + 1));
	element->exported = 1;
	element->next = NULL;
	return (element);
}

t_env	*get_environnement(char *envp[])
{
	size_t	i;
	size_t	j;
	t_env	*environnement;
	t_env	*current_line;

	environnement = env_initialisation();
	current_line = environnement;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (envp[i][j])
		{
			current_line->next = env_nextelement(envp, i, j);
			current_line = current_line->next;
			if (!current_line)
				return (free_environnement(environnement), NULL);
		}
		i++;
	}
	return (environnement);
}
