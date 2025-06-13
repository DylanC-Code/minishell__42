/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saal-kur <saal-kur@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-13 14:11:20 by saal-kur          #+#    #+#             */
/*   Updated: 2025-06-13 14:11:20 by saal-kur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmd_sequence *parse_tokens(t_token *head)
{
	t_cmd_sequence *seq_head;
	t_cmd_sequence *curr_seq;
	t_cmd *cmd_head;
	size_t arg_count; 
	t_token *token;

	seq_head = sequence_builder();
	cmd_head = cmd_builder(head);
	curr_seq = seq_head;
	curr_seq->cmds = cmd_head;
	token = head;

	arg_count = 0;

	while (token)
	{
		if (token->type == WORD)
		{
			cmd_head->args[arg_count] = ft_strdup(token->value);
			arg_count++;
		}
		else if (token->type == PIPE)
		{
			cmd_head->args[arg_count] = NULL;
			cmd_head->next = cmd_builder(token->next);
			cmd_head = cmd_head->next;
			arg_count = 0;
		}
		else if (token->type == REDIR_IN)
		{
			token = token->next;
			if (token && token->type == WORD)
				cmd_head->input_file = ft_strdup(token->value);
		}
		else if (token->type == REDIR_OUT)
		{
			token = token->next;
			if (token && token->type == WORD)
			{
				cmd_head->output_file = ft_strdup(token->value);
				cmd_head->append_output = 0;
			}
		}
		else if (token->type == REDIR_APPEND)
		{
			token = token->next;
			if (token && token->type == WORD)
			{
				cmd_head->output_file = ft_strdup(token->value);
				cmd_head->append_output = 1;
			}
		}
		else if (token->type == REDIR_HEREDOC)
		{
			token = token->next;
			if (token && token->type == WORD)
				cmd_head->heredoc_delim = ft_strdup(token->value);
		}
		else if (token->type == AND || token->type == OR)
		{
			cmd_head->args[arg_count] = NULL;
			if(token->type == AND)
				curr_seq->logical_op = LOGICAL_AND;
			else
				curr_seq->logical_op = LOGICAL_OR;
			curr_seq->next = sequence_builder();
			curr_seq = curr_seq->next;
			cmd_head = cmd_builder(token->next);
			curr_seq->cmds = cmd_head;
			arg_count = 0;
		}
		token = token->next;
	}
	cmd_head->args[arg_count] = NULL;
	
	return seq_head;
}
