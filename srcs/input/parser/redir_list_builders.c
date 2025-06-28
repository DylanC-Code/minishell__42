/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_builders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:08:43 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:09:03 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_list	*redir_node_builder(char *name, t_token_type type,
					t_garbage **gc);
void			redir_node_addback(t_redir_list **redir_list, char *name,
					t_token_type type, t_garbage **gc);
void			display_redir_list(t_redir_list *head);

t_redir_list	*redir_node_builder(char *name, t_token_type type,
		t_garbage **gc)
{
	t_redir_list	*node;

	node = gc_malloc(sizeof(t_redir_list), gc);
	if (!node)
		return (NULL);
	node->name = ft_strdup(name, gc);
	if (!node->name)
		return (NULL);
	node->type = type;
	node->next = NULL;
	return (node);
}

void	redir_node_addback(t_redir_list **redir_list, char *name,
		t_token_type type, t_garbage **gc)
{
	t_redir_list	*new_node;
	t_redir_list	*current;

	new_node = redir_node_builder(name, type, gc);
	if (!new_node)
		return ;
	if (!*redir_list)
	{
		*redir_list = new_node;
		return ;
	}
	current = *redir_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	display_redir_list(t_redir_list *head)
{
	t_redir_list	*lst;
	int				i;

	lst = head;
	i = 0;
	while (lst)
	{
		printf("[Node %d] lst->name = %s lst->type %s\n", i, lst->name,
			token_to_str(lst->type));
		i++;
		lst = lst->next;
	}
}
