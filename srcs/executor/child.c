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

char	*find_in_path(t_app *app, const char *cmd)
{
	char	*path;
	char	*env_path;
	char	**paths;
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
		path = ft_strjoin(paths[i], "/", &app->curr_gc);
		if (!path)
			return (NULL);
		path = ft_strjoin(path, cmd, &app->curr_gc);
		if (!path)
			return (NULL);
		if (!access(path, X_OK))
			break ;
		if (errno == 13)
			exit_with_error(app, path);
		i++;
	}
	if (!access(path, X_OK))
		return (path);
	return (NULL);
}

void	exec(t_app *app, t_cmd *cmd, char *path)
{
	execve(path, cmd->args, env_list_to_envp(app->env_head, &app->app_gc));
	exit_with_error(app, "execve");
}

void	exec_or_died(t_app *app, t_cmd *cmd)
{
	char	*path;
	char	*msg;

	if (!access(cmd->args[0], X_OK))
		return (exec(app, cmd, cmd->args[0]));
	if (errno == 13)
		exit_with_error(app, cmd->args[0]);
	path = find_in_path(app, cmd->args[0]);
	if (path)
		return (exec(app, cmd, path));
	msg = ft_strjoin(cmd->args[0], " command not found\n", &app->app_gc);
	if (!msg)
		cleanup_and_exit(app, errno);
	print_error(app, msg, "127");
	cleanup_and_exit(app, 127);
}
