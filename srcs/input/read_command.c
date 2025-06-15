/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:26:29 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/15 22:42:21 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_parse_status
{
	INCOMPLETE,
	COMPLETE,
	INVALID,
}		t_parse_status;

t_token	*append_eof_token(t_token **token_list, t_garbage **gc_list);
t_token	*get_user_input_and_tokenize(char *prompt, t_garbage **gb_list);

t_token	*read_complete_command(t_garbage **gc_current_cmd_line)
{
	t_parse_status	parsing_state;
	t_token			*token_head;
	t_token			*token_sequence;

	token_head = get_user_input_and_tokenize(USER_PROMPT, gc_current_cmd_line);
	while (true)
	{
		parsing_state = check_command_state(token_head);
		if (parsing_state == INVALID)
			return (NULL);
		else if (parsing_state == COMPLETE)
			break ;
		token_sequence = get_user_input_and_tokenize(">", gc_current_cmd_line);
		if (!token_sequence)
			return (NULL);
		add_token_back(&token_head, token_sequence);
	}
	return (append_eof_token(&token_head, gc_current_cmd_line));
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
