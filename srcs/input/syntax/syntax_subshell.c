
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

t_status	syntax_handle_subshell(t_token **token_list)
{
	t_token		*token;
	t_status	and_or_command_handled;
	bool		has_closing_parenthesis;

	token = *token_list;
	if (token->type != TOKEN_OPEN_PARENTHESIS)
		return (NOOP);
	token = token->next;
	and_or_command_handled = syntax_handle_and_or_command(&token);
	if (and_or_command_handled == ERROR)
		return (ERROR);
	has_closing_parenthesis = token->type == TOKEN_CLOSE_PARENTHESIS;
	if (has_closing_parenthesis)
		*token_list = token->next;
	return (has_closing_parenthesis);
}
