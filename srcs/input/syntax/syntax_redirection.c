/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:30:55 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 15:38:40 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_redirection(t_token **token_list)
{
	if (!is_redirection(*token_list))
		return (NOOP);
	return (syntax_check_redirection_sequence(token_list));
}

bool	is_redirection(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
		return (true);
	if (token->type == TOKEN_REDIR_HEREDOC || token->type == TOKEN_REDIR_APPEND)
		return (true);
	return (false);
}

bool	syntax_check_redirection_sequence(t_token **token_list)
{
	t_token	*token;
	bool	is_valid_syntax;

	token = *token_list;
	is_valid_syntax = token->next->type == TOKEN_WORD;
	if (is_valid_syntax)
		*token_list = token->next->next;
	return (is_valid_syntax);
}
