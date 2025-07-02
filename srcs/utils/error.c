/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:55:49 by dcastor           #+#    #+#             */
/*   Updated: 2025/06/26 16:06:22 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_app *app, char *msg, char *error_code)
{
	char	*res;

	set_env_value(app, "?", error_code);
	res = ft_strjoin("minishell: ", msg, &app->curr_gc);
	if (!res || !msg)
		cleanup_and_exit(app, EXIT_FAILURE);
	ft_putstr_fd(res, STDERR_FILENO);
}

void	exit_with_error(t_app *app, char *msg)
{
	perror(msg);
	cleanup(app);
	exit(errno);
}
