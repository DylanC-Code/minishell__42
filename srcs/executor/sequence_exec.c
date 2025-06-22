/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:10 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/21 18:44:33 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	exec_sequence(t_app *app, t_cmd_sequence *seq)
{
	t_cmd	*cmd;
	int		status;

	cmd = seq->cmds;
	while (cmd)
	{
		exec_simple_cmd(app, cmd);
		cmd = cmd->next;
	}
	cmd = seq->cmds;
	while (cmd)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	return (SUCCESS);
}
