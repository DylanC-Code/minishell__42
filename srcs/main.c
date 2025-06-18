/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/14 10:42:35 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_app	app;
	char	*line;
	t_token	*token_head;
	t_cmd_sequence *seq_head;
	t_garbage	*gc_current_cmd_line;

	(void)argc;
	(void)argv;
	init(&app, envp);
	gc_current_cmd_line = NULL;
	while (1)
	{
		line = readline(USER_PROMPT);
		//display_tokens(token_head, line);
		token_head = tokenizer(line, &gc_current_cmd_line);
		seq_head = parse_tokens(token_head);
		display_seq(seq_head);
		//display_tokens(token_head, line);
	}
	return (0);
}
