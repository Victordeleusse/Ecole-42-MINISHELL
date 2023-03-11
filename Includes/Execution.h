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

typedef enum s_outfile_type
{
	OUT_TRUNC = 1,
	OUT_APPEND,
}t_outfile_type;

typedef struct s_pipe
{
	int	fds[2];
	int	is_open;
} t_pipe;

typedef struct s_exec
{
	int				index;
	int				is_valid;
	int				previous_valid;
	pid_t			pid;
	char			*infile;
	int				fd_infile;
	int				fd_here_doc;
	char			*delimiter;
	int				is_a_quote_delimiter;
	char			*outfile;
	t_outfile_type	outfile_type;
	int				fd_outfile;
	char			**tab_cmd_args;
	char			**env;
	char			*env_path;
	char			**command_paths;
	struct s_exec	*next;
}t_exec;

//////////////// Pipe.c ///////////////////

void	ft_init_pipes(t_pipe *pipes);
void	ft_close(int *fd);
void	ft_swap_pipes(t_pipe *pipes);
void	ft_clean_one_pipe(t_pipe *pipe);
void	ft_dup(t_exec *exec_elem, t_pipe *pipes);

//////////////// Pipex_utils.c ///////////////////

char	*ft_get_env_path(t_env_elem *envp_list);
int		ft_get_infile(t_exec *exec_elem);
int		ft_get_outfile(t_exec *exec_elem);
char	*ft_get_command_for_the_pipe(t_exec *exec_elem);
void	ft_init_pipes(t_pipe *pipes);
void	ft_make_children(t_exec *exec_elem, t_pipe *pipes);
void	ft_exec(t_exec *exec_elem, t_pipe *pipes);

//////////////// Generate_exec_list.c ///////////////////

t_exec	*ft_generate_executable(t_env_elem *envp_list, t_parser *parser_list);
t_exec	*ft_generate_exec_list(t_env_elem *envp_list, t_parser *parser_list, int *nb_cmd);

//////////////// Launch_exec.c ////////////////

void	ft_launch_exec(t_exec *exec_list, int *nb_cmd);


#endif