/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:13:03 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 16:20:34 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_gb_to_back(t_garbage **garbage_list, t_garbage *new_gb);

void	*gc_malloc(size_t size, t_garbage **garbage_list)
{
	t_garbage	*new_gb;
	void		*alloc;

	new_gb = ft_calloc(1, sizeof(t_garbage));
	if (!new_gb)
		exit_with_error("gc_malloc", garbage_list);
	alloc = malloc(size);
	if (!alloc)
		(free(new_gb), exit_with_error("gc_malloc", garbage_list));
	new_gb->alloc = alloc;
	add_gb_to_back(garbage_list, new_gb);
	return (alloc);
}

void	gc_cleanup(t_garbage **garbage_list)
{
	t_garbage	*next;
	t_garbage	*curr;

	if (!garbage_list)
		return ;
	curr = *garbage_list;
	while (curr)
	{
		next = curr->next;
		free(curr->alloc);
		free(curr);
		curr = next;
	}
	*garbage_list = NULL;
}

void	add_to_gc(t_garbage **garbage_list, void *alloc)
{
	t_garbage	*new_gb;

	if (!alloc)
		return ;
	new_gb = ft_calloc(1, sizeof(t_garbage));
	if (!new_gb)
		(free(alloc), exit_with_error("gc_malloc", garbage_list));
	new_gb->alloc = alloc;
	add_gb_to_back(garbage_list, new_gb);
}

static void	add_gb_to_back(t_garbage **garbage_list, t_garbage *new_gb)
{
	t_garbage	*next;

	if (!garbage_list)
		return ;
	next = *garbage_list;
	if (!next)
	{
		*garbage_list = new_gb;
		return ;
	}
	while (next->next)
		next = next->next;
	next->next = new_gb;
}
