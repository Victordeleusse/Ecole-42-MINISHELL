/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstaddback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:47:36 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 16:47:43 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_lstaddback(t_env *env, char *key, char *value, int exported)
{
	printf("%p | %s | %s | %d\n", env, key, value, exported);
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
