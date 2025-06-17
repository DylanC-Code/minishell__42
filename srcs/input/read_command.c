/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:26:29 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/17 14:21:50 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*append_eof_token(t_token **token_list, t_garbage **gc_list);
char	*get_user_input(char *prompt, t_garbage **gb_list);

char	*read_complete_command(t_garbage **gc)
{
	char			*accum;
	char			*line;
	char			*tmp;
	t_parse_status	status;

	accum = NULL;
	line = get_user_input(USER_PROMPT, gc);
	while (true)
	{
		if (accum)
			tmp = ft_strjoin(accum, "\n");
		else
			tmp = ft_strjoin(accum, "");
		accum = ft_strjoin(tmp, line);
		(add_to_gc(gc, tmp), add_to_gc(gc, accum));
		status = check_command_status(accum);
		if (status == CMD_INVALID)
			return (NULL);
		if (status == CMD_COMPLETE)
			break ;
		line = get_user_input("> ", gc);
	}
	return (accum);
}


char	*get_user_input(char *prompt, t_garbage **gb_list)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		return (NULL);
	add_history(line);
	add_to_gc(gb_list, line);
	return (line);
}
