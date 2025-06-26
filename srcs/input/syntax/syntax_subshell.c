
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:06:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 16:25:59 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_subshell(t_app *app, t_token **token_list)
{
	t_token		*token;
	t_status	and_or_command_handled;

	token = *token_list;
	if (token->type != TOKEN_OPEN_PARENTHESIS)
		return (NOOP);
	token = token->next;
	if (token->type == TOKEN_CLOSE_PARENTHESIS)
		return (unexpected_token_error(app, token->value), ERROR);
	and_or_command_handled = syntax_handle_and_or_command(app, &token);
	if (and_or_command_handled == ERROR)
		return (ERROR);
	*token_list = token->next;
	return (SUCCESS);
}
