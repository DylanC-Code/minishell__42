/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/20 15:55:04 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	handle_heredoc(t_redir_list *heredoc_redir, t_garbage **gc)
{
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	tmp = readline(PS2_PROMPT);
	if (!tmp)
		return (ERROR);
	while (ft_strcmp(tmp, heredoc_redir->name))
	{
		if (!tmp)
			return (ERROR);
		if (!buffer)
			buffer = tmp;
		else
			ft_strjoin(buffer, tmp);
		tmp = readline(PS2_PROMPT);
	}
	return (SUCCESS);
}

void	handle_heredocs_cmd(t_cmd *cmd)
{
	t_redir_list	*redir_head;

	redir_head = cmd->redir_list;
	while (redir_head)
	{
		if (redir_head->type == TOKEN_REDIR_HEREDOC)
			handle_heredoc(redir_head);
		redir_head = redir_head->next;
	}
}

t_status	init_cmd(t_cmd *cmd)
{
	t_redir_list	*redir_head;

	redir_head = NULL;
	// if (!pipe(cmd->input_file))
	// 	return ; // todo: handle error
	handle_heredocs_cmd(cmd);
	// while (redir_head)
	// {
	// 	// if (redir_head->type == TOKEN_REDIR_IN)
	// 	if (!handle_redir_in_cmd(cmd, redir_head))
	// 		return (ERROR);
	// }
	return (SUCCESS);
}

void	init_sequence(t_cmd_sequence *seq)
{
	t_cmd	*cmd;

	cmd = seq->cmds;
	while (cmd)
	{
		init_cmd(cmd);
		cmd = cmd->next;
	}
}

t_status	handle_heredocs(t_cmd_sequence *head_seq)
{
	t_cmd	*cmd;

	while (head_seq)
	{
		cmd = head_seq->cmds;
		while (cmd)
		{
			handle_heredocs_cmd(cmd);
			cmd = cmd->next;
		}
		head_seq = head_seq->next;
	}
	return (SUCCESS);
}

t_status	handle_redir_in(t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_IN)
		return (NOOP);
	redir->fds[0] = open(redir->name, O_RDONLY);
	if (redir->fds[0] <= 0)
		return (perror(redir->name), ERROR);
	return (SUCCESS);
}

t_status	handle_redir_out(t_redir_list *redir)
{
	if (redir->type != TOKEN_REDIR_OUT)
		return (NOOP);
	redir->fds[0] = open(redir->name, O_CREAT | O_TRUNC);
	if (redir->fds[0] <= 0)
		return (perror(redir->name), ERROR);
	return (SUCCESS);
}

t_status	handle_redirections(t_cmd *cmd)
{
	t_redir_list	*redir;
	t_redir_list	*prev_in;
	t_redir_list	*prev_out;

	prev_in = NULL;
	prev_out = NULL;
	redir = cmd->redir_list;
	while (redir)
	{
		if (!handle_redir_in(redir))
			return (ERROR);
		if (!handle_redir_out(redir))
			return (ERROR);
		// if (redir->type == TOKEH)
		redir = redir->next;
	}
	return (SUCCESS);
}

t_status	init_exec(t_cmd_sequence *head_seq)
{
	t_cmd	*cmd;

	if (!handle_heredocs(head_seq))
		return (ERROR);
	while (head_seq)
	{
		cmd = head_seq->cmds;
		while (cmd)
		{
			if (!handle_redirections(cmd))
				return (ERROR);
			cmd = cmd->next;
		}
	}
	return (SUCCESS);
}

t_status	exec_simple_cmd(t_app *app, t_cmd *cmd)
{
	if (!handle_redirections(cmd))
		return (ERROR);
	cmd->pid = fork();
	// if (cmd.pid)
}

void	handle_exec(t_app *app, t_cmd_sequence *head_seq)
{
	init_exec(head_seq);
	// while
	// exec_command(&head_seq->cmds[0]);
	(void)app;
	(void)head_seq;
}
