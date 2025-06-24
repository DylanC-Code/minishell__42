/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:58:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 10:57:40 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	handle_heredoc(t_redir_list *heredoc_redir, t_garbage **gc);
static void		handle_heredocs_cmd(t_cmd *cmd, t_garbage **gc);

t_status	collect_heredocs(t_cmd_sequence *head_seq, t_garbage **gc)
{
	t_cmd	*cmd;

	while (head_seq)
	{
		cmd = head_seq->cmds;
		while (cmd)
		{
			handle_heredocs_cmd(cmd, gc);
			cmd = cmd->next;
		}
		head_seq = head_seq->next;
	}
	return (SUCCESS);
}

static t_status	handle_heredoc(t_redir_list *heredoc_redir, t_garbage **gc)
{
	char	*buffer;
	char	*tmp;
	int		fds[2];

	buffer = NULL;
	tmp = gc_readline(gc, PS2_PROMPT);
	if (!tmp)
		return (ERROR);
	if (pipe(fds) == -1)
		return (perror("pipe"), ERROR);
	while (ft_strcmp(tmp, heredoc_redir->name))
	{
		if (!tmp)
			return (ERROR);
		if (!buffer)
			buffer = tmp;
		else
			buffer = ft_strjoin(buffer, tmp, gc);
		buffer = ft_strjoin(buffer, "\n", gc);
		tmp = gc_readline(gc, PS2_PROMPT);
	}
	write(fds[1], buffer, ft_strlen(buffer));
	close(fds[1]);
	heredoc_redir->fd = fds[0];
	return (SUCCESS);
}

static void	handle_heredocs_cmd(t_cmd *cmd, t_garbage **gc)
{
	t_redir_list	*redir_head;

	redir_head = cmd->redir_list;
	while (redir_head)
	{
		if (redir_head->type == TOKEN_REDIR_HEREDOC)
			handle_heredoc(redir_head, gc);
		redir_head = redir_head->next;
	}
}
