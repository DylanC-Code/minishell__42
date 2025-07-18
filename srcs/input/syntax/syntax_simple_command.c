/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:16:36 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 15:43:20 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_simple_command(t_app *app, t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (is_redirection_sequence(token))
		if (!syntax_handle_redirection(app, &token))
			return (ERROR);
	*token_list = token;
	if (token->type != TOKEN_WORD)
		return (SUCCESS);
	while (token->type == TOKEN_WORD)
	{
		if (!check_word(app, token->value))
			return (ERROR);
		else
			token = token->next;
	}
	while (is_redirection_sequence(token) || token->type == TOKEN_WORD)
	{
		if (!syntax_handle_redirection(app, &token))
			return (ERROR);
		else if (token->type == TOKEN_WORD)
			token = token->next;
	}
	*token_list = token;
	return (SUCCESS);
}
