/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:23:42 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 12:13:09 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

t_token	*get_token(char *str, t_garbage **gb_list);

/* =============== Definition ================ */

t_token	*get_token(char *str, t_garbage **gb_list)
{
	t_token	*new_token;

	new_token = gc_malloc(sizeof(t_token), gb_list);
	ft_bzero(new_token, sizeof(t_token));
	if (*str == '\'')
		handle_single_quote_token(new_token, str);
	else if (*str == '"')
		handle_double_quote_token(new_token, str);
	else if (ft_ischarset(*str, OPERATORS))
		handle_operator_token(new_token, str);
	else if (*str == '\n')
		handle_new_line_token(new_token);
	else if (ft_isdigit(*str) && ft_ischarset(str[1], "<>"))
		handle_io_number_token(new_token, *str);
	else if (*str)
		handle_word_token(new_token, str);
	else
		handle_eof_token(new_token);
	if (new_token->value)
		return (add_to_gc(gb_list, new_token->value), new_token);
	return (NULL);
}
