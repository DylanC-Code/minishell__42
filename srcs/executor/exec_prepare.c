/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:34:55 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:40:32 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds_in_parents(t_cmd *cmd)
{
	safe_close(&cmd->fd_in);
	safe_close(&cmd->fd_out);
}

void	close_pipes(t_cmd *cmd)
{
	int	i;

	if (!cmd->pipes)
		return ;
	i = 0;
	while (cmd->pipes[i])
	{
		safe_close(&cmd->pipes[i][0]);
		safe_close(&cmd->pipes[i][1]);
		i++;
	}
}
