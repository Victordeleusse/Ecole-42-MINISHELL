/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct S_GLOBAL_MINISHELL S_GLOBAL;

int	main(int argc, char **argv, char **envp)
{
	t_env_elem	*my_envp;
	// t_env_elem	*begin;
	// char		**args_tab_export;
	// char		export_instruction[] = "export PIERRE==10 NICO TITOU=32";
	// char		**args_tab_export2;
	// char		export_instruction2[] = "export HOME=7";
	// char		**args_tab_unset;
	// char		unset_instruction[] = "unset HOME";
	// char		**args_tab_pwd;
	// char		pwd_instruction[] = "pwd";
	// char		**args_tab_cd;
	// char		cd_instruction[] = "cd ../..";
	// char		**args_tab_env;
	// char		env_instruction[] = "env";
	// char		**args_tab_exit;
	// char		exit_instruction[] = "exit -26";
	char		**args_tab_echo;
	char		echo_instruction[] = "echo -n Bonjour Victor et Titou";
	// int	len;

	// len = 0;
	// ft_get_data();
	(void)argc;
	(void)argv;
	// (void)envp;
	my_envp = ft_generate_envp_list(envp);
	// args_tab_export = ft_split(export_instruction, ' ');
	// args_tab_export2 = ft_split(export_instruction2, ' ');
	// args_tab_unset = ft_split(unset_instruction, ' ');
	// args_tab_pwd = ft_split(pwd_instruction, ' ');
	// args_tab_cd = ft_split(cd_instruction, ' ');
	// args_tab_env = ft_split(env_instruction, ' ');
	args_tab_echo = ft_split(echo_instruction, ' ');
	// ft_builtin_export_function(&my_envp, args_tab_export);
	// ft_builtin_unset_function(&my_envp, args_tab_unset);
	// ft_builtin_export_function(&my_envp, args_tab_export2);
	ft_builtin_echo_function(args_tab_echo);	
	// printf("\n\n");
	// begin = my_envp;
	// while (begin)
	// {
	// 	printf("%s ->", begin->name);
	// 	printf("%s\n", begin->value);
	// 	begin = begin->next;
	// }
	// ft_builtin_get_current_directory();
	// ft_builtin_change_directory(args_tab_cd);
	// ft_builtin_get_current_directory();
	// printf("\n\n%d", S_GLOBAL.IS_HOME);
	// printf("\n\n%s", S_GLOBAL.HOME_PATH);
	// ft_builtin_change_directory();
	// ft_builtin_env_function(&my_envp, args_tab_env);
	// ft_builtin_exit_function(&my_envp, args_tab_exit);
	// printf("valeur : %d -> len : %d\n", ft_atoi(argv[1], &len), len);
	return (0);
}