/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:33:52 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/16 22:25:49 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd_check_state
{
	size_t			paren_deps;
	t_parse_status	parse_status;
	char			*line;
}					t_cmd_check_state;

static bool			is_operator_start(const char *line);
void				handle_open_parenthesis(t_cmd_check_state *check_state,
						size_t *i);
void				handle_close_parenthesis(t_cmd_check_state *check_state,
						size_t *i);
void				handle_single_quote(t_cmd_check_state *check_state,
						size_t *i);
void				handle_double_quote(t_cmd_check_state *check_state,
						size_t *i);

t_parse_status	check_command_status(char *line)
{
	t_cmd_check_state	cmd_check_state;
	size_t				i;

	i = 0;
	ft_bzero(&cmd_check_state, sizeof(t_cmd_check_state));
	cmd_check_state.line = line;
	if (is_operator_start(line))
		return (print_op_start_syntax_error(line));
	while (line[i])
	{
		while (ft_isspace(line[i]) || !ft_ischarset(line[i], "()'\""))
			i++;
		handle_open_parenthesis(&cmd_check_state, &i);
		handle_close_parenthesis(&cmd_check_state, &i);
		handle_single_quote(&cmd_check_state, &i);
		handle_double_quote(&cmd_check_state, &i);
		if (cmd_check_state.parse_status != CMD_COMPLETE)
			return (cmd_check_state.parse_status);
	}
	if (cmd_check_state.paren_deps > 0)
		return (CMD_INCOMPLETE);
	return (cmd_check_state.parse_status);
}

void	handle_open_parenthesis(t_cmd_check_state *check_state, size_t *i)
{
	char	*line;

	if (check_state->parse_status > CMD_COMPLETE)
		return ;
	line = check_state->line;
	if (!line[*i] || line[*i] != '(')
		return ;
	check_state->paren_deps++;
	(*i)++;
	while (ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
	{
		check_state->parse_status = CMD_INCOMPLETE;
		return ;
	}
	if (line[*i] && line[*i] != ')')
		return ;
	check_state->parse_status = CMD_INVALID;
	print_syntax_error(")");
}

void	handle_close_parenthesis(t_cmd_check_state *check_state, size_t *i)
{
	char	*line;

	if (check_state->parse_status > CMD_COMPLETE)
		return ;
	line = check_state->line;
	if (!line[*i] || line[*i] != ')')
		return ;
	(*i)++;
	if (check_state->paren_deps-- != 0)
		return ;
	check_state->parse_status = CMD_INVALID;
	print_syntax_error(")");
}

void	handle_single_quote(t_cmd_check_state *check_state, size_t *i)
{
	char	*line;

	if (check_state->parse_status > CMD_COMPLETE)
		return ;
	line = check_state->line;
	if (!line[*i] || line[*i] != '\'')
		return ;
	(*i)++;
	if (line[*i] == '\'')
	{
		(*i)++;
		return ;
	}
	while (line[*i])
	{
		if (line[*i] != '\'')
			(*i)++;
		else
		{
			(*i)++;
			return ;
		}
	}
	check_state->parse_status = CMD_INCOMPLETE;
}

void	handle_double_quote(t_cmd_check_state *check_state, size_t *i)
{
	char	*line;

	if (check_state->parse_status > CMD_COMPLETE)
		return ;
	line = check_state->line;
	if (!line[*i] || line[*i] != '"')
		return ;
	(*i)++;
	if (line[*i] == '"')
	{
		(*i)++;
		return ;
	}
	while (line[*i])
	{
		if (line[*i] != '"' && line[(*i) - 1] != '\\')
			(*i)++;
		else
		{
			(*i)++;
			return ;
		}
	}
	check_state->parse_status = CMD_INCOMPLETE;
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
