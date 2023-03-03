/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_message_err(char	*str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	S_GLOBAL.GLOBAL_RETURN = 1;
}

void	ft_message_unexpected_token(char *str, char *token_str)
{
	write(2, str, ft_strlen(str));
	if (token_str && ft_strcmp(token_str, ""))
	{
		write(2, "'", 1);
		write(2, token_str, ft_strlen(token_str));
		write(2, "'", 1);
	}
	write(2, "\n", 1);
	S_GLOBAL.GLOBAL_RETURN = 1;
}
