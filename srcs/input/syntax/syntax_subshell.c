
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
	t_token	*token;

	token = *token_list;
	if (token->type != TOKEN_OPEN_PARENTHESE)
		return (NOOP);
    
}
