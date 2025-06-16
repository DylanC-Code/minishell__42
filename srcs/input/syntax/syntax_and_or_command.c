/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_or_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:18:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 16:56:33 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_and_or_token(t_token *token);

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
	while (*token_list && is_and_or_token(*token_list))
	{
		op_token = *token_list;
		*token_list = (*token_list)->next;
		if (!*token_list || is_and_or_token(*token_list))
			return (print_syntax_error(op_token->value), ERROR);
		pipeline_handled = syntax_handle_pipeline(token_list);
		if (pipeline_handled != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

static bool	is_and_or_token(t_token *token)
{
	return (token->type == TOKEN_AND || token->type == TOKEN_OR);
}
