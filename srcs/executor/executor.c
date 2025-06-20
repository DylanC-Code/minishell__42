/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/20 14:05:58 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void exec_heredoc(char *limiter)
// {

// }

// int	*handle_heredocs(t_cmd *)
// {

// }

// int	exec_command(t_cmd *head)
// {
// 	char	*path;

//     handle_heredocs(head->heredoc_delim)

// 	path = ft_strjoin("/bin/", head->args[0]);
// 	return (execve(path, head->args, NULL));
// }

// int	handle_seq(t_app *app, t_cmd_sequence *head)
// {
// 	int	last_exit_code;
// }

// void	handle_heredocs(t_redir_list *redir_head)
// {
// 	while (redir_head && redir_head->next)
//     {
//         if (redir_head->type == TOKEN_REDIR_HEREDOC)
//     }
// }

t_status	handle_heredoc(t_redir_list *heredoc_redir)
{
	char	*buffer;
	char	*tmp;
	int		*fds;

	fds = heredoc_redir->fds;
	if (pipe(heredoc_redir->fds))
		return (ERROR); // todo: handle error
	buffer = NULL;
	tmp = readline(PS2_PROMPT);
	while (ft_strcmp(tmp, heredoc_redir->name))
	{
		if (!buffer)
			buffer = tmp;
		else
			ft_strjoin(buffer, tmp);
		tmp = readline(PS2_PROMPT);
	}
	write(fds[1], buffer, ft_strlen(buffer));
	close(fds[1]);
	return (SUCCESS);
}

void	handle_heredocs_cmd(t_cmd *cmd)
{
	t_redir_list	*redir_head;

	redir_head = cmd->redir_list;
	while (redir_head)
	{
		if (redir_head->type == TOKEN_REDIR_HEREDOC)
		{
			handle_heredoc(redir_head);
		}
		redir_head = redir_head->next;
	}
}

// t_status	handle_redir_in_cmd(t_cmd *cmd, t_redir_list *redir)
// {
// }

t_status	init_cmd(t_cmd *cmd)
{
	t_redir_list	*redir_head;

	redir_head = NULL;
	// if (!pipe(cmd->input_file))
	// 	return ; // todo: handle error
	handle_heredocs_cmd(cmd);
	while (redir_head)
	{
		// if (redir_head->type == TOKEN_REDIR_IN)
		// if (!handle_redir_in_cmd(cmd, redir_head))
		// 	return (ERROR);
	}
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

void	init_exec(t_cmd_sequence *head_seq)
{
	while (head_seq)
	{
		init_sequence(head_seq);
		head_seq = head_seq->next;
	}
}

void	handle_exec(t_app *app, t_cmd_sequence *head_seq)
{
	init_exec(head_seq);
	// exec_command(&head_seq->cmds[0]);
	(void)app;
	(void)head_seq;
}
