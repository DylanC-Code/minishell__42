/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_sections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:32:22 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 11:32:55 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_variable_expansion(char *section, t_app *app)
{
	return (build_vars(section, app));
}

char	*process_section_literal(char *s, int start, int end, t_app *app)
{
	char	*res;

	res = ft_strndup(s + start, end - start, &app->curr_gc);
	if (!res)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (res);
}

char	*process_section_expand(char *s, int start, int end, t_app *app)
{
	char	*section;

	section = ft_strndup(s + start, end - start, &app->curr_gc);
	if (!section)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (process_variable_expansion(section, app));
}
