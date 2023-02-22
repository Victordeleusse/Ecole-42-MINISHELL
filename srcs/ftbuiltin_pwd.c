/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftbuiltin_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:49:33 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 14:34:20 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ftbuiltin_pwd(t_env *environnement)
{
	if (environnement && environnement->pwd)
		ft_printf("%s\n", environnement->pwd);
}
