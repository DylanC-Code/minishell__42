/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:16:36 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 14:56:07 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_command(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (is_redirection_sequence(token))
		if (!syntax_handle_redirection(&token))
			return (ERROR);
	if (token->type != TOKEN_WORD)
		return (NOOP);
	token = token->next;
	while (token->type == TOKEN_WORD)
		token = token->next;
	while (is_redirection_sequence(token))
		if (!syntax_handle_redirection(&token))
			return (ERROR);
	*token_list = token;
	return (SUCCESS);
}
