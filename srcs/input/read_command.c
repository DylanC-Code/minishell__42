/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:26:29 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/23 14:42:25 by dcastor          ###   ########.fr       */
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

char	*get_prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup(SHELL_EMOJI " " BBLUE "minishell" RESET "$"));
	prompt = malloc(strlen(cwd) + 100);
	if (!prompt)
		return (NULL);
	sprintf(prompt, PROMPT, cwd);
	free(cwd);
	return (prompt);
}

char	*get_user_input(t_garbage **gb_list)
{
	char	*line;

	line = readline(get_prompt());
	if (!line)
		return (NULL);
	add_history(line);
	add_to_gc(gb_list, line);
	return (line);
}
