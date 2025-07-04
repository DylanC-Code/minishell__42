/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:22:03 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:29:04 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_build_vars_variables(int *pos, int *last_pos, char **res,
		t_app *app)
{
	*pos = 0;
	*last_pos = 0;
	*res = ft_strdup("", &app->curr_gc);
	if (!*res)
		cleanup_and_exit(app, EXIT_FAILURE);
}

char	*add_text_part(char *str, int start, int end, t_app *app)
{
	char	*temp;

	if (start >= end)
		return ("");
	temp = ft_strndup(str + start, end - start, &app->curr_gc);
	if (!temp)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (temp);
}

char	*join_parts(char *result, char *part, t_app *app)
{
	char	*new_result;

	new_result = ft_strjoin(result, part, &app->curr_gc);
	if (!new_result)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (new_result);
}

char	*handle_dollar_patterns(char *str, int *pos, t_app *app)
{
	if (str[*pos + 1] == '"')
		return (handle_dollar_quote(str, pos, app));
	else if (str[*pos + 1] == '\'')
		return (handle_dollar_single_quote(str, pos, app));
	else
		return (handle_regular_var(str, pos, app));
}

char	*build_vars(char *str, t_app *app)
{
	char	*result;
	char	*part;
	int		pos;
	int		last_pos;

	set_build_vars_variables(&pos, &last_pos, &result, app);
	while (str[pos])
	{
		if (str[pos] == '$' && str[pos + 1] && (valid_env_start(str[pos + 1])
				|| str[pos + 1] == '"' || str[pos + 1] == '\''))
		{
			part = add_text_part(str, last_pos, pos, app);
			result = join_parts(result, part, app);
			part = handle_dollar_patterns(str, &pos, app);
			result = join_parts(result, part, app);
			last_pos = pos;
		}
		else
			pos++;
	}
	part = add_text_part(str, last_pos, pos, app);
	return (join_parts(result, part, app));
}
