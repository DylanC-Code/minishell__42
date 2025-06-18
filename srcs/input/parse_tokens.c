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

int	handle_pipe(t_parser *parser)
{
	if (parser->token->type != PIPE)
		return (0);
	if (!parser->token->next)
		return (1);
	parser->cmd_head->args[parser->arg_count] = NULL;
	parser->cmd_head->next = cmd_builder(parser->token->next);
	parser->cmd_head = parser->cmd_head->next;
	parser->arg_count = 0;
	return (0);
}

int	handle_logical_operator(t_parser *parser)
{
	if (parser->token->type != AND && parser->token->type != OR)
		return (0);
	parser->cmd_head->args[parser->arg_count] = NULL;
	if (parser->token->type == AND)
		parser->curr_seq->logical_op = LOGICAL_AND;
	else if (parser->token->type == OR)
		parser->curr_seq->logical_op = LOGICAL_OR;
	parser->curr_seq->next = sequence_builder();
	parser->curr_seq = parser->curr_seq->next;
	parser->cmd_head = cmd_builder(parser->token->next);
	parser->curr_seq->cmds = parser->cmd_head;
	return (1);
}

int	handle_redirection(t_parser *parser)
{
	t_token_type	redir_type;

	redir_type = parser->token->type;
	if (!is_redirection_operator(redir_type))
		return (0);
	if (!parser->token->next || parser->token->next->type != WORD)
		return (-1);
	redir_node_addback(&parser->redir_head, parser->token->next->value, parser->token->type);
	if (redir_type == REDIR_IN)
		parser->cmd_head->input_file = ft_strdup(parser->token->next->value);
	else if (redir_type == REDIR_OUT)
	{
		parser->cmd_head->output_file = ft_strdup(parser->token->next->value);
		parser->cmd_head->append_output = 0;
	}
	else if (redir_type == REDIR_APPEND)
	{
		parser->cmd_head->output_file = ft_strdup(parser->token->next->value);
		parser->cmd_head->append_output = 1;
	}
	else if (redir_type == REDIR_HEREDOC)
		parser->cmd_head->heredoc_delim = ft_strdup(parser->token->next->value);
	parser->token = parser->token->next;
	return (1);
}

t_cmd_sequence	*parse_tokens(t_token *head)
{
	t_parser	parser;

	parser.seq_head = sequence_builder();
	parser.cmd_head = cmd_builder(head);
	parser.curr_seq = parser.seq_head;
	parser.curr_seq->cmds = parser.cmd_head;
	parser.token = head;
	parser.arg_count = 0;
	parser.redir_head = NULL;
	while (parser.token)
	{
		if (parser.token->type == WORD)
			parser.cmd_head->args[parser.arg_count++] = ft_strdup(parser.token->value);
		else if (handle_pipe(&parser))
			return (NULL);
		else if (handle_redirection(&parser) == -1)
			return (NULL);
		else if (handle_logical_operator(&parser))
			parser.arg_count = 0;
		parser.token = parser.token->next;
	}
	display_redir_list(parser.redir_head);
	return (parser.cmd_head->args[parser.arg_count] = NULL, parser.seq_head);
}