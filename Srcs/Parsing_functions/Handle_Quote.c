/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_Quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// To handle "$ENV_VAR" vs. '$ENV_VAR' or "$ ENV_VAR"

int	ft_handle_dollar(t_env_elem *envp_list, t_token *token_list)
{
	t_token	*token_begin;
	int		i;

	(void)envp_list;
	token_begin = token_list;
	while (token_begin)
	{
		if (ft_detect_dollar_out_of_simple_quote(token_begin))
		{
			i = 0;
			while (token_begin->string[i])
			{
				while (token_begin->string[i] && token_begin->string[i] != '$')
					i++;
				if (token_begin->string[i] && token_begin->string[i] == '$' && token_begin->string[i + 1] && token_begin->string[i + 1] != ' ')
				{	
					if (!ft_substitute_dollar_env_var(envp_list, token_begin, i))
					{
						ft_free_env_list(&envp_list);
						ft_free_token_list(token_list);
						fprintf(stderr, "ERREUR GESTION DES QUOTES\n");
						S_GLOBAL.GLOBAL_RETURN = 1;
						return (0);
					}	
				}
				i++;
			}
		}
		token_begin = token_begin->next;
	}
	return (1);
}

// To handle SINGLE and DOUBLE QUOTES

int	ft_clean_quote_token_list(t_token *token_list, int *is_open_simple, int *is_open_double)
{
	t_token	*token_begin;

	token_begin = token_list;	
	if ((*is_open_simple) && (*is_open_double))
		return (0);
	while (token_begin)
	{
		while (token_begin && token_begin->symbol != SINGLE_LEFT && token_begin->symbol != DOUBLE_LEFT)
			token_begin = token_begin->next;
		if (token_begin && token_begin->symbol == SINGLE_LEFT)
		{	
			if (!ft_handle_single(token_begin, is_open_double))
			{	
				fprintf(stderr, "SINGLE : PROBLEME PARCING DETECTE - QUOTES OUVERTS\n");
				return (0);
			}
		}
		if (token_begin && token_begin->symbol == DOUBLE_LEFT)
		{
			if (!ft_handle_double(token_begin, is_open_simple))
			{	
				fprintf(stderr, "DOUBLE : PROBLEME PARCING DETECTE - QUOTES OUVERTS\n");
				return (0);
			}
		}
		if (token_begin)
			token_begin = token_begin->next;
	}
	ft_clean_whitespace(token_list);
	return (1);
}

