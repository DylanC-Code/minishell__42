/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 12:17:42 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_logical_op(t_cmd_sequence *seq);

void	handle_exec(t_app *app, t_cmd_sequence *head_seq)
{
	if (!collect_heredocs(app, head_seq))
		return ;
	resolve_all_redirection(app, head_seq);
	while (head_seq)
	{
		if (!setup_pipes(head_seq, &app->curr_gc))
			return ;
		exec_sequence(app, head_seq);
		if (!check_logical_op(head_seq))
			return ;
		head_seq = head_seq->next;
	}
}

static bool	check_logical_op(t_cmd_sequence *seq)
{
    if (seq->logical_op == LOGICAL_AND && seq->last_exit_status == 0)
		return (true);
	if (seq->logical_op == LOGICAL_OR && seq->last_exit_status != 0)
		return (true);
	return (false);
}
