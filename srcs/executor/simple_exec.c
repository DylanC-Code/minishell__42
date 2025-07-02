/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:16:45 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 17:21:16 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple_cmd(t_app *app, t_cmd *cmd)
{
	while (*cmd->args && !**cmd->args)
		cmd->args++;
	if (cmd->failed || !*cmd->args)
	{
		set_env_value(app, "?", "0");
		safe_close(&cmd->fd_in);
		safe_close(&cmd->fd_out);
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("fork"));
	if (cmd->pid > 0)
		return (close_fds_in_parents(cmd));
	return (child_exec(app, cmd));
}
