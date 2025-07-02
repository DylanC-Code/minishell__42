/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:32:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/01 14:58:50 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_or_died(t_app *app, t_cmd *cmd);
void	close_fds_and_pipes(t_cmd *cmd);

void	child_exec(t_app *app, t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 0)
		dup2(cmd->fd_out, STDOUT_FILENO);
	close_fds_and_pipes(cmd);
	if (is_builtin(cmd->args[0]))
		return (exec_builtin(app, cmd));
	exec_or_died(app, cmd);
}

void	close_fds_and_pipes(t_cmd *cmd)
{
	close_pipes(cmd);
	while (cmd)
	{
		safe_close(&cmd->fd_in);
		safe_close(&cmd->fd_out);
		cmd = cmd->next;
	}
}

char	*build_path(t_app *app, char *dir, char *cmd)
{
	char	*path;

	path = ft_strjoin(dir, "/", &app->curr_gc);
	if (!path)
		return (NULL);
	path = ft_strjoin(path, cmd, &app->curr_gc);
	return (path);
}


char *find_in_path(t_app *app, char *cmd)
{
	char	*env_path;
	char	**paths;
	char	*result;
	int		i;

	env_path = get_env_value(app->env_head, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':', &app->curr_gc);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		result = build_path(app, paths[i], cmd);
		if (!result)
			return (NULL);
		if (access(result, X_OK) == 0)
			return (result);
		if (errno == 13)
			exit_with_error(app, result);
		i++;
	}
	return (NULL);
}

void	exec(t_app *app, t_cmd *cmd, char *path)
{
	execve(path, cmd->args, env_list_to_envp(app->env_head, &app->app_gc));
	exit_with_error(app, "execve");
}

void handle_direct_path(t_app *app, t_cmd *cmd)
{
	struct stat	stat_buf;
	char		*msg;

	if (access(cmd->args[0], F_OK) != 0)
	{
		msg = ft_strjoin(cmd->args[0], ": No such file or directory\n", &app->curr_gc);
		print_error(app, msg, "127");
		cleanup_and_exit(app, 127);
	}
	if (stat(cmd->args[0], &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
	{
		msg = ft_strjoin(cmd->args[0], ": Is a directory\n", &app->curr_gc);
		print_error(app, msg, "126");
		cleanup_and_exit(app, 126);
	}
	if (access(cmd->args[0], X_OK) != 0)
	{
		msg = ft_strjoin(cmd->args[0], ": Permission denied\n", &app->curr_gc);
		print_error(app, msg, "126");
		cleanup_and_exit(app, 126);
	}
	exec(app, cmd, cmd->args[0]);
}

void handle_path_search(t_app *app, t_cmd *cmd)
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
		print_error(app, msg, "126");
		cleanup_and_exit(app, 126);
	}
	msg = ft_strjoin(cmd->args[0], ": command not found\n", &app->curr_gc);
	print_error(app, msg, "127");
	cleanup_and_exit(app, 127);
}

void exec_or_died(t_app *app, t_cmd *cmd)
{
	if (ft_strchr(cmd->args[0], '/'))
		handle_direct_path(app, cmd);
	else
		handle_path_search(app, cmd);
}