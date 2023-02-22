/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:06:02 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:14:47 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

////////////////////// Environment.c /////////////////////

typedef struct s_env_elem
{
	char				*name;
	char				*value;
	int					is_export;
	struct s_env_elem	*next;
} t_env_elem;

char		**ft_envp_in_tab(char **envp);

// UTILS //

char		*ft_extract_name(char *envp_index);
char		*ft_extract_value(char *envp_index);
void		ft_lst_envp_add_back(t_env_elem **envp_elem_list, t_env_elem *elem);

#endif