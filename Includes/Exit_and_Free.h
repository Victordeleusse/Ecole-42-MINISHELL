/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_AND_FREE_H
# define EXIT_AND_FREE_H

# include "Environment.h"

void	ft_free_list(t_env_elem **envp_list);
void	ft_free_tab(char **tab);
void	ft_free_all(t_env_elem **envp_list, char **tab_args);
void	ft_builtin_exit_function(t_env_elem **envp_list, char **tab_args);

#endif