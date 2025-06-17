/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:20 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/17 15:17:28 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_sequence	*parse_tokens(t_token *head)
{
	t_cmd_sequence	*seq_head;
	t_cmd_sequence	*curr_seq;
	t_cmd			*cmd_head;
	size_t			arg_count;
	t_token			*token;

	seq_head = sequence_builder();
	cmd_head = cmd_builder(head);
	curr_seq = seq_head;
	curr_seq->cmds = cmd_head;
	token = head;
	arg_count = 0;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			cmd_head->args[arg_count++] = ft_strdup(token->value);
		else if (handle_pipe(&cmd_head, &token, &arg_count))
			return (NULL);
		else if (handle_redirection(&cmd_head, &token) == -1)
			return (NULL);
		else if (handle_logical_op(&curr_seq, &cmd_head, token, arg_count))
			arg_count = 0;
		token = token->next;
	}
	return (cmd_head->args[arg_count] = NULL, seq_head);
}

int	handle_pipe(t_cmd **cmd_head, t_token **token, size_t *arg_count)
{
	if ((*token)->type != TOKEN_PIPE)
		return (0);
	if (!(*token)->next) // à changer pour aller lire la stdin
		return (1);
	(*cmd_head)->args[*arg_count] = NULL;
	(*cmd_head)->next = cmd_builder((*token)->next);
	*cmd_head = (*cmd_head)->next;
	*arg_count = 0;
	return (0);
}

int	handle_logical_op(t_cmd_sequence **curr_seq, t_cmd **cmd_head,
		t_token *token, size_t arg_count)
{
	if (token->type != TOKEN_AND && token->type != TOKEN_OR)
		return (0);
	(*cmd_head)->args[arg_count] = NULL;
	if (token->type == TOKEN_AND)
		(*curr_seq)->logical_op = LOGICAL_AND;
	else if (token->type == TOKEN_OR)
		(*curr_seq)->logical_op = LOGICAL_OR;
	(*curr_seq)->next = sequence_builder();
	*curr_seq = (*curr_seq)->next;
	*cmd_head = cmd_builder(token->next);
	(*curr_seq)->cmds = *cmd_head;
	return (1);
}

int	handle_redirection(t_cmd **cmd, t_token **token)
{
	t_token_type	redir_type;

	redir_type = (*token)->type;
	if (redir_type != TOKEN_REDIR_IN && redir_type != TOKEN_REDIR_OUT
		&& redir_type != TOKEN_REDIR_APPEND && redir_type != TOKEN_REDIR_HEREDOC)
		return (0);
	if (!(*token)->next || (*token)->next->type != TOKEN_WORD) // à changer pour aller lire la stdin
		return (-1);
	if (redir_type == TOKEN_REDIR_IN)
		(*cmd)->input_file = ft_strdup((*token)->next->value);
	else if (redir_type == TOKEN_REDIR_OUT)
	{
		(*cmd)->output_file = ft_strdup((*token)->next->value);
		(*cmd)->append_output = 0;
	}
	else if (redir_type == TOKEN_REDIR_APPEND)
	{
		(*cmd)->output_file = ft_strdup((*token)->next->value);
		(*cmd)->append_output = 1;
	}
	else if (redir_type == TOKEN_REDIR_HEREDOC) // à changer pour aller lire la stdin
		(*cmd)->heredoc_delim = ft_strdup((*token)->next->value);
	*token = (*token)->next;
	return (1);
}
