/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/13 14:25:52 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_app	app;
	char	*line;
	t_token	*token_head;
	t_cmd_sequence *seq_head;
	(void)argc;
	(void)argv;
	init(&app, envp);
	while (1)
	{
		line = readline(USER_PROMPT);
		token_head = tokenizer(&app, line);
		//display_tokens(token_head, line);
		seq_head = parse_tokens(token_head);
		display_seq(seq_head);
	}
	return (0);
}
