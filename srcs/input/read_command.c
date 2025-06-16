/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:26:29 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 18:02:35 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*append_eof_token(t_token **token_list, t_garbage **gc_list);
t_token	*get_user_input_and_tokenize(char *prompt, t_garbage **gb_list);

t_token	*read_complete_command(t_garbage **gc)
{
	char			*accum;
	char			*line;
	char			*tmp;
	t_parse_status	status;
	t_token			*tokens;

	accum = NULL;
	while (true)
	{
		line = readline(accum ? "> " : USER_PROMPT);
		if (!line)
			return (NULL);
		add_history(line);
		tmp = ft_strjoin(accum, accum ? "\n" : "");
		free(accum);
		accum = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		status = check_command_status(accum);
		if (status == CMD_INVALID)
			return (free(accum), NULL);
		if (status == CMD_COMPLETE)
			break ;
	}
	tokens = tokenizer(accum, gc);
	free(accum);
	append_eof_token(&tokens, gc);
	return (tokens);
}

t_token	*append_eof_token(t_token **token_list, t_garbage **gc_list)
{
	t_token	*eof_token;

	eof_token = gc_malloc(sizeof(t_token), gc_list);
	if (!eof_token)
		return (NULL);
	ft_bzero(eof_token, sizeof(t_token));
	handle_eof_token(eof_token);
	add_token_back(token_list, eof_token);
	return (*token_list);
}

t_token	*get_user_input_and_tokenize(char *prompt, t_garbage **gb_list)
{
	char	*line;

	line = readline(prompt);
	add_history(line);
	return (tokenizer(line, gb_list));
}
