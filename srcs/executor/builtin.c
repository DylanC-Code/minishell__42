/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:10:41 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:46:43 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0);
}

static void	dispatch_builtin(t_app *app, t_cmd *cmd)
{
	char	**args;

	args = cmd->args + 1;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		cd_builtin(app, args);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		echo_builtin(app, args);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit_builtin(app, args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		export_builtin(app, args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		pwd_builtin(app, args);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		unset_builtin(app, args);
}

void	exec_builtin(t_app *app, t_cmd *cmd)
{
	int	saved_stdout;

	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			exit_with_error(app, "dup2");
	}
	dispatch_builtin(app, cmd);
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
	{
		safe_close(&cmd->fd_out);
		safe_close(&cmd->fd_in);
		if (dup2(saved_stdout, STDOUT_FILENO) < 0)
			exit_with_error(app, "dup2");
		safe_close(&saved_stdout);
	}
}
