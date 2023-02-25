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

# define ERR_ALLOC	"Erreur lors d'allocation memoire"
# define ERR_IN_SHELL	"minishell-TitouVictor$: "

struct S_GLOBAL_MINISHELL
{
	int		GLOBAL_RETURN;
	char	*PWD;
};

extern struct S_GLOBAL_MINISHELL S_GLOBAL;

#endif