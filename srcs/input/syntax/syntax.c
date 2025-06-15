/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:45:57 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 15:50:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_syntax(t_token *head_token)
{
	if (syntax_handle_and_or_command(&head_token) == ERROR)
		return (false);
	if (syntax_handle_pipeline(&head_token) == ERROR)
		return (false);
	if (syntax_handle_command(&head_token) == ERROR)
		return (false);
	if (syntax_handle_redirection(&head_token) == ERROR)
		return (false);
	return (head_token->type == TOKEN_EOF);
}
