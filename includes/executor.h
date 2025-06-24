/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:56 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/22 09:25:47 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "init.h"
# include "input.h"
# include "minishell.h"

void		handle_exec(t_app *app, t_cmd_sequence *head_seq);
t_status	collect_heredocs(t_cmd_sequence *head_seq);
void		resolve_all_redirection(t_cmd_sequence *seq);
t_status	setup_pipes(t_cmd_sequence *seq, t_garbage **gc);
t_status	exec_simple_cmd(t_app *app, t_cmd *cmd);
t_status	exec_sequence(t_app *app, t_cmd_sequence *seq);
void		child_exec(t_app *app, t_cmd *cmd);
void		close_fds_in_parents(t_cmd *cmd);
int	handle_expansion(t_app *app, t_cmd_sequence *head_seq);

#endif
