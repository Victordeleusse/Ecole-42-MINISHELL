/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:08:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Environment.h"
#include "libft.h"
#include "minishell.h"

// -> Genere ma nouvelle variable, d environnement ou non

static t_env_elem	*ft_generate_env_element(char *envp_index, int is_exported)
{
	t_env_elem	*elem;

	elem = 	ft_calloc(sizeof(t_env_elem), 1);
	if (!elem)
	{
		RETURNVAL = 1;
		return (ft_message_err(ERR_ALLOC), NULL);
	}
	elem->name = ft_extract_name(envp_index);
	elem->value = ft_extract_value(envp_index);
	elem->is_export = is_exported;
	elem->next = NULL;
	return (elem);
}

// -> Exporte ma variable nouvelle (QUE CE SOIT UNE VAR D ENV OU NON) dans l environnement

void	ft_export_variable_in_env(char *new_elem_env, t_env_elem **envp_list, int is_exported)
{
	t_env_elem	*new_elem;

	if (!new_elem_env)
	{
		RETURNVAL = 1;
		return ;
	}
	new_elem = ft_generate_env_element(new_elem_env, is_exported);
	ft_lst_envp_add_back(envp_list, new_elem);
}


// -> Genere une liste chaine contenant l environnement SEULEMENT 
// - INITIALISATION SUR LAQUELLE VIENDRA SE RAJOUTER TOUTES LES VARIABLES, D ENVIRONNEMENT OU NON

t_env_elem	*ft_generate_envp_list(char **envp)
{
	int				i;
	t_env_elem		*env_elem_list;
	t_env_elem		*begin;
	t_env_elem		*next_elem;

	if (!envp || !envp[0])
		return (RETURNVAL = 1, NULL);
	env_elem_list = ft_generate_env_element(envp[0], 1);
	if (!env_elem_list)
		return (RETURNVAL = 1, ft_message_err(ERR_ALLOC), NULL);
	begin = env_elem_list;
	i = 1;
	while (envp[i])
	{
		next_elem = ft_generate_env_element(envp[i], 1);
		if (!next_elem)
			return (RETURNVAL = 1, ft_message_err(ERR_ALLOC), NULL);
		begin->next = next_elem;
		begin = begin->next;
		i++;
	}
	return (env_elem_list);
}

// -> Recuperation de l environnement SEUL sous forme de tableau

char	**ft_envp_in_tab(char **envp) 
{
	int			len;
	int			i;
	t_env_elem	*env_elem_list;
	t_env_elem	*begin;
	char		**envp_tab;

	if (!*envp || !envp[0])
		return (NULL);
	len = 0;
	i = 0;
	env_elem_list = ft_generate_envp_list(envp);
	if (!env_elem_list)
		return (RETURNVAL = 1, ft_message_err(ERR_ALLOC), NULL);
	begin = env_elem_list;
	while (begin)
	{
		if (begin->is_export)
			len++;
		begin = begin->next;
	}
	envp_tab = ft_calloc(sizeof(char *), len + 1);
	if (!envp_tab)
		return (RETURNVAL = 1, ft_message_err(ERR_ALLOC), NULL);
	envp_tab[len] = 0;
	begin = env_elem_list;
	while (begin)
	{
		if (begin->is_export)
		{
			envp_tab[i] = ft_strjoin((const char *)begin->name, "=");
			envp_tab[i] = ft_strjoin((const char *)envp_tab[i], (const char *)begin->value);
		}
		begin = begin->next;
		i++;
	}
	return (envp_tab);
}

