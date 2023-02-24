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

static t_env_elem	*ft_generate_new_variable(char *ligne, int is_exported)
{
	t_env_elem	*elem;

	elem = 	ft_calloc(sizeof(t_env_elem), 1);
	if (!elem)
	{
		GLOBAL_RETURNVAL = 1;
		return (ft_message_err(ERR_ALLOC), NULL);
	}
	elem->name = ft_extract_name(ligne);
	elem->value = ft_extract_value(ligne);
	elem->is_export = is_exported;
	elem->next = NULL;
	return (elem);
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
		return (GLOBAL_RETURNVAL = 1, NULL);
	env_elem_list = ft_generate_new_variable(envp[0], 1);
	if (!env_elem_list)
		return (GLOBAL_RETURNVAL = 1, ft_message_err(ERR_ALLOC), NULL);
	begin = env_elem_list;
	i = 1;
	while (envp[i])
	{
		next_elem = ft_generate_new_variable(envp[i], 1);
		if (!next_elem)
			return (GLOBAL_RETURNVAL = 1, ft_message_err(ERR_ALLOC), NULL);
		begin->next = next_elem;
		begin = begin->next;
		i++;
	}
	return (env_elem_list);
}


// -> Exporte ma variable nouvelle (QUE CE SOIT UNE VAR D ENV OU NON) dans l environnement

void	ft_export_new_variable(t_env_elem **envp_list, char *ligne, int is_exported)
{
	t_env_elem	*new_elem;
	int			len_name;

	if (!ligne)
	{
		GLOBAL_RETURNVAL = 1;
		return ;
	}
	new_elem = ft_generate_new_variable(ligne, is_exported);
	len_name = ft_strlen(new_elem->name);
	if (new_elem->name[len_name - 1] == '+')
		new_elem->name[len_name - 1] = '\0';
	ft_lst_envp_add_back(envp_list, new_elem);
}

// Gestion de remplacement ou ajout de la value avec une VARIABLE DEJA PRESENTE 

void	ft_add_or_replace_value(t_env_elem **envp_list, char *ligne)
{
	char		*name;
	char		*new_value;
	t_env_elem	*element;
	int			to_add;
	int			len_name;
	char		*tmp;

	element = *envp_list;
	to_add = 0;
	name = ft_extract_name(ligne);
	len_name = ft_strlen(name);
	new_value = ft_extract_value(ligne);
	if (name[len_name - 1] == '+')
	{
		to_add = 1;
		name[len_name - 1] = '\0';
	}
	while (ft_strcmp(element->name, name))
		element = element->next;
	if (to_add)
	{	
		tmp = ft_strjoin(element->value, new_value);
		free(element->value);
		free(new_value);
		element->value = tmp;
	}
	else
	{
		free(element->value);
		element->value = new_value;
	}
	free(name);
}

// -> Recuperation de l environnement sous forme de tableau

char	**ft_envp_in_tab(t_env_elem	**env_elem_list)
{
	int			len;
	int			i;
	t_env_elem	*begin;
	char		**envp_tab;

	if (!(*env_elem_list))
		return (NULL);
	begin = *env_elem_list;
	len = 0;
	while (begin)
	{
		if (begin->is_export)
			len++;
		begin = begin->next;
	}
	envp_tab = ft_calloc(sizeof(char *), len + 1);
	if (!envp_tab)
		return (GLOBAL_RETURNVAL = 1, ft_message_err(ERR_ALLOC), NULL);
	envp_tab[len] = 0;
	begin = *env_elem_list;
	i = 0;
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

