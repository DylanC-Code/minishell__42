/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:06:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 15:41:14 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_following_pipe_token(t_token *token);
static bool	is_invalid_following_word_token(t_token *token);

t_status	syntax_handle_pipeline(t_app *app, t_token **token_list)
{
	t_status	command_handled;
	t_token		*token;

	token = *token_list;
	if (token->type == TOKEN_PIPE)
		return (unexpected_token_error(app, token->value), ERROR);
	command_handled = syntax_handle_command(app, &token);
	if (command_handled != SUCCESS)
		return (command_handled);
	if (is_invalid_following_word_token(token))
		return (unexpected_token_error(app, token->value), ERROR);
	while (token->type == TOKEN_PIPE)
	{
		token = token->next;
		if (is_invalid_following_pipe_token(token))
			return (unexpected_token_error(app, token->value), ERROR);
		command_handled = syntax_handle_command(app, &token);
		if (command_handled != SUCCESS)
			return (ERROR);
	}
	*token_list = token;
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
