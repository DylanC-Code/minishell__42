/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_or_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:18:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:54:34 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_and_or_token(t_token *token);
static bool	is_invalid_token(t_token *token);

t_status	syntax_handle_and_or_command(t_app *app, t_token **token_list)
{
	t_status	pipeline_handled;
	t_token		*token;

	token = *token_list;
	if (is_and_or_token(token))
		return (unexpected_token_error(app, token->value), ERROR);
	pipeline_handled = syntax_handle_pipeline(app, &token);
	if (pipeline_handled != SUCCESS)
		return (pipeline_handled);
	while (is_and_or_token(token))
	{
		token = token->next;
		if (is_invalid_token(token))
			return (unexpected_token_error(app, token->value), ERROR);
		pipeline_handled = syntax_handle_pipeline(app, &token);
		if (pipeline_handled == ERROR)
			return (ERROR);
	}
	*token_list = token;
	return (SUCCESS);
}

static bool	is_and_or_token(t_token *token)
{
	return (token->type == TOKEN_AND || token->type == TOKEN_OR);
}

static bool	is_invalid_token(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_PIPE
		|| type == TOKEN_NEW_LINE);
}
