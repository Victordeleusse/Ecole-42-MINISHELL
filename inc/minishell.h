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
# define SEPARATORS " \n\r\t\b\f\v"
extern int RETURNVAL;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
	char			*pwd;
}					t_env;

/* Built-in Functions */
void	ftbuiltin_pwd(t_env *environnement);
void	ftbuiltin_export(t_env *environnement, char *arg);
void	ftbuiltin_unset(t_env *environnement, char *arg);
void	ftbuiltin_env(t_env *environnement);
void	ftbuiltin_exit(t_env *environnement, char *line);

// opening.c
t_env	*opening(int argc, char **argv, char *envp[]);

// signal.c
void	change_signal_behavior(void);

// environnement.c
void	free_environnement(t_env *environnement);
char	*get_value_by_key(t_env *environnement, char *key);
int		env_lstaddback(t_env *env, char *key, char *value, int exported);

// get_environnement.c
t_env	*get_environnement(char *envp[]);

// parsing.c
void	parsing(t_env *environnement, char *line);

// closing.c
void	closing_the_program(t_env *environnement);

#endif
