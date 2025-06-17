/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:27:08 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/17 14:22:00 by dcastor          ###   ########.fr       */
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

t_token	*append_eof_token(t_token **token_list, t_garbage **gc_list)
{
	t_token	*eof_token;

	eof_token = gc_malloc(sizeof(t_token), gc_list);
	if (!eof_token)
		return (NULL);
	ft_bzero(eof_token, sizeof(t_token));
	handle_eof_token(eof_token);
	add_token_back(token_list, eof_token);
	return (*token_list);
}
