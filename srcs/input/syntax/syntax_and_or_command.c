/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_or_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:18:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 11:10:24 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_and_or_token(t_token *token);
static bool	is_invalid_token(t_token *token);

t_status	syntax_handle_and_or_command(t_token **token_list)
{
	t_status	pipeline_handled;
	t_token		*op_token;

	op_token = *token_list;
	if (is_and_or_token(*token_list))
		return (print_syntax_error((*token_list)->value), ERROR);
	pipeline_handled = syntax_handle_pipeline(token_list);
	if (pipeline_handled != SUCCESS)
		return (pipeline_handled);
	while (is_and_or_token(*token_list))
	{
		op_token = *token_list;
		*token_list = (*token_list)->next;
		if (is_invalid_token(*token_list))
			return (print_syntax_error((*token_list)->value), ERROR);
		pipeline_handled = syntax_handle_pipeline(token_list);
		if (pipeline_handled == ERROR)
			return (ERROR);
	}
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
