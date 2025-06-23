/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:10 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 15:14:46 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_children(t_app *app, t_cmd_sequence *seq);
void	wait_children(t_app *app, t_cmd_sequence *seq, pid_t pid);

void	exec_sequence(t_app *app, t_cmd_sequence *seq)
{
	t_cmd	*cmd;

	cmd = seq->cmds;
	while (cmd)
	{
		exec_simple_cmd(app, cmd);
		cmd = cmd->next;
	}
	wait_all_children(app, seq);
}

void	wait_all_children(t_app *app, t_cmd_sequence *seq)
{
	t_cmd	*cmd;

	cmd = seq->cmds;
	while (cmd)
	{
		if (cmd->pid > 0)
			wait_children(app, seq, cmd->pid);
		cmd = cmd->next;
	}
}

void	wait_children(t_app *app, t_cmd_sequence *seq, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		seq->last_exit_status = WEXITSTATUS(status);
		set_env_value(app, "?", ft_itoa(seq->last_exit_status));
	}
	else if (WIFSIGNALED(status))
	{
		seq->last_exit_status = 128 + WTERMSIG(status);
		set_env_value(app, "?", ft_itoa(seq->last_exit_status));
	}
	else
		seq->last_exit_status = 1;
}
