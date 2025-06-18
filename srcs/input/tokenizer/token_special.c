/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:25:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 10:56:43 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void	handle_new_line_token(t_token *token);
void	handle_operator_token(t_token *token, char *str);
void	handle_io_number_token(t_token *token, char *str);
bool	ft_is_ionumber(char *str);

/* =============== Definition ================ */

void	handle_new_line_token(t_token *token)
{
	token->type = TOKEN_NEW_LINE;
	token->value = ft_strdup("newline");
}

void	handle_io_number_token(t_token *token, char *str)
{
	char	*p_redirection;

	p_redirection = ft_str_contains_any(str, "<>");
	token->type = TOKEN_IO_NUMBER;
	token->value = ft_strndup(str, p_redirection - str);
}

void	handle_eof_token(t_token *token)
{
	token->type = TOKEN_EOF;
	token->value = ft_strdup("");
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
