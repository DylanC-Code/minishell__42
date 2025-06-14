/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:27:08 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 10:28:44 by dcastor          ###   ########.fr       */
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
