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

# define ENVIRONMENT_EXCLUDED_SET "+-*/=.<>?!@#%%$^&()"

////////////////////// Environment.c /////////////////////

typedef struct s_env_elem
{
	char				*name;
	char				*value;
	int					is_export;
	struct s_env_elem	*next;
} t_env_elem;

char		**ft_envp_in_tab(t_env_elem	**env_elem_list);
t_env_elem	*ft_generate_new_variable(char *ligne, int is_exported);
void		ft_export_new_variable(char *ligne, t_env_elem **envp_list, int is_exported);
void		ft_add_or_replace_value(t_env_elem **envp_list, char *ligne);

// UTILS //

int			ft_str_detect(char *str, char *set);
int			ft_is_a_variable(char *ligne);
char		*ft_extract_name(char *envp_index);
char		*ft_extract_value(char *envp_index);
void		ft_lst_envp_add_back(t_env_elem **envp_elem_list, t_env_elem *elem);
int			ft_check_variable_name_is_valid(char *ligne);


#endif