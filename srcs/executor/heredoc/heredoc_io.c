/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:15:25 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:26:45 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	read_in_stdin(t_app *app, int fd, char *word)
{
	char	*buf;
	char	*tmp;

	while (1)
	{
		buf = readline(PS3_PROMPT);
		if (!buf)
		{
			printf("warning: \
here-document delimited by end-of-file (wanted '%s')\n",
				word);
			return (ERROR);
		}
		if (!ft_strncmp(word, buf, INT_MAX))
		{
			free(buf);
			break ;
		}
		tmp = process_argument(buf, app);
		free(buf);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
	}
	return (SUCCESS);
}

void	heredoc_child(t_app *app, t_redir_list *heredoc_redir, int fds[2])
{
	close_previous_heredoc_fd(app->seq_head);
	safe_close(&fds[0]);
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

	(void)redir_list;
	safe_close(&fds[1]);
	g_in_heredoc = true;
	waitpid(pid, &status, 0);
	g_in_heredoc = false;
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
	return (SUCCESS);
}
