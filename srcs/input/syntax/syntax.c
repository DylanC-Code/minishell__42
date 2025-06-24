/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:45:57 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 15:22:34 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_syntax(t_app *app, t_token *head_token)
{
	if (!head_token)
		return (false);
	if (syntax_handle_and_or_command(&head_token) == ERROR)
		return (set_env_value(app, "?", "2"), false);
	if (syntax_handle_pipeline(&head_token) == ERROR)
		return (set_env_value(app, "?", "2"), false);
	if (syntax_handle_command(&head_token) == ERROR)
		return (set_env_value(app, "?", "2"), false);
	if (syntax_handle_redirection(&head_token) == ERROR)
		return (set_env_value(app, "?", "2"), false);
	if (head_token->type == TOKEN_NEW_LINE)
		return (true);
	return (set_env_value(app, "?", "2"), false);
}
