/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:12:19 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/21 18:40:47 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_delimiter(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_NEW_LINE || type == TOKEN_OPEN_PARENTHESIS
		|| type == TOKEN_CLOSE_PARENTHESIS);
}

int	is_redirection_operator(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC));
}

size_t	count_words(t_token *start_token)
{
	size_t	arg_count;
	t_token	*current;

	current = start_token;
	arg_count = 0;
	if (current && current->type == TOKEN_OPEN_PARENTHESIS)
		current = current->next;
	while (current)
	{
		if (is_command_delimiter(current->type))
			break ;
		if (current->type == TOKEN_WORD)
		{
			arg_count++;
			current = current->next;
		}
		else if (is_redirection_operator(current->type))
		{
			current = current->next;
			if (current && current->type == TOKEN_WORD)
				current = current->next;
		}
		else
			current = current->next;
	}
	return (arg_count);
}

t_cmd	*cmd_builder(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * count_words(token) + 1);
	if (!cmd->args)
		return (NULL);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_output = -1;
	cmd->heredoc_delim = NULL;
	cmd->redir_list = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd_sequence	*sequence_builder(void)
{
	t_cmd_sequence	*seq;

	seq = malloc(sizeof(t_cmd_sequence));
	if (!seq)
		return (NULL);
	ft_bzero(seq, sizeof(t_cmd_sequence));
	seq->cmds = NULL;
	seq->logical_op = -1;
	seq->next = NULL;
	return (seq);
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

void	redir_node_addback(t_redir_list **redir_list, char *name,
		t_token_type type)
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
