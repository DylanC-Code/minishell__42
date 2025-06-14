/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:45:57 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 14:58:08 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_syntax(t_token *head_token)
{
	while (head_token && head_token->type != TOKEN_EOF)
	{
		if (!syntax_handle_redirection(&head_token))
			return (false);
		break ;
	}
	return (true);
}
