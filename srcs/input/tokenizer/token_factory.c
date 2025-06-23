/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:23:42 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 21:55:30 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

t_token	*get_token(char *str, t_garbage **gb_list);

/* =============== Definition ================ */

t_token	*get_token(char *str, t_garbage **gc)
{
	t_token	*new_token;

	new_token = gc_malloc(sizeof(t_token), gc);
	ft_bzero(new_token, sizeof(t_token));
	if (*str == '\'')
		handle_single_quote_token(new_token, str, gc);
	else if (*str == '"')
		handle_double_quote_token(new_token, str, gc);
	else if (ft_ischarset(*str, OPERATORS))
		handle_operator_token(new_token, str, gc);
	else if (*str == '\n')
		handle_new_line_token(new_token, gc);
	else if (ft_is_ionumber(str))
		handle_io_number_token(new_token, str, gc);
	else if (*str)
		handle_word_token(new_token, str, gc);
	if (new_token->value)
		return (new_token);
	return (NULL);
}
