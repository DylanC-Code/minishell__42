/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/21 18:39:57 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	init_exec(t_cmd_sequence *head_seq)
{
	if (!collect_heredocs(head_seq))
		return (ERROR);
	resolve_all_redirection(head_seq);
	return (SUCCESS);
}

void	handle_exec(t_app *app, t_cmd_sequence *head_seq)
{
	if (!collect_heredocs(head_seq))
		return ;
	resolve_all_redirection(head_seq);
	while (head_seq)
	{
		if (!setup_pipes(head_seq, &app->garb_head))
			return ;
		exec_sequence(app, head_seq);
		head_seq = head_seq->next;
	}
	// exec_command(&head_seq->cmds[0]);
}
