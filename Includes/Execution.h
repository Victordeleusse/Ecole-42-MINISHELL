/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_exec
{
	int				index;
	int				is_valid;
	char			*infile;
	int				fd_infile;
	char			*outfile;
	int				fd_outfile;
	char			**tab_cmd_args;
	t_env_elem		*envp_list;
	struct s_exec	*next;
}t_exec;

//////////////// Generate_exec_list.c ///////////////////

t_exec	*ft_generate_executable(t_env_elem *envp_list, t_parser *parser_list);
t_exec	*ft_generate_exec_list(t_env_elem *envp_list, t_parser *parser_list);

#endif