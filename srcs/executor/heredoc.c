/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:58:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 16:16:49 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir);
static void		handle_heredocs_cmd(t_app *app, t_cmd *cmd);

t_status	collect_heredocs(t_app *app, t_cmd_sequence *head_seq)
{
	t_cmd	*cmd;

	while (head_seq)
	{
		cmd = head_seq->cmds;
		while (cmd)
		{
			handle_heredocs_cmd(app, cmd);
			cmd = cmd->next;
		}
		head_seq = head_seq->next;
	}
	return (SUCCESS);
}

static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir)
{
	char	*buffer;
	char	*tmp;
	int		fds[2];

	buffer = NULL;
	in_heredoc = true;
	tmp = gc_readline(app, PS3_PROMPT);
	if (!tmp)
		cleanup_and_exit(app, EXIT_SUCCESS);
	if (pipe(fds) == -1)
		return (perror("pipe"), ERROR);
	while (ft_strcmp(tmp, heredoc_redir->name))
	{
		if (!buffer)
			buffer = tmp;
		else
			buffer = ft_strjoin(buffer, tmp, &app->curr_gc);
		buffer = ft_strjoin(buffer, "\n", &app->curr_gc);
		tmp = gc_readline(app, PS3_PROMPT);
		if (!tmp)
		{
			close(fds[0]);
			close(fds[1]);
			cleanup_and_exit(app, EXIT_SUCCESS);
		}
	}
	write(fds[1], buffer, ft_strlen(buffer));
	close(fds[1]);
	in_heredoc = false;
	heredoc_redir->fd = fds[0];
	return (SUCCESS);
}

static void	handle_heredocs_cmd(t_app *app, t_cmd *cmd)
{
	t_redir_list	*redir_head;

	redir_head = cmd->redir_list;
	while (redir_head)
	{
		if (redir_head->type == TOKEN_REDIR_HEREDOC)
			handle_heredoc(app, redir_head);
		redir_head = redir_head->next;
	}
}
