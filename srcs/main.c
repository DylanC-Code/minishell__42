/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 09:28:41 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_app		app;
	char		*line;
	t_token		*token_head;
	t_garbage	*gc_current_cmd_line;

	(void)argc;
	(void)argv;
	init(&app, envp);
	gc_current_cmd_line = NULL;
	while (1)
	{
		line = readline(USER_PROMPT);
		token_head = tokenizer(line, &gc_current_cmd_line);
		display_tokens(token_head, line);
		// if (check_syntax(token_head))
		// 	printf("VALID SYNTAX ✅\n");
		// else
		// 	printf("INVALID SYNTAX ❌\n");
	}
	return (0);
}
