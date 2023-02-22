/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:17:29 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/22 18:15:47 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define ERRALLOC "minishell: Could not allocate memory.\n"

extern int RETURNVAL;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}					t_env;

/* Built-in Functions */
void	ftbuiltin_env(t_env *environnement);
void	ftbuiltin_export(t_env *environnement, char *arg);
void	ftbuiltin_unset(t_env *environnement, char *arg);

// opening.c
t_env	*opening(int argc, char **argv, char *envp[]);

// signal.c
void	change_signal_behavior(void);

// environnement.c
void	free_environnement(t_env *environnement);
int		env_lstaddback(t_env *env, char *key, char *value, int exported);
t_env	*get_environnement(char *envp[]);

// closing.c
void	closing_the_program(t_env *environnement);

#endif
