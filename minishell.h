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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>

# include "Libft_vde-leus/libft.h"

# define ERR_ALLOC	"Erreur lors d'allocation memoire"

extern int RETURNVAL;

////////////////////// Environment.c /////////////////////

typedef struct s_env_elem
{
	char				*name;
	char				*value;
	int					is_export;
	struct s_env_elem	*next;
}t_env_elem;

char		**ft_envp_in_tab(char **envp);

// UTILS //

char		*ft_extract_name(char *envp_index);
char		*ft_extract_value(char *envp_index);
void		ft_lst_envp_add_back(t_env_elem **envp_elem_list, t_env_elem *elem);

////////////////////// Signal.c /////////////////////

void		ft_get_data(void);
t_env_elem	*ft_generate_envp_list(char **envp);
void		ft_export_variable(char *new_elem_env, t_env_elem **envp_list);

void		ft_message_err(char	*str);

#endif