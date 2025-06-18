/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saal-kur <saal-kur@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-13 17:12:19 by saal-kur          #+#    #+#             */
/*   Updated: 2025-06-13 17:12:19 by saal-kur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_command_delimiter(t_token_type type)
{
	return (type == PIPE || type == AND || type == OR || 
			type == NEW_LINE || type == OPEN_PARENTHESE || type == CLOSE_PARENTHESE);
}

int is_redirection_operator(t_token_type type)
{	
	return (type == REDIR_IN || type == REDIR_OUT || 
			(type == REDIR_APPEND || type == REDIR_HEREDOC));
}

size_t count_words(t_token *start_token)
{
	size_t	arg_count;
	t_token	*current;

	current = start_token;
	arg_count = 0;
	if (current && current->type == OPEN_PARENTHESE)
		current = current->next;
	while (current)
	{
		if (is_command_delimiter(current->type))
			break;
		if (current->type == WORD)
		{
			arg_count++;
			current = current->next;
		}
		else if (is_redirection_operator(current->type))
		{
			current = current->next;
			if (current && current->type == WORD)
				current = current->next;
		}
		else
			current = current->next;
	}
	return (arg_count);
}

t_cmd *cmd_builder(t_token *token)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return NULL;
	printf("\nWORD COUNT IN CMD BUILDER %ld\n", count_words(token));
	cmd->args = malloc(sizeof(char *) * count_words(token) + 1);
	if(!cmd->args)
		return NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_output = -1;
	cmd->heredoc_delim = NULL;
	cmd->next = NULL;
	return cmd;
}

t_cmd_sequence *sequence_builder(void)
{
	t_cmd_sequence *seq;
	
	seq = malloc(sizeof(t_cmd_sequence));
	if(!seq)
		return NULL;
	seq->cmds = NULL;
	seq->logical_op = -1;
	seq->next = NULL;

	return seq;
}


t_redir_list	*redir_node_builder(char *name, t_token_type type)
{
	t_redir_list	*node;

	node = malloc(sizeof(t_redir_list));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (!node->name)
		return (NULL);
	node->type = type;
	node->next = NULL;
	return (node);
}

void	redir_node_addback(t_redir_list **redir_list, char *name, t_token_type type)
{
	t_redir_list	*new_node;
	t_redir_list	*current;

	new_node = redir_node_builder(name, type);
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

	lst = head;
	int i = 0;
	while (lst)
	{
		printf("[Node %d] lst->name = %s lst->type %s\n", i, lst->name, token_to_str(lst->type));
		i++;
		lst = lst->next;
	}
}