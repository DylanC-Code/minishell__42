/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:58:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/01 15:38:11 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir);
static t_status	handle_heredocs_cmd(t_app *app, t_cmd *cmd);
static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir);

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

static t_status	handle_heredocs_cmd(t_app *app, t_cmd *cmd)
{
	t_redir_list	*redir_head;

	redir_head = cmd->redir_list;
	while (redir_head)
	{
		if (redir_head->type == TOKEN_REDIR_HEREDOC)
		{
			if (!handle_heredoc(app, redir_head))
				cmd->failed = true;
			else
				cmd->failed = false;
		}
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

static t_status	read_in_stdin(t_app *app, int fd, char *word)
{
	char	*buf;
	char	*tmp;

	(void)app;
	while (1)
	{
		buf = NULL;
		buf = readline(PS3_PROMPT);
		if (!buf)
		{
			printf("warning: here-document delimited by end-of-file (wanted '%s')\n",
				word);
			close(fd);
			return (ERROR);
		}
		if (!ft_strncmp(word, buf, INT_MAX))
			break ;
		tmp = process_argument(buf, app);
		free(buf);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
	}
	close(fd);
	return (SUCCESS);
}

static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir)
{
	int	fd;

	if (heredoc_redir->type != TOKEN_REDIR_HEREDOC)
		return (NOOP);
	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit_with_error(app, "open");
	if (!read_in_stdin(app, fd, heredoc_redir->name))
	{
		unlink(".heredoc.tmp");
		return (ERROR);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	heredoc_redir->fd = fd;
	return (SUCCESS);
}
