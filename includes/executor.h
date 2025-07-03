/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:27:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 09:27:40 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "init.h"
# include "input.h"
# include "minishell.h"

void		handle_exec(t_app *app, t_cmd_sequence *head_seq);
t_status	collect_heredocs(t_app *app, t_cmd_sequence *head_seq);
void		resolve_all_redirection(t_app *app, t_cmd_sequence *seq);
t_status	setup_pipes(t_cmd_sequence *seq, t_garbage **gc);
void		exec_simple_cmd(t_app *app, t_cmd *cmd);
void		exec_sequence(t_app *app, t_cmd_sequence *seq);
void		child_exec(t_app *app, t_cmd *cmd);
void		close_fds_in_parents(t_cmd *cmd);
void		close_pipes(t_cmd *cmd);
void		exec_builtin(t_app *app, t_cmd *cmd);
bool		is_builtin(const char *cmd);
int			handle_expansion(t_app *app, t_cmd_sequence *head_seq);
void		exec_single_builtin(t_app *app, t_cmd *cmd);

#endif
