/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:22:18 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 16:04:23 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool				is_operator_end(const char *line);
static bool				is_operator_start(const char *line);
static void				handle_quote_none(char c, t_quote *quote,
							int *paren_depth);
static void				handle_quote_active(char c, char prev_char,
							t_quote *quote);
static t_parse_status	get_final_status(t_quote quote, int paren_depth,
							char *line);

t_parse_status	check_command_status(char *line)
{
	t_quote	quote;
	int		paren_depth;
	int		i;

	if (!line)
		return (CMD_INVALID);
	if (is_operator_start(line))
		return (print_op_start_syntax_error(line));
	quote = QUOTE_NONE;
	paren_depth = 0;
	i = 0;
	while (line[i])
	{
		if (quote == QUOTE_NONE)
			handle_quote_none(line[i], &quote, &paren_depth);
		else if (i > 0)
			handle_quote_active(line[i], line[i - 1], &quote);
		else
			handle_quote_active(line[i], '\0', &quote);
		if (line[i] == ')' && paren_depth < 0)
			return (print_syntax_error(")"));
		i++;
	}
	return (get_final_status(quote, paren_depth, line));
}

static void	handle_quote_none(char c, t_quote *quote, int *paren_depth)
{
	if (c == '\'')
		*quote = QUOTE_SINGLE;
	if (c == '"')
		*quote = QUOTE_DOUBLE;
	if (c == '(')
		(*paren_depth)++;
	if (c == ')')
		(*paren_depth)--;
}

static void	handle_quote_active(char c, char prev_char, t_quote *quote)
{
	if (*quote == QUOTE_SINGLE && c == '\'')
		*quote = QUOTE_NONE;
	if (*quote == QUOTE_DOUBLE && c == '"' && prev_char != '\\')
		*quote = QUOTE_NONE;
}

static t_parse_status	get_final_status(t_quote quote, int paren_depth,
		char *line)
{
	if (quote != QUOTE_NONE)
		return (CMD_INCOMPLETE);
	if (paren_depth > 0)
		return (CMD_INCOMPLETE);
	if (is_operator_end(line))
		return (CMD_INCOMPLETE);
	return (CMD_COMPLETE);
}

static bool	is_operator_end(const char *line)
{
	int	i;

	if (!line)
		return (false);
	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	if (i < 0)
		return (false);
	if (line[i] == '|')
		return (true);
	if (line[i] == '&')
		return (true);
	if (i >= 1 && line[i - 1] == '|' && line[i] == '|')
		return (true);
	if (i >= 1 && line[i - 1] == '&' && line[i] == '&')
		return (true);
	return (false);
}

static bool	is_operator_start(const char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '|')
		return (true);
	if (*line == '&')
		return (true);
	if (*line == '\0')
		return (false);
	return (false);
}
