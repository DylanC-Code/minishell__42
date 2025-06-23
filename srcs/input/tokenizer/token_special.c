/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:25:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 21:52:03 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void	handle_new_line_token(t_token *token, t_garbage **gc);
void	handle_io_number_token(t_token *token, char *str, t_garbage **gc);
bool	ft_is_ionumber(char *str);

/* =============== Definition ================ */

void	handle_new_line_token(t_token *token, t_garbage **gc)
{
	token->type = TOKEN_NEW_LINE;
	token->value = ft_strdup("newline", gc);
}

void	handle_io_number_token(t_token *token, char *str, t_garbage **gc)
{
	char	*p_redirection;

	p_redirection = ft_str_contains_any(str, "<>");
	token->type = TOKEN_IO_NUMBER;
	token->value = ft_strndup(str, p_redirection - str, gc);
}

void	handle_eof_token(t_token *token, t_garbage **gc)
{
	token->type = TOKEN_EOF;
	token->value = ft_strdup("", gc);
}

bool	ft_is_ionumber(char *str)
{
	size_t	i;

	i = 0;
	if (!ft_isdigit(str[i++]))
		return (false);
	while (ft_isdigit(str[i++]))
		if (i > 12)
			return (false);
	return (str[i - 1] == '<' || str[i - 1] == '>');
}
