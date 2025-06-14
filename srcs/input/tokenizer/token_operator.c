/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:48:42 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 12:16:01 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void		handle_operator_token(t_token *token, char *str);
static void	handle_operator_token_type(t_token *token, char *str);
static void	handle_single_char_operator(t_token *token, char *operator);
static void	handle_double_char_operator(t_token *token, char *operator);

/* =============== Definition ================ */

void	handle_operator_token(t_token *token, char *str)
{
	handle_operator_token_type(token, str);
	if (str[0] != str[1])
		token->value = ft_strndup(str, 1);
	else
		token->value = ft_strndup(str, 2);
}

static void	handle_operator_token_type(t_token *token, char *str)
{
	if (ft_strlen(str) == 1)
		handle_single_char_operator(token, str);
	else if (ft_strlen(str) == 2)
		handle_double_char_operator(token, str);
}

static void	handle_single_char_operator(t_token *token, char *operator)
{
	if (*operator == '|')
		token->type = TOKEN_PIPE;
	else if (*operator == '<')
		token->type = TOKEN_REDIR_IN;
	else if (*operator == '>')
		token->type = TOKEN_REDIR_OUT;
	else if (*operator == '(')
		token->type = TOKEN_OPEN_PARENTHESE;
	else if (*operator == ')')
		token->type = TOKEN_CLOSE_PARENTHESE;
}

static void	handle_double_char_operator(t_token *token, char *operator)
{
	if (*operator == '|')
		token->type = TOKEN_OR;
	else if (*operator == '<')
		token->type = TOKEN_REDIR_APPEND;
	else if (*operator == '>')
		token->type = TOKEN_REDIR_HEREDOC;
	else if (*operator == '&')
		token->type = TOKEN_AND;
}
