/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:30:55 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 15:01:27 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_redirection(t_token **token_list)
{
	t_token	*head_token;
	bool	has_io_number;

	head_token = *token_list;
	has_io_number = head_token->type == TOKEN_IO_NUMBER;
		// TODO: check max value authorized for io_number
	if (has_io_number)
		head_token = head_token->next;
	if (has_io_number && !is_redirection_op(head_token))
		return (ERROR);
	else if (is_redirection_op(head_token))
		head_token = head_token->next;
	else
		return (NOOP);
	if (head_token->type != TOKEN_WORD)
		return (ERROR);
	*token_list = head_token->next;
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
