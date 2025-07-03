/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_resolver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:45:00 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:48:02 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc(t_cmd *cmd, t_redir_list *redir)
{
	safe_close(&cmd->fd_in);
	cmd->fd_in = redir->fd;
}

static void	resolve_cmd_redirs(t_app *app, t_cmd *cmd)
{
	t_redir_list	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		handle_redir_in(app, cmd, redir);
		handle_redir_out(app, cmd, redir);
		handle_redir_append(app, cmd, redir);
		if (redir->type == TOKEN_REDIR_HEREDOC)
			handle_heredoc(cmd, redir);
		redir = redir->next;
	}
}

void	resolve_all_redirection(t_app *app, t_cmd_sequence *seq)
{
	t_cmd	*cmd;

	while (seq)
	{
		cmd = seq->cmds;
		while (cmd)
		{
			if (!cmd->failed)
				resolve_cmd_redirs(app, cmd);
			cmd = cmd->next;
		}
		seq = seq->next;
	}
}
