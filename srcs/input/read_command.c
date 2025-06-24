/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:26:29 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 09:59:13 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*append_newline_token(t_token **token_list, t_garbage **gc_list);
char	*get_user_input(t_garbage **gb_list);

t_token	*read_complete_command(t_garbage **gc)
{
	char	*line;
	t_token	*token_head;

	line = get_user_input(gc);
	token_head = tokenizer(line, gc);
	// display_tokens(token_head, line);
	return (token_head);
}

char	*get_prompt(t_garbage **gc)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup(SHELL_EMOJI " " BBLUE "minishell" RESET "$", gc));
	add_to_gc(gc, cwd);
	prompt = gc_malloc(strlen(cwd) + 100, gc);
	if (!prompt)
		return (NULL);
	sprintf(prompt, PROMPT, cwd); // TODO: remove
	return (prompt);
}

char	*get_user_input(t_garbage **gc)
{
	char	*line;

	line = readline(get_prompt(gc));
	if (!line)
		return (NULL);
	add_history(line);
	add_to_gc(gc, line);
	return (line);
}
