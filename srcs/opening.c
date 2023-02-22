/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:02:06 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 14:09:56 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	RETURNVAL;

t_env *opening(int argc, char **argv, char *envp[])
{
	t_env	*environnement;

	(void) argc;
	(void) argv;
	RETURNVAL = 0;
	change_signal_behavior();
	environnement = get_environnement(envp);
	return (environnement);
}
