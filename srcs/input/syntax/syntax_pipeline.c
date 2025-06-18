/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:06:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 13:32:34 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_following_pipe_token(t_token *token);
static bool	is_invalid_following_word_token(t_token *token);

t_status	syntax_handle_pipeline(t_token **token_list)
{
	t_status	command_handled;

	if ((*token_list)->type == TOKEN_PIPE)
		return (print_syntax_error((*token_list)->value), ERROR);
	command_handled = syntax_handle_command(token_list);
	if (command_handled != SUCCESS)
		return (command_handled);
	if (is_invalid_following_word_token(*token_list))
		return (print_syntax_error((*token_list)->value), ERROR);
	while ((*token_list)->type == TOKEN_PIPE)
	{
		*token_list = (*token_list)->next;
		if (is_invalid_following_pipe_token(*token_list))
			return (print_syntax_error((*token_list)->value), ERROR);
		command_handled = syntax_handle_command(token_list);
		if (command_handled != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

static bool	is_invalid_following_pipe_token(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_OPEN_PARENTHESIS || type == TOKEN_CLOSE_PARENTHESIS
		|| type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_NEW_LINE
		|| type == TOKEN_PIPE);
}

static bool	is_invalid_following_word_token(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_OPEN_PARENTHESIS || type == TOKEN_CLOSE_PARENTHESIS);
}
