/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:31:20 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:31:45 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dollar_quote(char *str, int *pos, t_app *app)
{
	char	*part;
	int		last_pos;

	(*pos)++;
	(*pos)++;
	last_pos = *pos;
	while (str[*pos] && str[*pos] != '"')
		(*pos)++;
	part = ft_strndup(str + last_pos, *pos - last_pos, &app->curr_gc);
	if (!part)
		cleanup_and_exit(app, EXIT_FAILURE);
	part = process_variable_expansion(part, app);
	if (str[*pos] == '"')
		(*pos)++;
	return (part);
}

char	*handle_dollar_single_quote(char *str, int *pos, t_app *app)
{
	char	*part;
	int		last_pos;

	(*pos)++;
	(*pos)++;
	last_pos = *pos;
	while (str[*pos] && str[*pos] != '\'')
		(*pos)++;
	part = ft_strndup(str + last_pos, *pos - last_pos, &app->curr_gc);
	if (!part)
		cleanup_and_exit(app, EXIT_FAILURE);
	if (str[*pos] == '\'')
		(*pos)++;
	return (part);
}

char	*handle_regular_var(char *str, int *pos, t_app *app)
{
	char	*part;
	int		last_pos;

	last_pos = ++(*pos);
	*pos = find_var_end(str, *pos);
	part = get_var_value(str, last_pos, *pos, app);
	return (part);
}
