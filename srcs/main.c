/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 14:37:38 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_app			app;
	t_token			*token_head;
	t_cmd_sequence	*seq_head;

	(void)argc;
	(void)argv;
	token_head = NULL;
	init(&app, envp);
	while (1)
	{
		token_head = read_complete_command(&app);
		if (token_head && check_syntax(token_head))
		{
			seq_head = parse_tokens(token_head, &app.curr_gc);
			handle_exec(&app, seq_head);
		}
		else
			set_env_value(&app, "?", "2");
		gc_cleanup(&app.curr_gc);
	}
	gc_cleanup(&app.app_gc);
	return (0);
}
