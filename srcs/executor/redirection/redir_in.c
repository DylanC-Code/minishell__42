/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:46:00 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:47:27 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_in(t_app *app, t_cmd *cmd, t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_IN)
		return ;
	redir->fd = open(redir->name, O_RDONLY);
	if (redir->fd < 0)
	{
		cmd->failed = true;
		set_env_value(app, "?", ft_itoa(errno, &app->curr_gc));
		perror(redir->name);
		return ;
	}
	safe_close(&cmd->fd_in);
	cmd->fd_in = redir->fd;
}
