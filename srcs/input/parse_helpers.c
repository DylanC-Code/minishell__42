/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:12:19 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/17 15:14:49 by dcastor          ###   ########.fr       */
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
	if(current->type == OPEN_PARENTHESE)
		current = current->next;
	while (current)
	{
		if (is_command_delimiter(current->type))
			break ;
		if (current->type == TOKEN_WORD)
			arg_count++;
		else if (is_redirection_operator(current->type))
		{
			current = current->next;
			if (current && current->type == TOKEN_WORD)
			{
				current = current->next;
				continue ;
			}
		}
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
	printf("\nWORD COUNT IN CMD BUILDER %ld\n", count_words(token));
	cmd->args = malloc(sizeof(char *) * count_words(token) + 1);
	if (!cmd->args)
		return (NULL);
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_output = -1;
	cmd->heredoc_delim = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd_sequence	*sequence_builder(void)
{
	t_cmd_sequence	*seq;

	seq = malloc(sizeof(t_cmd_sequence));
	if (!seq)
		return (NULL);
	seq->cmds = NULL;
	seq->logical_op = -1;
	seq->next = NULL;
	return (seq);
}
