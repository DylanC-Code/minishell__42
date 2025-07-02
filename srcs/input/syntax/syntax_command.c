/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:41:41 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 15:43:52 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	syntax_handle_command(t_app *app, t_token **token_list)
{
	t_status	simple_command_handled;

	simple_command_handled = syntax_handle_simple_command(app, token_list);
	if (simple_command_handled == ERROR)
		return (ERROR);
	if (simple_command_handled == SUCCESS)
		return (SUCCESS);
	return (syntax_handle_subshell(app, token_list));
}
