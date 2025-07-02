/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:22:26 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:22:50 by dcastor          ###   ########.fr       */
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

char	*handle_unquoted_part(char *arg, int start, int *i, t_app *app)
{
	while (arg[*i] && arg[*i] != '"' && arg[*i] != '\'')
		(*i)++;
	return (process_section_expand(arg, start, *i, app));
}

char	*process_mixed_quotes(char *arg, t_app *app)
{
	char	*result;
	char	*part;
	int		i;
	int		start;

	result = ft_strdup("", &app->curr_gc);
	i = 0;
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
	}
	return (result);
}
