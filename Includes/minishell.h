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

extern int GLOBAL_RETURNVAL;

#endif