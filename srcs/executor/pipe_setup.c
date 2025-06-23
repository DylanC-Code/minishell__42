/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:10:34 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 21:42:37 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void	assign_pipe_fds(t_cmd *cmd, int **pipes, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (cmd->fd_in == -1 && i > 0)
			cmd->fd_in = pipes[i - 1][0];
		if (cmd->fd_out == -1 && i < count - 1)
			cmd->fd_out = pipes[i][1];
		cmd->pipes = pipes;
		cmd = cmd->next;
	}
}

t_status	setup_pipes(t_cmd_sequence *seq, t_garbage **gc)
{
	t_cmd	*cmd;
	int		cmd_count;
	int		**pipes;
	int		i;

	cmd = seq->cmds;
	cmd_count = count_cmds(cmd);
	if (cmd_count < 2)
		return (NOOP);
	pipes = gc_malloc(sizeof(int *) * (cmd_count - 1), gc);
	if (!pipes)
		return (ERROR);
	i = -1;
	while (++i < cmd_count - 1)
	{
		pipes[i] = gc_malloc(sizeof(int) * 2, gc);
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			// Gérer les erreurs : à implémenter proprement
			// Exemple : close all pipes déjà ouverts, free
			return (ERROR);
		}
	}
	assign_pipe_fds(cmd, pipes, cmd_count);
	return (SUCCESS);
}
