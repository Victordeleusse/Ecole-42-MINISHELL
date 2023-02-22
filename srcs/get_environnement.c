/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environnement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:47:36 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 16:47:43 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	get_environnement_pwd(t_env *environnement)
{
	environnement->pwd = get_value_by_key(environnement, "PWD");
	if (!(environnement->pwd))
		environnement->pwd = get_value_by_key(environnement, "OLDPWD");
	if (!(environnement->pwd))
		environnement->pwd = "/";
	environnement->pwd = ft_strdup(environnement->pwd);
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
	get_environnement_pwd(environnement);
	return (environnement);
}
