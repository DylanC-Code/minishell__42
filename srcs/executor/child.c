/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:32:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/22 09:26:03 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exec(t_app *app, t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 0)
		dup2(cmd->fd_out, STDOUT_FILENO);
	safe_close(&cmd->fd_in);
	safe_close(&cmd->fd_out);
	if (!access(cmd->args[0], X_OK))
		execve(cmd->args[0], cmd->args, env_list_to_envp(app->env_head,
				&app->garb_head));
}
