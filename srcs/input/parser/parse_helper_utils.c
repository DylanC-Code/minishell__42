/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:05:04 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:12:14 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_command_delimiter(t_token_type type);
int				is_redirection_operator(t_token_type type);
static t_token	*advance_token_count(t_token *current, size_t *arg_count);
size_t			count_words(t_token *start_token);

static int	is_command_delimiter(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_NEW_LINE || type == TOKEN_OPEN_PARENTHESIS
		|| type == TOKEN_CLOSE_PARENTHESIS);
}

int	is_redirection_operator(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC));
}

static t_token	*advance_token_count(t_token *current, size_t *arg_count)
{
	if (current->type == TOKEN_WORD)
	{
		(*arg_count)++;
		return (current->next);
	}
	if (is_redirection_operator(current->type))
	{
		current = current->next;
		if (current && current->type == TOKEN_WORD)
			return (current->next);
	}
	return (current->next);
}

size_t	count_words(t_token *start_token)
{
	size_t	arg_count;
	t_token	*current;

	current = start_token;
	arg_count = 0;
	if (current && current->type == TOKEN_OPEN_PARENTHESIS)
		current = current->next;
	while (current && !is_command_delimiter(current->type))
		current = advance_token_count(current, &arg_count);
	return (arg_count);
}
