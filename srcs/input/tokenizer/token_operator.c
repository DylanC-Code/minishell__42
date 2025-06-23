/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:48:42 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 21:51:08 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void		handle_operator_token(t_token *token, char *str, t_garbage **gc);
static void	handle_operator_token_type(t_token *token);
static void	handle_single_char_operator(t_token *token);
static void	handle_double_char_operator(t_token *token);

/* =============== Definition ================ */

void	handle_operator_token(t_token *token, char *str, t_garbage **gc)
{
	if (str[0] == str[1] && ft_ischarset(*str, "<>|&"))
		token->value = ft_strndup(str, 2, gc);
	else
		token->value = ft_strndup(str, 1, gc);
	handle_operator_token_type(token);
}

static void	handle_operator_token_type(t_token *token)
{
	if (ft_strlen(token->value) == 1)
		handle_single_char_operator(token);
	else if (ft_strlen(token->value) == 2)
		handle_double_char_operator(token);
}

static void	handle_single_char_operator(t_token *token)
{
	if (*token->value == '|')
		token->type = TOKEN_PIPE;
	else if (*token->value == '<')
		token->type = TOKEN_REDIR_IN;
	else if (*token->value == '>')
		token->type = TOKEN_REDIR_OUT;
	else if (*token->value == '(')
		token->type = TOKEN_OPEN_PARENTHESIS;
	else if (*token->value == ')')
		token->type = TOKEN_CLOSE_PARENTHESIS;
}

static void	handle_double_char_operator(t_token *token)
{
	if (*token->value == '|')
		token->type = TOKEN_OR;
	else if (*token->value == '<')
		token->type = TOKEN_REDIR_HEREDOC;
	else if (*token->value == '>')
		token->type = TOKEN_REDIR_APPEND;
	else if (*token->value == '&')
		token->type = TOKEN_AND;
}
