/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftbuiltin_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:15:33 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 18:20:47 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ftbuiltin_unset_element(t_env *environnement, char *arg)
{
	t_env	*elem;
	t_env	*tmp;
	
	elem = environnement;
	if (!arg || !elem)
		return ;
	while (elem && elem->next)
	{
		if (ft_strcmp(elem->next->key, arg) == 0)
		{
			tmp = elem->next;
			elem->next = elem->next->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		elem = elem->next;
	}
}

void	ftbuiltin_unset(t_env *environnement, char *arg)
{
	RETURNVAL = 0;
	if (!arg)
		return ;
	else if (ft_strchrset(arg, "-+/*=") != NULL)
	{
		ft_printf("minishell: unset: `%s': not a valid identifier\n", arg);
		RETURNVAL = 1;
		return ;
	}
	else
		ftbuiltin_unset_element(environnement, arg);
}
