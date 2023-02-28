/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:59:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define SPECIAL_ARGS	">|<&"

typedef enum s_symbol
{
	SINGLE_LEFT,
	DOUBLE_LEFT,
	SINGLE_RIGHT,
	DOUBLE_RIGHT,
	SIMPLE_PIPE,
	DIR_RIGHT,
	DIR_LEFT
} t_symbol;

typedef struct s_token
{
	int				is_symbol;
	t_symbol		symbol;
	char			*string;
	struct s_token	*next;
} t_token;

int		ft_is_special_character(char c);
int		ft_is_separator(char c);
t_token	ft_generate_token(char *str, int *is_open_simple, int *is_open_double);

int	ft_parsing_function(char *command_buffer);

#endif