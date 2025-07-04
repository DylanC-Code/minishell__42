/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:13:28 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:38:11 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	handle_heredoc(t_app *app, t_cmd *cmd,
		t_redir_list *heredoc_redir)
{
	pid_t		pid;
	int			fds[2];
	t_status	heredoc_res;

	if (heredoc_redir->type != TOKEN_REDIR_HEREDOC)
		return (NOOP);
	if (pipe(fds) == -1)
		exit_with_error(app, "pipe");
	pid = fork();
	heredoc_redir->fd = fds[0];
	if (pid < 0)
		(safe_close(&fds[1]), safe_close(&heredoc_redir->fd),
			exit_with_error(app, "fork"));
	if (pid == 0)
		return (heredoc_child(app, heredoc_redir, fds), (SUCCESS));
	heredoc_res = heredoc_parent(app, heredoc_redir, pid, fds);
	cmd->failed = heredoc_res == ERROR;
	if (cmd->failed)
		safe_close(&heredoc_redir->fd);
	return (SUCCESS);
}

static t_status	handle_heredocs_cmd(t_app *app, t_cmd *cmd)
{
	t_redir_list	*redir_head;

	redir_head = cmd->redir_list;
	while (redir_head)
	{
		if (redir_head->type == TOKEN_REDIR_HEREDOC)
			if (!handle_heredoc(app, cmd, redir_head))
				return (ERROR);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

t_status	collect_heredocs(t_app *app, t_cmd_sequence *head_seq)
{
	t_cmd	*cmd;

	while (head_seq)
	{
		cmd = head_seq->cmds;
		while (cmd)
		{
			if (!handle_heredocs_cmd(app, cmd))
				return (ERROR);
			cmd = cmd->next;
		}
		head_seq = head_seq->next;
	}
	return (SUCCESS);
}

void	close_previous_heredoc_fd(t_cmd_sequence *seq_head)
{
	t_cmd			*cmd;
	t_redir_list	*redir;

	while (seq_head)
	{
		cmd = seq_head->cmds;
		while (cmd)
		{
			redir = cmd->redir_list;
			while (redir)
			{
				if (redir->type == TOKEN_REDIR_HEREDOC)
					safe_close(&redir->fd);
				redir = redir->next;
			}
			cmd = cmd->next;
		}
		seq_head = seq_head->next;
	}
}
