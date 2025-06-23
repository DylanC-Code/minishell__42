/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:16:45 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 12:03:11 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	exec_simple_cmd(t_app *app, t_cmd *cmd)
{
	if (cmd->failed)
		return (ERROR);
	if (!cmd->args[0])
		return (SUCCESS);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("fork"), ERROR);
	if (cmd->pid == 0)
		return (child_exec(app, cmd), SUCCESS);
	close_fds_in_parents(cmd);
	return (SUCCESS);
}
