/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_or_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:18:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 15:26:24 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_and_or_token(t_token *token);

t_status	syntax_handle_and_or_command(t_token **token_list)
{
	t_status	pipeline_handled;

	pipeline_handled = syntax_handle_pipeline(token_list);
	if (pipeline_handled == ERROR)
		return (ERROR);
	if (pipeline_handled == NOOP)
		return (NOOP);
	while (is_and_or_token(*token_list))
	{
		*token_list = (*token_list)->next;
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
