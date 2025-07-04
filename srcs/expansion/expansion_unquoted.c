/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_unquoted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:33:48 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 13:30:32 by dcastor          ###   ########.fr       */
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

typedef struct s_b
{
	char	*result;
	char	*arg;
	int		last_pos;
	int		pos;
	int		pwned;
	int		end;
}			t_b;

char	*handle_remaining_text(t_app *app, t_b *b)
{
	char	*part;

	if (b->end > b->last_pos)
	{
		part = ft_strndup(b->arg + b->last_pos, b->end - b->last_pos,
				&app->curr_gc);
		if (!part)
			cleanup_and_exit(app, EXIT_FAILURE);
		part = process_variable_expansion(part, app);
		b->result = ft_strjoin(b->result, part, &app->curr_gc);
		if (!b->result)
			cleanup_and_exit(app, EXIT_FAILURE);
	}
	return (b->result);
}

// char	*add_text_before_dollar(char *result, char *arg, int last_pos, int pos,
// t_app *app)
char	*add_text_before_dollar(t_app *app, t_b *b)
{
	char	*part;

	if (b->pos > b->last_pos)
	{
		part = ft_strndup(b->arg + b->last_pos, b->pos - b->last_pos,
				&app->curr_gc);
		if (!part)
			cleanup_and_exit(app, EXIT_FAILURE);
		part = process_variable_expansion(part, app);
		b->result = ft_strjoin(b->result, part, &app->curr_gc);
		if (!b->result)
			cleanup_and_exit(app, EXIT_FAILURE);
	}
	return (b->result);
}

char	*process_unquoted_text(char *arg, int start, int end, t_app *app)
{
	t_b		b;
	char	*part;

	ft_bzero(&b, sizeof(t_b));
	b.arg = arg;
	b.end = end;
	b.result = set_unquoted_vars(app, &b.pos, &b.last_pos, start);
	while (b.pos < end)
	{
		b.pwned = (arg[b.pos + 1] == '"' || arg[b.pos + 1] == '\'');
		if (arg[b.pos] == '$' && b.pos + 1 < end && b.pwned)
		{
			b.result = add_text_before_dollar(app, &b);
			part = handle_dollar_patterns(arg, &b.pos, app);
			b.result = ft_strjoin(b.result, part, &app->curr_gc);
			if (!b.result)
				cleanup_and_exit(app, EXIT_FAILURE);
			b.last_pos = b.pos;
		}
		else
			b.pos++;
	}
	return (handle_remaining_text(app, &b));
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
