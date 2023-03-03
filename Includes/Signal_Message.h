/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_Message.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:06:02 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:14:47 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MESSAGE_H
# define SIGNAL_MESSAGE_H

////////////////////// Signal.c /////////////////////

void	ft_signal_ctrl_c(int sig);

////////////////////// Message.c /////////////////////

void		ft_message_err(char	*str);
void		ft_message_unexpected_token(char *str, char *token_str);


#endif
