/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exit_and_Free.h"
#include "minishell.h"
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

void	ft_free_list(t_env_elem **envp_list)
{
	t_env_elem *begin;
	t_env_elem *current;

	begin = *envp_list;
	while (begin)
	{
		free(begin->name);
		free(begin->value);
		current = begin;
		begin = begin->next;
		free(current);
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_all(t_env_elem **envp_list, char **tab_args)
{
	rl_clear_history();
	free(S_GLOBAL.HOME_PATH);
	ft_free_tab(tab_args);
	ft_free_list(envp_list);
}

void	ft_builtin_exit_function(t_env_elem **envp_list, char **tab_args)
{
	int	nombre;
	int	len;
	int	str_len;

	if (!envp_list || !tab_args)
		return ;
	if (!tab_args[1])
	{
		write(1, "exit\n", 5);
		ft_free_all(envp_list, tab_args);
		S_GLOBAL.GLOBAL_RETURN = 0;
		exit(S_GLOBAL.GLOBAL_RETURN);
	}
	if (tab_args[2])
	{
		write(2, "exit\n", 5);
		ft_message_err(ERR_EXIT_TOO_MANY_ARGS);
		return ;
	}
	len = 0;
	nombre = ft_atoi(tab_args[1], &len);
	str_len = ft_strlen(tab_args[1]);
	if (tab_args[1][0] == '-')
		len++;
	if (len != str_len)
	{
		write(2, "exit\n", 5);
		ft_message_err(ERR_IN_SHELL_EXIT);
		write(2, tab_args[1], str_len);
		write(2, ": numeric argument required\n", 29);
		ft_free_all(envp_list, tab_args);
		exit(S_GLOBAL.GLOBAL_RETURN);
	}
	write(2, "exit\n", 5);
	if (nombre < 0)
	{
		while (nombre <= 0)
			nombre = nombre + 256;
	}
	S_GLOBAL.GLOBAL_RETURN = nombre % 256;
	ft_free_all(envp_list, tab_args);
	exit(S_GLOBAL.GLOBAL_RETURN);
}
