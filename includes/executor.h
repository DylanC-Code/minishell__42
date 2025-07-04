/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:27:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:25:22 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "init.h"
# include "input.h"
# include "minishell.h"

void		handle_exec(t_app *app, t_cmd_sequence *head_seq);
t_status	collect_heredocs(t_app *app, t_cmd_sequence *head_seq);
t_status	setup_pipes(t_cmd_sequence *seq, t_garbage **gc);
void		exec_simple_cmd(t_app *app, t_cmd *cmd);
void		exec_sequence(t_app *app, t_cmd_sequence *seq);
void		child_exec(t_app *app, t_cmd *cmd);
void		close_fds_in_parents(t_cmd *cmd);
void		close_pipes(t_cmd *cmd);
void		exec_builtin(t_app *app, t_cmd *cmd);
bool		is_builtin(const char *cmd);
int			handle_expansion(t_app *app);
void		exec_single_builtin(t_app *app, t_cmd *cmd);

/* Child */
char		*build_path(t_app *app, char *dir, char *cmd);
char		*find_in_path(t_app *app, char *cmd);
void		close_other_fds(t_cmd_sequence *seq_head);
void		close_fds_and_pipes(t_cmd_sequence *seq_head, t_cmd *current_cmd);
void		child_exec(t_app *app, t_cmd *cmd);
void		exec(t_app *app, t_cmd *cmd, char *path);
void		handle_direct_path(t_app *app, t_cmd *cmd);
void		handle_path_search(t_app *app, t_cmd *cmd);
void		exec_or_died(t_app *app, t_cmd *cmd);

/* Redirection */
void		resolve_all_redirection(t_app *app, t_cmd_sequence *seq);
void		handle_redir_out(t_app *app, t_cmd *cmd, t_redir_list *redir);
void		handle_redir_append(t_app *app, t_cmd *cmd, t_redir_list *redir);
void		handle_redir_in(t_app *app, t_cmd *cmd, t_redir_list *redir);

/* Heredoc */
void		heredoc_child(t_app *app, t_redir_list *heredoc_redir, int fds[2]);
t_status	heredoc_parent(t_app *app, t_redir_list *redir_list, pid_t pid,
				int fds[2]);
t_status	collect_heredocs(t_app *app, t_cmd_sequence *head_seq);
void		close_previous_heredoc_fd(t_cmd_sequence *seq_head);

#endif
