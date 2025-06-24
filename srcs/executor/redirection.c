/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:27:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 14:48:54 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir_in(t_app *app, t_cmd *cmd, t_redir_list *redir);
static void	handle_redir_out(t_app *app, t_cmd *cmd, t_redir_list *redir);
static void	handle_redir_append(t_app *app, t_cmd *cmd, t_redir_list *redir);

void	resolve_all_redirection(t_app *app, t_cmd_sequence *seq)
{
	t_redir_list	*redir;
	t_cmd			*cmd;

	while (seq)
	{
		cmd = seq->cmds;
		while (cmd)
		{
			redir = cmd->redir_list;
			while (redir)
			{
				handle_redir_in(app, cmd, redir);
				handle_redir_out(app, cmd, redir);
				handle_redir_append(app, cmd, redir);
				if (redir->type == TOKEN_REDIR_HEREDOC)
				{
					safe_close(&cmd->fd_in);
					cmd->fd_in = redir->fd;
				}
				redir = redir->next;
			}
			cmd = cmd->next;
		}
		seq = seq->next;
	}
}

static void	handle_redir_in(t_app *app, t_cmd *cmd, t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_IN)
		return ;
	redir->fd = open(redir->name, O_RDONLY);
	if (redir->fd < 0)
	{
		cmd->failed = true;
		set_env_value(app, "?", ft_itoa(errno, &app->curr_gc));
		return (perror(redir->name));
	}
	safe_close(&cmd->fd_in);
	cmd->fd_in = redir->fd;
}

static void	handle_redir_out(t_app *app, t_cmd *cmd, t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_OUT)
		return ;
	redir->fd = open(redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->fd < 0)
	{
		cmd->failed = true;
		set_env_value(app, "?", ft_itoa(errno, &app->curr_gc));
		return (perror(redir->name));
	}
	safe_close(&cmd->fd_in);
	cmd->fd_out = redir->fd;
}

static void	handle_redir_append(t_app *app, t_cmd *cmd, t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_APPEND)
		return ;
	redir->fd = open(redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		cmd->failed = true;
		set_env_value(app, "?", ft_itoa(errno, &app->curr_gc));
		return (perror(redir->name));
	}
	safe_close(&cmd->fd_out);
	cmd->fd_out = redir->fd;
}
