/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:58:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/29 11:10:00 by dcastor          ###   ########.fr       */
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
	t_status ret_code;

	signal(SIGINT, sigs_handler);
	while (head_seq)
	{
		cmd = head_seq->cmds;
		while (cmd)
		{
			ret_code = handle_heredocs_cmd(app, cmd);
			if (!ret_code)
			{
				signal(SIGINT, SIG_DFL);
				return (ret_code);
			}
			cmd = cmd->next;
		}
		head_seq = head_seq->next;
	}
	signal(SIGINT, sigs_handler);
	return (SUCCESS);
}

static t_status	handle_heredocs_cmd(t_app *app, t_cmd *cmd)
{
	t_redir_list	*redir_head;
	t_status		ret_code;

	redir_head = cmd->redir_list;
	while (redir_head)
	{
		ret_code = handle_heredoc(app, redir_head);
		if (redir_head->type != TOKEN_REDIR_HEREDOC)
			;
		else if (!ret_code)
			return (ret_code);
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

	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		printf("Parent process: PID %d, child exited with status %d\n", pid, WTERMSIG(status));
		printf("Heredoc child recieved SIGINT\n");
		//ft_putstr_fd("^C\n", 1);
		close(fds[0]);
		set_env_value(app, "?", "130");
		return (WEXITSTATUS(status));
	}

	close(fds[1]);
	heredoc_redir->fd = fds[0];
	set_env_value(app, "?", "0");
	return (SUCCESS);
}

void check_eof(t_app *app, char *line, t_redir_list *heredoc)
{
	char *msg;

	if (line == NULL)
	{
		msg = ft_strjoin("minishell: warning: here-document delimited by end-of-file (wanted `", heredoc->name, &app->curr_gc);
		msg = ft_strjoin(msg, "')\n", &app->curr_gc);
		ft_putstr_fd(msg, 1);
	}
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
	check_eof(app, line, heredoc_redir);
	close(fds[1]);
	exit(0);
	// close(fds[1]);
	// exit(22);
}
