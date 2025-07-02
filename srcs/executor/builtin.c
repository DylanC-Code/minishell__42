/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:10:41 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/01 13:42:10 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0);
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
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		env_builtin(app, args);
}

void	exec_builtin(t_app *app, t_cmd *cmd)
{
	char	*exit_status;

	dispatch_builtin(app, cmd);
	exit_status = get_env_value(app->env_head, "?");
	cleanup_and_exit(app, ft_atoi(exit_status));
}

void	exec_single_builtin(t_app *app, t_cmd *cmd)
{
	dispatch_builtin(app, cmd);
	safe_close(&cmd->fd_out);
	safe_close(&cmd->fd_in);
}
