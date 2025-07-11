/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/03 11:07:24 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_app	app;
	t_token	*token_head;

	(void)argc;
	(void)argv;
	token_head = NULL;
	init(&app, envp);
	while (1)
	{
		gc_cleanup(&app.curr_gc);
		token_head = read_complete_command(&app);
		if (!check_syntax(&app, token_head))
			continue ;
		app.seq_head = parse_tokens(token_head, &app.curr_gc, &app);
		handle_expansion(&app);
		handle_exec(&app, app.seq_head);
	}
	cleanup_and_exit(&app, EXIT_FAILURE);
	return (0);
}
