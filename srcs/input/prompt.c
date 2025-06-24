/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:14:27 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/24 14:38:27 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_status(t_app *app);
char	*get_user(t_app *app);
char	*get_core(t_app *app);

char	*get_prompt(t_app *app)
{
	const char	*user = get_user(app);
	const char	*status = get_status(app);
	const char	*core = get_core(app);
	char		*result;

	result = SHELL_EMOJI;
	if (!user || !status || !core)
		return (NULL);
	result = ft_strjoin(result, user, &app->curr_gc);
	if (!result)
		return (NULL);
	result = ft_strjoin(result, core, &app->curr_gc);
	if (!result)
		return (NULL);
	result = ft_strjoin(result, status, &app->curr_gc);
	if (!result)
		return (NULL);
	return (ft_strjoin(result, MAGENTA "\n> " RESET, &app->curr_gc));
}

char	*get_status(t_app *app)
{
	const char	*status_code_str = get_env_value(app->env_head, "?");
	char		*res;

	res = " ";
	if (!status_code_str || !ft_strcmp(status_code_str, "0"))
		return (ft_strdup(GREEN " 0 " RESET, &app->curr_gc));
	res = ft_strjoin(res, RED, &app->curr_gc);
	if (!res)
		return (res);
	res = ft_strjoin(res, status_code_str, &app->curr_gc);
	if (!res)
		return (NULL);
	return (ft_strjoin(res, RESET, &app->curr_gc));
}

char	*get_user(t_app *app)
{
	const char	*user = get_env_value(app->env_head, "USER");
	char		*result;

	result = YELLOW " ";
	if (!user)
		user = "unknown";
	result = ft_strjoin(result, user, &app->curr_gc);
	if (!result)
		return (NULL);
	return (ft_strjoin(result, RESET, &app->curr_gc));
}

char	*get_core(t_app *app)
{
	char		cwd[1024];
	const char	*prefix = MAGENTA "@" BLUE "minishell: ";

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	return (ft_strjoin(prefix, cwd, &app->curr_gc));
}
