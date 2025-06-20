/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 16:51:55 by dcastor          ###   ########.fr       */
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

void	handle_exec(t_app *app, t_cmd_sequence *head_seq)
{
	// exec_command(&head_seq->cmds[0]);
	(void)app;
	(void)head_seq;
}
