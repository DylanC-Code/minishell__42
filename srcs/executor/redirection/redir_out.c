/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:46:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:46:45 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_out(t_app *app, t_cmd *cmd, t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_OUT)
		return ;
	redir->fd = open(redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->fd < 0)
	{
		cmd->failed = true;
		set_env_value(app, "?", ft_itoa(errno, &app->curr_gc));
		perror(redir->name);
		return ;
	}
	safe_close(&cmd->fd_out);
	cmd->fd_out = redir->fd;
}

void	handle_redir_append(t_app *app, t_cmd *cmd, t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_APPEND)
		return ;
	redir->fd = open(redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		cmd->failed = true;
		set_env_value(app, "?", ft_itoa(errno, &app->curr_gc));
		perror(redir->name);
		return ;
	}
	safe_close(&cmd->fd_out);
	cmd->fd_out = redir->fd;
}
