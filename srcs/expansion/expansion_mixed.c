/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_mixed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:36:07 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:36:33 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quoted_part(char *arg, int *i, t_app *app)
{
	char	quote_char;
	int		end;

	quote_char = arg[*i];
	end = find_quote_end(arg, *i, quote_char);
	if (quote_char == '"')
		return (process_section_expand(arg, *i + 1, end, app));
	return (process_section_literal(arg, *i + 1, end, app));
}

void	set_mixed_quotes_vars(t_app *app, char **res, int *i)
{
	*i = 0;
	*res = ft_strdup("", &app->curr_gc);
	if (!*res)
		cleanup_and_exit(app, EXIT_FAILURE);
}

char	*process_mixed_quotes(char *arg, t_app *app)
{
	char	*result;
	char	*part;
	int		i;
	int		start;

	set_mixed_quotes_vars(app, &result, &i);
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			part = handle_quoted_part(arg, &i, app);
			i = find_quote_end(arg, i, arg[i]) + 1;
		}
		else
		{
			start = i;
			part = handle_unquoted_part(arg, start, &i, app);
		}
		result = ft_strjoin(result, part, &app->curr_gc);
		if (!result)
			cleanup_and_exit(app, EXIT_FAILURE);
	}
	return (result);
}

int	contains_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
