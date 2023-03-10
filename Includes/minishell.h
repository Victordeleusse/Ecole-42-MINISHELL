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

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h> 
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdbool.h>

# include "libft.h"
# include "Environment.h"
# include "Signal_Message.h"
# include "Export.h"
# include "Unset.h"
# include "Directory.h"
# include "Exit_and_Free.h"
# include "Echo.h"
# include "Parsing_Tokens.h"
# include "Parsing_Parsers.h"
# include "Files.h"
# include "Execution.h"

# define ERR_ALLOC	"Erreur lors d'allocation memoire"
# define ERR_HERE_DOC	"Here_doc : Erreur lors d'allocation du fichier temporaire"
# define ERR_STOP_HERE_DOC	"minishell-TitouVictor$: warning: here-document delimited by end-of-file (wanted `end')"
# define ERR_IN_SHELL_PWD	"minishell-TitouVictor$: pwd"
# define ERR_IN_SHELL_CD	"minishell-TitouVictor$: cd"
# define ERR_IN_SHELL_EXIT	"minishell-TitouVictor$: exit: "
# define ERR_CD_TOO_MANY_ARGS	"minishell-TitouVictor$: cd: too many arguments"
# define ERR_CD_NO_HOME	"minishell-TitouVictor$: cd: HOME not set"
# define ERR_CD	"cd"
# define ERR_ENV_TOO_MANY_ARGS	"minishell-TitouVictor$: cd: too many arguments"
# define ERR_EXIT_TOO_MANY_ARGS	"minishell-TitouVictor$: exit: too many arguments"
# define ERR_EXIT_NUM_ARG_REQUIRED "numeric argument required"

struct S_GLOBAL_MINISHELL
{
	int		GLOBAL_RETURN;
	int		IS_HOME;
	char	*HOME_PATH;
	char	*PWD;
};

extern struct S_GLOBAL_MINISHELL S_GLOBAL;

#endif