/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:27:08 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 21:21:24 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =============== Importation =============== */

#include "minishell.h"

/* =============== Declaration =============== */

void	add_token_back(t_token **token_list, t_token *new_token);

/* =============== Definition ================ */

void	add_token_back(t_token **token_list, t_token *new_token)
{
	t_token	*next;

	if (!*token_list)
	{
		*token_list = new_token;
		return ;
	}
	next = *token_list;
	while (next->next)
		next = next->next;
	next->next = new_token;
}

t_token	*append_newline_token(t_token **token_list, t_garbage **gc)
{
	t_token	*newline_token;

	newline_token = gc_malloc(sizeof(t_token), gc);
	if (!newline_token)
		return (NULL);
	ft_bzero(newline_token, sizeof(t_token));
	handle_new_line_token(newline_token, gc);
	add_token_back(token_list, newline_token);
	return (*token_list);
}
