/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:32 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 15:28:36 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exec(t_app *app, t_cmd *cmd)
{
	int	dups[2];

	dups[0] = 0;
	dups[1] = 0;
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 0)
		dups[0] = dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 0)
		dups[1] = dup2(cmd->fd_out, STDOUT_FILENO);
	if (dups[0] < 0 || dups[1] < 0)
	{
		close_fds_and_pipes(app->seq_head, cmd);
		exit_with_error(app, "dup2");
	}
	close_fds_and_pipes(app->seq_head, cmd);
	if (is_builtin(cmd->args[0]))
		return (exec_builtin(app, cmd));
	exec_or_died(app, cmd);
}

void	exec(t_app *app, t_cmd *cmd, char *path)
{
	execve(path, cmd->args, env_list_to_envp(app->env_head, &app->app_gc));
	exit_with_error(app, "execve");
}

void	handle_direct_path(t_app *app, t_cmd *cmd)
{
	struct stat	stat_buf;
	char		*msg;

	if (access(cmd->args[0], F_OK) != 0)
	{
		msg = ft_strjoin(cmd->args[0], ": No such file or directory\n",
				&app->curr_gc);
		o7bfu3sca3tion1(app, msg);
		(print_error(app, msg, "127"), cleanup_and_exit(app, 127));
	}
	if (stat(cmd->args[0], &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
	{
		msg = ft_strjoin(cmd->args[0], ": Is a directory\n", &app->curr_gc);
		o7bfu3sca3tion1(app, msg);
		(print_error(app, msg, "126"), cleanup_and_exit(app, 126));
	}
	if (access(cmd->args[0], X_OK) != 0)
	{
		msg = ft_strjoin(cmd->args[0], ": Permission denied\n", &app->curr_gc);
		o7bfu3sca3tion1(app, msg);
		(print_error(app, msg, "126"), cleanup_and_exit(app, 126));
	}
	exec(app, cmd, cmd->args[0]);
}

void	handle_path_search(t_app *app, t_cmd *cmd)
{
	char	*path;
	char	*msg;

	path = find_in_path(app, cmd->args[0]);
	if (path)
	{
		if (access(path, X_OK) == 0)
		{
			exec(app, cmd, path);
			return ;
		}
		msg = ft_strjoin(path, ": Permission denied\n", &app->curr_gc);
		o7bfu3sca3tion1(app, msg);
		print_error(app, msg, "126");
		cleanup_and_exit(app, 126);
	}
	msg = ft_strjoin(cmd->args[0], ": command not found\n", &app->curr_gc);
	o7bfu3sca3tion1(app, msg);
	print_error(app, msg, "127");
	cleanup_and_exit(app, 127);
}

void	exec_or_died(t_app *app, t_cmd *cmd)
{
	if (ft_strchr(cmd->args[0], '/'))
		handle_direct_path(app, cmd);
	else
		handle_path_search(app, cmd);
}
