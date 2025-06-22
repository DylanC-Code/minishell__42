/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:34:55 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/22 09:26:23 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds_in_parents(t_cmd *cmd)
{
	safe_close(&cmd->fd_in);
	safe_close(&cmd->fd_out);
}
