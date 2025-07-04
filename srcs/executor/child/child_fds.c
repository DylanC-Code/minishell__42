/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:01:52 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:02:20 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_other_fds(t_cmd_sequence *seq_head)
{
	t_cmd	*cmd;

	while (seq_head)
	{
		cmd = seq_head->cmds;
		while (cmd)
		{
			safe_close(&cmd->fd_in);
			safe_close(&cmd->fd_out);
			cmd = cmd->next;
		}
		seq_head = seq_head->next;
	}
}

void	close_fds_and_pipes(t_cmd_sequence *seq_head, t_cmd *current_cmd)
{
	close_pipes(current_cmd);
	close_other_fds(seq_head);
}
