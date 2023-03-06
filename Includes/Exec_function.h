/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FUNCTION_H
# define EXEC_FUNCTION_H

///////////////// Get_files.c //////////////////

int	ft_get_fd_infile(t_parser *parser_elem);
int	ft_get_fd_outfile_trunc(t_parser *parser_elem);
int	ft_get_fd_outfile_append(t_parser *parser_elem);

///////////////// Here_doc_handler.c //////////////////

void	ft_get_delimiter_here_doc(t_parser *parser_elem);
int		ft_initialize_recep_tmp_file_heredoc(int *recep_file, char *rnd_name);
int		ft_get_here_doc_traitement(t_parser *parser_elem);


#endif