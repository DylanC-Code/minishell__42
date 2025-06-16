/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:06:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 17:03:22 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_pipeline(t_token **token_list)
{
	t_status	command_handled;

	if ((*token_list)->type == TOKEN_PIPE)
		return (print_syntax_error("|"), ERROR);
	command_handled = syntax_handle_command(token_list);
	if (command_handled != SUCCESS)
		return (command_handled);
	while (*token_list && (*token_list)->type == TOKEN_PIPE)
	{
		*token_list = (*token_list)->next;
		if (!*token_list || (*token_list)->type == TOKEN_PIPE)
			return (print_syntax_error("|"), ERROR);
		command_handled = syntax_handle_command(token_list);
		if (command_handled != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
