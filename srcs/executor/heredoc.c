/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:58:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/27 15:14:48 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir);
static t_status	handle_heredocs_cmd(t_app *app, t_cmd *cmd);
static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir);
static t_status	parent_heredoc(t_app *app, t_redir_list *heredoc_redir,
					int fds[2], pid_t pid);
static void		child_heredoc(t_app *app, t_redir_list *heredoc_redir,
					int fds[2], pid_t pid);

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
		if (redir_head->type != TOKEN_REDIR_HEREDOC)
			;
		else if (!handle_heredoc(app, redir_head))
			return (ERROR);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

static t_status	handle_heredoc(t_app *app, t_redir_list *heredoc_redir)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit_with_error(app, "pipe");
	pid = fork();
	if (pid == -1)
		exit_with_error(app, "fork");
	if (pid > 0)
		return (parent_heredoc(app, heredoc_redir, fds, pid));
	child_heredoc(app, heredoc_redir, fds, pid);
	return (SUCCESS);
}

static t_status	parent_heredoc(t_app *app, t_redir_list *heredoc_redir,
		int fds[2], pid_t pid)
{
	int	status;

	(void)app;
	(void)pid;
	(void)heredoc_redir;
	(void)fds;
	waitpid(pid, &status, 0);
	printf("Parent process: PID %d, child exited with status %d\n", pid,
		WEXITSTATUS(status));
	close(fds[1]); 
	heredoc_redir->fd = fds[0];
	return (SUCCESS);
}

static void	child_heredoc(t_app *app, t_redir_list *heredoc_redir, int fds[2],
		pid_t pid)
{
	char	*line;
	//char	*prompt;

	(void)app;
	(void)pid;
	(void)heredoc_redir;
	(void)fds;
	signal(SIGINT, SIG_DFL);
	//prompt = get_prompt(app);
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, heredoc_redir->name) == 0)
			break;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		line = readline("> ");
	}
	close(fds[1]);
	exit(0);

	// close(fds[1]);
	// exit(22);
}
