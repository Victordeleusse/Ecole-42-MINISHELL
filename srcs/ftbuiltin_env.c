/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftbuiltin_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:25:33 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 16:25:57 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ftbuiltin_env(t_env *environnement)
{
	while (environnement)
	{
		if (environnement->key && environnement->exported)
		{
			write(1, environnement->key, ft_strlen(environnement->key));
			write(1, "=", 1);
			write(1, environnement->value, ft_strlen(environnement->value));
			write(1, "\n", 1);
		}	
		environnement = environnement->next;
	}
	RETURNVAL = 0;
}
