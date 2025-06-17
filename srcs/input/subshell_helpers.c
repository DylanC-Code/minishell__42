/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saal-kur <saal-kur@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-16 13:27:42 by saal-kur          #+#    #+#             */
/*   Updated: 2025-06-16 13:27:42 by saal-kur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *match_opening_paran(t_token *open_paren)
{
	size_t	depth;
	t_token	*current;
	
	current = open_paren->next;
	depth = 1;
	while (current && depth > 0)
	{
		if (current->type == OPEN_PARENTHESE)
			depth++;
		else if (current->type == CLOSE_PARENTHESE)
			depth--;
		if (depth > 0)
			current = current->next;
	}
	/* à supprimer si la gestion syntaxe est parfaite*/
	if (depth == 0)
		return current;
	else
		return NULL;
}
