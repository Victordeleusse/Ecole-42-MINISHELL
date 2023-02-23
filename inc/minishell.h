/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:17:29 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/23 14:09:12 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define PROMPT "minishell →"
# define ERRALLOC "minishell: Could not allocate memory.\n"
# define SEPARATOR -84
# define VARNAMESET "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789_"
# define VARKEY -42

# ifndef true
#  define true 1
# endif

# ifndef false
#  define false 0
# endif

extern int	g_returnval;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
	char			*pwd;
}					t_env;

				/* Built-in Functions */

void	ftbuiltin_pwd(t_env *environment);
void	ftbuiltin_export(t_env *environment, char **args);
void	ftbuiltin_unset(t_env *environment, char **args);
void	ftbuiltin_env(t_env *environment);
void	ftbuiltin_exit(t_env *environment, char **args, char *line);

					/* Parsing */

// parsing.c
void	parsing(t_env *environment, char **line);
// parse_args.c
char	**parse_args(t_env *environment, char **line);
// replace_key_by_value.c
char	*replace_key_by_value(t_env *environment, char *line);
// quotes_interpretation.c
int		quotes_interpretation(t_env *environment, char **line);

				/* One-time actions */

// opening.c
t_env	*opening(int argc, char **argv, char *envp[]);
// closing.c
void	closing_the_program(t_env *environment);
// signal.c
void	change_signal_behavior(void);
// get_environment.c
t_env	*get_environment(char *envp[]);

					/* Utils */

// environment.c
void	free_environment(t_env *environment);
char	*get_value_by_key(t_env *environment, char *key);
int		env_lstaddback(t_env *env, char *key, char *value, int exported);

#endif
