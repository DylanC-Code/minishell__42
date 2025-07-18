/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:20 by saal-kur          #+#    #+#             */
/*   Updated: 2025/07/07 10:08:59 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(t_parser *parser, t_garbage **gc)
{
	if (parser->token->type != TOKEN_PIPE)
		return (0);
	if (!parser->token->next)
		return (1);
	parser->cmd_head->args[parser->arg_count] = NULL;
	parser->cmd_head->next = cmd_builder(parser->token->next, gc);
	parser->cmd_head->next->prev = parser->cmd_head;
	parser->cmd_head = parser->cmd_head->next;
	parser->arg_count = 0;
	return (0);
}

int	handle_logical_operator(t_parser *parser, t_garbage **gc)
{
	if (parser->token->type != TOKEN_AND && parser->token->type != TOKEN_OR)
		return (0);
	parser->cmd_head->args[parser->arg_count] = NULL;
	if (parser->token->type == TOKEN_AND)
		parser->curr_seq->logical_op = LOGICAL_AND;
	else if (parser->token->type == TOKEN_OR)
		parser->curr_seq->logical_op = LOGICAL_OR;
	parser->curr_seq->next = sequence_builder(gc);
	parser->curr_seq = parser->curr_seq->next;
	parser->cmd_head = cmd_builder(parser->token->next, gc);
	parser->curr_seq->cmds = parser->cmd_head;
	return (1);
}

int	handle_redirection(t_parser *parser, t_garbage **gc)
{
	t_token_type	redir_type;

	redir_type = parser->token->type;
	if (!is_redirection_operator(redir_type))
		return (0);
	if (!parser->token->next || parser->token->next->type != TOKEN_WORD)
		return (-1);
	redir_node_addback(&parser->redir_head, parser->token->next->value,
		parser->token->type, gc);
	redir_node_addback(&parser->cmd_head->redir_list,
		parser->token->next->value, parser->token->type, gc);
	parser->token = parser->token->next;
	return (1);
}

t_cmd_sequence	*parse_tokens(t_token *head, t_garbage **gc, t_app *app)
{
	t_parser	p;

	p.seq_head = sequence_builder(gc);
	p.cmd_head = cmd_builder(head, gc);
	p.curr_seq = p.seq_head;
	p.curr_seq->cmds = p.cmd_head;
	p.token = head;
	p.arg_count = 0;
	p.redir_head = NULL;
	while (p.token)
	{
		if (p.token->type == TOKEN_WORD)
		{
			p.cmd_head->args[p.arg_count] = ft_strdup(p.token->value, gc);
			if (!p.cmd_head->args[p.arg_count++])
				cleanup_and_exit(app, EXIT_FAILURE);
		}
		else if (handle_pipe(&p, gc) || handle_redirection(&p, gc) == -1)
			return (NULL);
		else if (handle_logical_operator(&p, gc))
			p.arg_count = 0;
		p.token = p.token->next;
	}
	return (p.cmd_head->args[p.arg_count] = NULL, p.seq_head);
}
