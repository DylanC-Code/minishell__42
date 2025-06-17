/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/17 14:28:46 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_app		app;
	t_token		*token_head;
	t_garbage	*gc_current_cmd_line;
	char		*cmd_line;

	(void)argc;
	(void)argv;
	(void)token_head;
	init(&app, envp);
	gc_current_cmd_line = NULL;
	while (1)
	{
		cmd_line = read_complete_command(&gc_current_cmd_line);
		// token_head = tokenizer(cmd_line, &gc_current_cmd_line);
		// display_tokens(token_head, cmd_line);
		// check_syntax(token_head);
		// if (token_head && check_syntax(token_head))
		// {
		// 	printf("VALID SYNTAX ✅\n");
		// }
		// else
		// 	printf("INVALID SYNTAX ❌\n");
		gc_cleanup(&gc_current_cmd_line);
	}
	return (0);
}
