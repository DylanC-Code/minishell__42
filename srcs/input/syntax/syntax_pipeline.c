/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:06:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 15:07:45 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_pipeline(t_token **token_list)
{
	t_status	command_handled;

	command_handled = syntax_handle_command(token_list);
	if (!command_handled)
		return (ERROR);
	if (command_handled == NOOP)
		return (NOOP);
	while ((*token_list)->type == TOKEN_PIPE)
	{
		*token_list = (*token_list)->next;
		command_handled = syntax_handle_command(token_list);
		if (command_handled != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
