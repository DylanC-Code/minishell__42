/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:22:03 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/28 22:22:12 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_var(char *s, int *i, t_app *app)
{
	char	*result;
	char	*var_name;
	char	*value;
	int		var_start;

	result = ft_strndup(s, *i, &app->curr_gc);
	var_start = *i + 1;
	(*i)++;
	while (s[*i] && valid_var_char(s[*i]))
		(*i)++;
	var_name = ft_strndup(s + var_start, *i - var_start, &app->curr_gc);
	value = look_up_env(var_name, app->env_head);
	result = ft_strjoin(result, value, &app->curr_gc);
	return (ft_strjoin(result, s + *i, &app->curr_gc));
}

char	*process_variable_expansion(char *section, t_app *app)
{
	int	i;

	i = 0;
	while (section[i])
	{
		if (section[i] == '$' && valid_env_start(section[i + 1]))
			return (build_var(section, &i, app));
		i++;
	}
	return (ft_strdup(section, &app->curr_gc));
}

char	*process_section_literal(char *s, int start, int end, t_app *app)
{
	return (ft_strndup(s + start, end - start, &app->curr_gc));
}

char	*process_section_expand(char *s, int start, int end, t_app *app)
{
	char	*section;

	section = ft_strndup(s + start, end - start, &app->curr_gc);
	return (process_variable_expansion(section, app));
}
