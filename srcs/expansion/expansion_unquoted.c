/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_unquoted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:33:48 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:35:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_unquoted_vars(t_app *app, int *pos, int *last_pos, int start)
{
	char	*result;

	result = ft_strdup("", &app->curr_gc);
	if (!result)
		cleanup_and_exit(app, EXIT_FAILURE);
	*pos = start;
	*last_pos = start;
	return (result);
}

char	*process_unquoted_text(char *arg, int start, int end, t_app *app)
{
	char	*result;
	char	*part;
	int		pos;
	int		last_pos;

	result = set_unquoted_vars(app, &pos, &last_pos, start);
	while (pos < end)
	{
		if (arg[pos] == '$' && pos + 1 < end && (arg[pos + 1] == '"' || arg[pos
				+ 1] == '\''))
		{
			result = add_text_before_dollar(result, arg, last_pos, pos, app);
			part = handle_dollar_patterns(arg, &pos, app);
			result = ft_strjoin(result, part, &app->curr_gc);
			if (!result)
				cleanup_and_exit(app, EXIT_FAILURE);
			last_pos = pos;
		}
		else
			pos++;
	}
	return (handle_remaining_text(result, arg, last_pos, end, app));
}

char	*handle_unquoted_part(char *arg, int start, int *i, t_app *app)
{
	int	end;

	end = start;
	while (arg[end] && arg[end] != '"' && arg[end] != '\'')
	{
		if (arg[end] == '$' && (arg[end + 1] == '"' || arg[end + 1] == '\''))
		{
			end += 2;
			if (arg[end - 1] == '"')
			{
				while (arg[end] && arg[end] != '"')
					end++;
			}
			else
			{
				while (arg[end] && arg[end] != '\'')
					end++;
			}
			if (arg[end])
				end++;
		}
		else
			end++;
	}
	return (*i = end, process_unquoted_text(arg, start, end, app));
}

char	*add_text_before_dollar(char *result, char *arg, int last_pos, int pos,
		t_app *app)
{
	char	*part;

	if (pos > last_pos)
	{
		part = ft_strndup(arg + last_pos, pos - last_pos, &app->curr_gc);
		if (!part)
			cleanup_and_exit(app, EXIT_FAILURE);
		part = process_variable_expansion(part, app);
		result = ft_strjoin(result, part, &app->curr_gc);
		if (!result)
			cleanup_and_exit(app, EXIT_FAILURE);
	}
	return (result);
}

char	*handle_remaining_text(char *result, char *arg, int last_pos, int end,
		t_app *app)
{
	char	*part;

	if (end > last_pos)
	{
		part = ft_strndup(arg + last_pos, end - last_pos, &app->curr_gc);
		if (!part)
			cleanup_and_exit(app, EXIT_FAILURE);
		part = process_variable_expansion(part, app);
		result = ft_strjoin(result, part, &app->curr_gc);
		if (!result)
			cleanup_and_exit(app, EXIT_FAILURE);
	}
	return (result);
}
