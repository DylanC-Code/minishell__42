/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:09:37 by saal-kur          #+#    #+#             */
/*   Updated: 2025/06/26 17:52:16 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_option(char *arg);

void	echo_builtin(t_app *app, char **args)
{
	bool	is_n;

	(void)app;
	is_n = false;
	while (*args)
	{
		if (!is_option(*args))
			break ;
		is_n = true;
		args++;
	}
	if (*args)
		printf("%s", *args++);
	while (*args)
		printf(" %s", *args++);
	if (is_n)
		printf("\n");
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
