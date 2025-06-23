/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:54:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 14:44:10 by dcastor          ###   ########.fr       */
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
		token_head = read_complete_command(&app.curr_gc);
		if (token_head && check_syntax(token_head))
		{
			seq_head = parse_tokens(token_head);
			handle_exec(&app, seq_head);
		}
		gc_cleanup(&app.curr_gc);
		printf("$? == %d\n", ft_atoi(get_env_value(app.env_head, "?")));
	}
	return (0);
}
