/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:26:29 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 16:05:36 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*append_newline_token(t_token **token_list, t_garbage **gc_list);
char	*get_user_input(t_app *app);

t_token	*read_complete_command(t_app *app)
{
	char	*line;
	t_token	*token_head;

	set_env_value(app, "?", "0");
	line = get_user_input(app);
	token_head = tokenizer(app, line);
	if (!token_head)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (token_head);
}

char	*get_user_input(t_app *app)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(app);
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	if (!line)
		(cleanup(app), exit(EXIT_SUCCESS));
	add_history(line);
	add_to_gc(&app->curr_gc, line);
	return (line);
}
