/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/18 16:25:54 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_garbage		*gc_current_cmd_line;
	t_app			app;
	t_token			*token_head;
	t_cmd_sequence	*seq_head;
	t_redir_list	*redir_head;

	(void)argc;
	(void)argv;
	token_head = NULL;
	init(&app, envp);
	gc_current_cmd_line = NULL;
	while (1)
	{
		token_head = read_complete_command(&gc_current_cmd_line);
		if (token_head && check_syntax(token_head))
		{
			seq_head = parse_tokens(token_head, &redir_head);
			display_seq(seq_head);
			handle_exec(&app, seq_head, redir_head);
		}
		gc_cleanup(&gc_current_cmd_line);
	}
	return (0);
}
