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

t_cmd *cmd_builder(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return NULL;
	cmd->args = 0;
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
