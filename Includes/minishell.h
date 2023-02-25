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
# include "Signal_Message.h"
# include "Export.h"
# include "Unset.h"
# include "Directory.h"
# include "Exit_and_Free.h"

# define ERR_ALLOC	"Erreur lors d'allocation memoire"
# define ERR_IN_SHELL_PWD	"minishell-TitouVictor$: pwd"
# define ERR_IN_SHELL_CD	"minishell-TitouVictor$: cd"
# define ERR_IN_SHELL_EXIT	"minishell-TitouVictor$: exit: "
# define ERR_CD_TOO_MANY_ARGS	"minishell-TitouVictor$: cd: too many arguments"
# define ERR_CD_NO_HOME	"minishell-TitouVictor$: cd: HOME not set"
# define ERR_CD	"cd"
# define ERR_ENV_TOO_MANY_ARGS	"minishell-TitouVictor$: cd: too many arguments"
# define ERR_EXIT_TOO_MANY_ARGS	"minishell-TitouVictor$: exit: too many arguments"

struct S_GLOBAL_MINISHELL
{
	int		GLOBAL_RETURN;
	int		IS_HOME;
	char	*HOME_PATH;
	char	PWD[1024];
};

extern struct S_GLOBAL_MINISHELL S_GLOBAL;

#endif