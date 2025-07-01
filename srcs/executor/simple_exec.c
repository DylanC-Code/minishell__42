/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:16:45 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/01 13:38:52 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple_cmd(t_app *app, t_cmd *cmd)
{
	if (cmd->failed || !cmd->args[0])
		return ;
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("fork"));
	if (cmd->pid > 0)
		return (close_fds_in_parents(cmd));

	return (child_exec(app, cmd));
}
