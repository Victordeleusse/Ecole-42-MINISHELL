/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:06:02 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:14:47 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Environment.h"

# define ERR_ALLOC	"Erreur lors d'allocation memoire"

extern int RETURNVAL;

////////////////////// Signal.c /////////////////////

void		ft_get_data(void);
t_env_elem	*ft_generate_envp_list(char **envp);
void		ft_export_variable_in_env(char *new_elem_env, t_env_elem **envp_list, int is_exported);
int			ft_check_is_already_present_and_exported(t_env_elem **envp_elem_list, char *str_entry);

void		ft_message_err(char	*str);

#endif