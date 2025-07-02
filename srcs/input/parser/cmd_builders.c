/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:08:01 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:08:21 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*cmd_builder(t_token *token, t_garbage **gc);
t_cmd_sequence	*sequence_builder(t_garbage **gc);

t_cmd	*cmd_builder(t_token *token, t_garbage **gc)
{
	t_cmd	*cmd;

	cmd = gc_malloc(sizeof(t_cmd), gc);
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->args = gc_malloc(sizeof(char *) * (count_words(token) + 1), gc);
	if (!cmd->args)
		return (NULL);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

t_cmd_sequence	*sequence_builder(t_garbage **gc)
{
	t_cmd_sequence	*seq;

	seq = gc_malloc(sizeof(t_cmd_sequence), gc);
	if (!seq)
		return (NULL);
	ft_bzero(seq, sizeof(t_cmd_sequence));
	seq->cmds = NULL;
	seq->logical_op = -1;
	seq->next = NULL;
	return (seq);
}
