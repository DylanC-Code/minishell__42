/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:30:55 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 18:12:44 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_redirection(t_token **token_list)
{
	t_token	*token;
	bool	has_io_number;

	token = *token_list;
	has_io_number = token->type == TOKEN_IO_NUMBER;
	if (has_io_number)
		token = token->next;
	if (!is_redirection_op(token))
		return (NOOP);
	token = token->next;
	if (token->type == TOKEN_EOF)
		return (print_syntax_error("newline'"), ERROR);
	if (token->type != TOKEN_WORD)
		return (print_syntax_error(token->value), ERROR);
	*token_list = token->next;
	return (SUCCESS);
}

bool	is_redirection_op(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
		return (true);
	if (token->type == TOKEN_REDIR_HEREDOC || token->type == TOKEN_REDIR_APPEND)
		return (true);
	return (false);
}

bool	is_redirection_sequence(t_token *token)
{
	return (token->type == TOKEN_IO_NUMBER || is_redirection_op(token));
}

void	consume_redirection_sequence(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	if (token->type == TOKEN_IO_NUMBER)
		token = token->next;
	*token_list = token->next->next;
}
