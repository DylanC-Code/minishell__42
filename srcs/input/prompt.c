/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:14:27 by dcastor           #+#    #+#             */
/*   Updated: 2025/07/04 12:06:33 by dcastor          ###   ########.fr       */
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

	if (!user || !status || !core)
		cleanup_and_exit(app, errno);
	result = ft_strjoin(SHELL_EMOJI, user, &app->curr_gc);
	if (!result)
		cleanup_and_exit(app, errno);
	result = ft_strjoin(result, core, &app->curr_gc);
	if (!result)
		cleanup_and_exit(app, errno);
	result = ft_strjoin(result, status, &app->curr_gc);
	if (!result)
		cleanup_and_exit(app, errno);
	result = ft_strjoin(result, PS2_PROMPT, &app->curr_gc);
	if (!result)
		cleanup_and_exit(app, EXIT_FAILURE);
	return (result);
}

char	*get_status(t_app *app)
{
	const char	*status_code_str = get_env_value(app->env_head, "?");
	char		*res;
	char		*ret;

	res = " ";
	if (!status_code_str || !ft_strcmp(status_code_str, "0"))
		return (ft_strdup(GREEN " 0 " RESET "\n", &app->curr_gc));
	res = ft_strjoin(res, RED, &app->curr_gc);
	if (!res)
		cleanup_and_exit(app, errno);
	res = ft_strjoin(res, status_code_str, &app->curr_gc);
	if (!res)
		cleanup_and_exit(app, errno);
	ret = ft_strjoin(res, "\n" RESET, &app->curr_gc);
	if (!ret)
		cleanup_and_exit(app, errno);
	return (ret);
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
		cleanup_and_exit(app, errno);
	return (ft_strjoin(result, RESET, &app->curr_gc));
}

char	*get_core(t_app *app)
{
	char		cwd[1024];
	const char	*prefix = MAGENTA "@" BLUE "minishell: ";
	const char	*unknown = "unknown";

	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_strjoin(prefix, unknown, &app->curr_gc));
	return (ft_strjoin(prefix, cwd, &app->curr_gc));
}
