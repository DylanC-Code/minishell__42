/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:09:37 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/29 10:49:10 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_option(char *arg);

void	echo_builtin(t_app *app, char **args)
{
	bool	is_n;

	(void)app;
	is_n = true;
	while (*args)
	{
		if (!is_option(*args))
			break ;
		is_n = false;
		args++;
	}
	if (*args)
		printf("%s", *args++);
	while (*args)
		printf(" %s", *args++);
	if (is_n)
		printf("\n");
	set_env_value(app, "?", "0");
}

static bool	is_option(char *arg)
{
	if (*arg++ != '-')
		return (false);
	while (*arg)
		if (*arg++ != 'n')
			return (false);
	return (true);
}
