/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:58:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/02 14:05:24 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status			handle_heredocs_cmd(t_app *app, t_cmd *cmd);
static t_status			handle_heredoc(t_app *app, t_cmd *cmd,
							t_redir_list *heredoc_redir);

volatile sig_atomic_t	g_sigint = 0;

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
			if (!handle_heredoc(app, cmd, redir_head))
				return (ERROR);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

static t_status	read_in_stdin(t_app *app, int fd, char *word)
{
	char	*buf;
	char	*tmp;

	while (1)
	{
		buf = readline(PS3_PROMPT);
		if (!buf)
		{
			printf("warning: here-document delimited by end-of-file (wanted '%s')\n",
				word);
			return (ERROR);
		}
		if (!ft_strncmp(word, buf, INT_MAX))
			break ;
		tmp = process_argument(buf, app);
		free(buf);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
	}
	return (SUCCESS);
}

void	heredoc_child(t_app *app, t_redir_list *heredoc_redir, int fds[2])
{
	safe_close(&fds[0]);
	signal(SIGINT, SIG_DFL);
	if (!read_in_stdin(app, fds[1], heredoc_redir->name))
	{
		safe_close(&fds[1]);
		cleanup_and_exit(app, 1);
	}
	safe_close(&fds[1]);
	cleanup_and_exit(app, 0);
}

t_status	heredoc_parent(t_app *app, t_redir_list *redir_list, pid_t pid,
		int fds[2])
{
	int	status;

	(void)app;
	safe_close(&fds[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
	{
		safe_close(&fds[0]);
		return (ERROR);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		safe_close(&fds[0]);
		set_env_value(app, "?", "130");
		return (-1);
	}
	redir_list->fd = fds[0];
	return (SUCCESS);
}

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
	if (pid < 0)
		exit_with_error(app, "fork");
	if (pid == 0)
	{
		heredoc_child(app, heredoc_redir, fds);
		return (SUCCESS);
	}
	heredoc_res = heredoc_parent(app, heredoc_redir, pid, fds);
	if (heredoc_res == ERROR)
		cmd->failed = true;
	else if (heredoc_res == SUCCESS)
		cmd->failed = false;
	else
		return (ERROR);
	return (SUCCESS);
}
